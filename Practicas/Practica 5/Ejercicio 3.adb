3. Se dispone de un sistema compuesto por 1 central y 2 procesos. Los procesos envían
señales a la central. La central comienza su ejecución tomando una señal del proceso 1,
luego toma aleatoriamente señales de cualquiera de los dos indefinidamente. Al recibir una
señal de proceso 2, recibe señales del mismo proceso durante 3 minutos.
El proceso 1 envía una señal que es considerada vieja (se deshecha) si en 2 minutos no fue
recibida.
El proceso 2 envía una señal, si no es recibida en ese instante espera 1 minuto y vuelve a
mandarla (no se deshecha).
procedure sistema is    
    task type profesor;
    task central is
        entry pedido1();
        ebtry pedido2();
    end central;
    arrProfesor: array (1..2) of profesor;
    task body profesor is
    begin
        select
            central.pedido1();
        or delay 120
            null;
        end select;
        central.pedido2();
    end profesor
    task body central is
    begin
        accept pedido1();
        end pedido1;
        loop
            accept pedido1();
            end pedido
--falta completar no se como hacer el timer