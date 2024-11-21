En un sistema para acreditar carreras universitarias, hay UN Servidor que atiende pedidos
de U Usuarios de a uno a la vez y de acuerdo con el orden en que se hacen los pedidos.
Cada usuario trabaja en el documento a presentar, y luego lo envía al servidor; espera la
respuesta del mismo que le indica si está todo bien o hay algún error. Mientras haya algún
error vuelve a trabajar con el documento y a enviarlo al servidor. Cuando el servidor le
responde que está todo bien el usuario se retira. Cuando un usuario envía un pedido espera
a lo sumo 2 minutos a que sea recibido por el servidor, pasado ese tiempo espera un minuto
y vuelve a intentarlo (usando el mismo documento).

Procedure sistema is
    task type usuarios;
    task servidor is
        entry pedidos(documento:in string, exito:out bool);
    end;
    arrUsuarios:array(1..U)of usuarios;
    task body usuarios is
        string documento;
        bool exito=false;
        bool same=false;
    begin
        while(exito==false) loop
            if(same=false) then trabajar(documento);
            select
                servidor.pedido(documento,exito);
            or delay 120
                    exito:=false;
                    same:=false;
                    delay 60;
            end select
        end loop;
        retirarse();
    end usuario;
    task body servidor is
    begin
        loop
            accept pedido(documento:in string, exito:out bool)do
                exito=procesar(documento);
            end pedido;
        end loop;
    end servidor;
begin
    null;
end sistema;


