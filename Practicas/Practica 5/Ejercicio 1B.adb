/*Se requiere modelar un puente de un solo sentido, el puente solo soporta el peso de 5
unidades de peso. Cada auto pesa 1 unidad, cada camioneta pesa 2 unidades y cada camión
3 unidades. Suponga que hay una cantidad innumerable de vehículos (A autos, B
camionetas y C camiones).
b. Modifique la solución para que tengan mayor prioridad los camiones que el resto de los
vehículos*/

procedure Puente is
    -- Definir el puente como una tarea única
    task Puente is
        entry AutoOK;
        entry CamionetaOK;
        entry CamionOK;
        entry Salida(Peso : in Integer);
    end Puente;

    -- Definir los tipos de tareas para los vehículos
    task type Auto;
    task type Camioneta;
    task type Camion;

    -- Crear arreglos de vehículos
    ArrAutos : array(1..A) of Auto;
    ArrCamionetas : array(1..B) of Camioneta;
    ArrCamiones : array(1..C) of Camion;

    -- Implementación de la tarea Auto
    task body Auto is
        Peso : constant Integer := 1;
    begin
        Puente.AutoOK;                  -- Solicitar acceso al puente
        Put_Line("Auto cruzando el puente...");
        TransitarPuente();              -- Simular el tránsito
        Puente.Salida(Peso);            -- Notificar salida del puente
    end Auto;

    -- Implementación de la tarea Camioneta
    task body Camioneta is
        Peso : constant Integer := 2;
    begin
        Puente.CamionetaOK;             -- Solicitar acceso al puente
        Put_Line("Camioneta cruzando el puente...");
        TransitarPuente();              -- Simular el tránsito
        Puente.Salida(Peso);            -- Notificar salida del puente
    end Camioneta;

    -- Implementación de la tarea Camion
    task body Camion is
        Peso : constant Integer := 3;
    begin
        Puente.CamionOK;                -- Solicitar acceso al puente
        Put_Line("Camión cruzando el puente...");
        TransitarPuente();              -- Simular el tránsito
        Puente.Salida(Peso);            -- Notificar salida del puente
    end Camion;

    -- Implementación del puente
    task body Puente is
        PesoActual : Integer := 0;      -- Peso total actual en el puente
    begin
        loop
            select
                -- Salida de un vehículo, actualizar el peso
                accept Salida(Peso : in Integer) do
                    PesoActual := PesoActual - Peso;
                    Put_Line("Un vehículo salió del puente. Peso actual: " & PesoActual'Image);
                end;
            or
                -- Permitir acceso a un camión si hay capacidad
                when PesoActual + 3 <= 5 =>
                    accept CamionOK do
                        PesoActual := PesoActual + 3;
                        Put_Line("Camión ingresó al puente. Peso actual: " & PesoActual'Image);
                    end;
            or
                -- Permitir acceso a una camioneta si hay capacidad y no hay camiones esperando
                when (CamionOK'Count = 0 and PesoActual + 2 <= 5) =>
                    accept CamionetaOK do
                        PesoActual := PesoActual + 2;
                        Put_Line("Camioneta ingresó al puente. Peso actual: " & PesoActual'Image);
                    end;
            or
                -- Permitir acceso a un auto si hay capacidad y no hay camiones ni camionetas esperando
                when (CamionOK'Count = 0 and CamionetaOK'Count = 0 and PesoActual + 1 <= 5) =>
                    accept AutoOK do
                        PesoActual := PesoActual + 1;
                        Put_Line("Auto ingresó al puente. Peso actual: " & PesoActual'Image);
                    end;
            end select;
        end loop;
    end Puente;

begin
    null; -- Punto de entrada al procedimiento principal
end Puente;
