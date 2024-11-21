--2. Se quiere modelar la cola de un banco que atiende un solo empleado, los clientes llegan y si
esperan más de 10 minutos se retiran.
procedure banco is
    task empleado is
        entry pedido(solicitud:in string,respuesta:out string);
    end atencion;
    task type cliente;
    arrCliente:array(1..n)of cliente;
    task body cliente is
        solicitud: string;
    begin
        solicitud=GenerarSolicitud();
        select
            empleado.pedido(solicitud);
        or  delay 600;
            null
        end select        
    end;
    task body empleado is       
        solicitud:string;
    begin
        loop 
            accept pedido(solicitud:in/out string,respuesta out string)do
                respuesta=resolverSolicitud(solicitud);
            end pedido;
        end loop;
    end empleado
begin   
    null;
end banco;