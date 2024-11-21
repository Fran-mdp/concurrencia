/*Resolver con PMA (Pasaje de Mensajes ASINCRÓNICOS) el siguiente problema. En un negocio hay 3
empleados que atienden de acuerdo al orden de llegada a N personas que van a pedir un presupuesto. Cuando el
cliente sabe que empleado lo va a atender le entrega el listado de productos que necesita, y luego el empleado le
entrega el presupuesto del mismo. Cuando un empleado está libre atiende a la primera persona que esté esperando
para ser atendida, y si no hubiese nadie esperando se dedica a ordenar el local durante unos minutos.*/
chan pedidos(int);              // Canal para que las personas pidan ser atendidas
chan elejido[N](int);           // Canal para asignar empleados a las personas
chan atencion[3](string);       // Canal para enviar la lista de productos a los empleados
chan respuesta[N](string);      // Canal para que los empleados envíen los presupuestos a las personas
chan siguiente(int);            // Canal para que los empleados pidan al admin un cliente

// Proceso Persona
process persona[id: 0..N-1] {
    string lista, presu;
    int idE;
    while (true) {
        // Solicitar ser atendido
        send pedidos(id);

        // Esperar asignación de un empleado
        receive elejido[id](idE);

        // Enviar listado al empleado asignado
        lista = generarListado();
        send atencion[idE](lista);

        // Recibir presupuesto del empleado
        receive respuesta[id](presu);

        // Procesar el presupuesto recibido
        procesarPresupuesto(presu);
    }
}

// Proceso Admin
process admin {
    int idP, idE;
    while (true) {
        // Esperar solicitud de un empleado
        receive siguiente(idE);

        // Asignar cliente si hay en la cola
        if (not empty(pedidos)) {
            receive pedidos(idP);
            send elejido[idP](idE);
        }
    }
}

// Proceso Empleados
process empleados[id: 0..2] {
    int idC;
    string listado, presupuesto;
    while (true) {
        // Solicitar al admin un cliente
        send siguiente(id);

        // Atender cliente si hay en el canal de atención
        if (not empty(atencion[id])) {
            receive atencion[id](listado);

            // Generar presupuesto
            presupuesto = generarPresupuesto(listado);

            // Enviar presupuesto al cliente
            send respuesta[idC](presupuesto);
        } else {
            // Ordenar el local si no hay clientes
            ordenarLocal();
        }
    }
}
/*Resolver con PMS (Pasaje de Mensajes SINCRÓNICOS) el siguiente problema. Simular una clase donde hay 2
ayudantes para atender a A alumnos de acuerdo al orden de llegada. El alumno al llegar espera hasta que cualquiera
de los ayudantes lo atienda, le hace su consulta y cuando el ayudante le responde el alumno se retira. Nota: los
ayudantes no necesitan terminar su ejecución.*/
process alumnos[id:1..A] {
    string consulta, respuesta;

    admin!pedido(id, consulta);  // Enviar consulta al admin
    ayudante?respuesta(respuesta);  // Esperar respuesta del ayudante
    exit();  // Terminar después de recibir respuesta
}

process admin {
    string consulta;
    int alu, id_ayudante;
    cola fila;  // Cola para gestionar consultas

    do 
        alumnos[*]?pedido(alu, consulta) → push(fila, (alu, consulta))
    [](not empty(fila)); ayudante[*]?siguiente(id_ayudante) →
        pop(fila, (alu, consulta));
        ayudante[id_ayudante]!consulta(alu, consulta);
    od
}

process ayudante[id:1..2] {
    string respuesta, consulta;
    int idA;

    while (true) {
        admin!siguiente(id);  // Solicitar una consulta al admin
        admin?consulta(idA, consulta);  // Recibir la consulta
        respuesta = GenerarRespuesta(consulta);  // Generar respuesta
        alumnos[idA]!respuesta(respuesta);  // Responder al alumno
    }
}
/*Resolver con ADA el siguiente problema. Hay un Empleado que atiende pedidos de un Director y de C Clientes
dando prioridad a los pedidos del director. Los clientes al llegar esperan a lo sumo 20 minutos al que el empleado lo
atienda, y si no se retira sin resolver su pedido (intenta sólo una vez hacer el pedido). El director hace un pedido y si
no es atendido inmediatamente espera 10 minutos y lo vuelve a intentar, y esto lo repite hasta que finalmente
atienden su pedido y se retira. Nota: todas las tareas deben terminar.*/
procedure Ada is
    // Declaración del tipo de tarea Cliente
    task type Cliente;
    // Declaración del tipo de tarea Director
    task type Director;
    // Tarea Admin para gestionar la finalización de tareas
    task Admin is
        entry SevaCliente;
        entry SevaDirector;
    end Admin;

    // Tarea Empleado para atender pedidos
    task Empleado is
        entry PedidoClientes(Pedido: in String; Respuesta: out String);
        entry PedidoDirector(Pedido: in String; Respuesta: out String);
        entry Termine;
    end Empleado;

    // Declaración de arrays de Clientes y Directores
    ArrClientes : array (1..C) of Cliente;
    ArrDirector : array (1..D) of Director;

    // Implementación de la tarea Cliente
    task body Cliente is
    begin
        // Intento de hacer el pedido al empleado con un tiempo límite
        select
            Empleado.PedidoClientes("Pedido del Cliente", Respuesta);
        or
            delay 20.0; // Espera de 20 minutos (en segundos)
        end select;
        // Notificación de que el cliente se va
        Admin.SevaCliente;
    end Cliente;

    // Implementación de la tarea Director
    task body Director is
        Atendido : Boolean := False; // Indicador para saber si fue atendido
    begin
        while not Atendido loop
            // El director intenta hacer su pedido
            select
                Empleado.PedidoDirector("Pedido del Director", Respuesta);
                Atendido := True; // Marca que el pedido fue atendido
            or
                delay 10.0; // Espera de 10 minutos (en segundos) antes de reintentar
            end select;
        end loop;
        // Notificación de que el director se va
        Admin.SevaDirector;
    end Director;

    // Implementación de la tarea Empleado
    task body Empleado is
        Fin : Boolean := False; // Indicador para terminar la tarea
    begin
        while not Fin loop
            select
                // Se atienden pedidos del director con prioridad
                accept PedidoDirector(Pedido: in String; Respuesta: out String) do
                    Respuesta := "Resolviendo pedido del director: " & Pedido;
                end PedidoDirector;
            or
                // Los pedidos de clientes se atienden si no hay pedidos del director
                when (PedidoDirector´count==0) =>
                    accept PedidoClientes(Pedido: in String; Respuesta: out String) do
                        Respuesta := "Resolviendo pedido del cliente: " & Pedido;
                    end PedidoClientes;
            end select;
        end loop;
        // Finalización de la tarea
        accept Termine do
            Fin := True;
        end Termine;
    end Empleado;

    //Implementación de la tarea Admin
    task body Admin is
    begin
        // Espera a que todos los clientes terminen
        for I in 1 .. C loop
            accept SevaCliente;
        end loop;
        // Espera a que todos los directores terminen
        for I in 1 .. D loop
            accept SevaDirector;
        end loop;
        // Notificación al empleado para que termine
        Empleado.Termine;
    end Admin;

begin
    null; // Punto de entrada principal del programa
end Ada;
