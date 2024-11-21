En una clínica existe un médico de guardia que recibe continuamente peticiones de
atención de las E enfermeras que trabajan en su piso y de las P personas que llegan a la
clínica ser atendidos.
Cuando una persona necesita que la atiendan espera a lo sumo 5 minutos a que el médico lo
haga, si pasado ese tiempo no lo hace, espera 10 minutos y vuelve a requerir la atención del
médico. Si no es atendida tres veces, se enoja y se retira de la clínica.
Cuando una enfermera requiere la atención del médico, si este no lo atiende inmediatamente
le hace una nota y se la deja en el consultorio para que esta resuelva su pedido en el
momento que pueda (el pedido puede ser que el médico le firme algún papel). Cuando la
petición ha sido recibida por el médico o la nota ha sido dejada en el escritorio, continúa
trabajando y haciendo más peticiones.
El médico atiende los pedidos dándoles prioridad a los enfermos que llegan para ser
atendidos. Cuando atiende un pedido, recibe la solicitud y la procesa durante un cierto
tiempo. Cuando está libre aprovecha a procesar las notas dejadas por las enfermeras.

Procedure atencion is
    task type paciente;
    task type enfermeras;
    task medico is
        entry pedidoP(caso:in string,resultado:out string);
        entry pedidoE_atencion(caso2:in string,resultado2:out string);
    end medico;
    arrEnfermera:array(1..E)of enfermeras;
    arrPaciente:array (1..P)of paciente;
    task body paciente is   
    begin   
        select
            medico.pedidoP(caso:in string,resultado:out string);
        or delay 300
            or delay 600
                null;
        end select
    end paciente;
    task body enfermera is
    begin   
        medico.pedidoE_atencion(caso2:in string,resultado:out string);
    end enfermera;
    task body medico is
    begin
        loop
            select
                accept pedidoE_atencion(caso2:in string,resultado:out string)do
                resultado2=AtenderEnfermera(caso2)
                end pedidoE_atencion;
            or
                //dejar nota
                when(pedidoE_atencion´count=0)=>
                    accept pedidoP(caso:in string,reusltado:out string);
                    resultado=AtenderPaciente(caso);
                end pedidoP;
            end select;
        end loop;
    end medico;
begin
    null;
end atención;

        