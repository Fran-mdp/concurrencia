 En una playa hay 5 equipos de 4 personas cada uno (en total son 20 personas donde cada 
una  conoce  previamente  a  que  equipo  pertenece).  Cuando  las  personas  van  llegando 
esperan  con  los  de  su  equipo  hasta  que  el  mismo  esté  completo  (hayan  llegado  los  4 
integrantes), a partir de ese momento el equipo comienza a jugar. El juego consiste en que 
cada integrante del grupo junta 15 monedas de a una en una playa (las monedas pueden ser 
de  1,  2  o  5  pesos)  y  se  suman  los  montos  de  las  60  monedas  conseguidas  en  el  grupo.  Al 
finalizar  cada  persona  debe  conocer  grupo  que  más  dinero  junto.  Nota:  maximizar  la 
concurrencia.  Suponga  que  para  simular  la  búsqueda  de  una  moneda  por  parte  de  una 
persona existe una función Moneda() que retorna el valor de la moneda encontrada.
procedure Juego is
    task persona is
        entry ganador(equipo:in int);
    task coordinador is
        entry llegada();
        entry pedido(monto:in int,fin:out bool);
    end coordinador;
    arraPersonas:array(1..20) of persona;
    arrCoordinadores: array(1..5) of Coordinador
    task body personas is
        int monto=0;
        bool fin=false;
    begin
        coordinador(miequipo).llegada();
        while(fin==false)loop
            monto:=moneda();
            coordinador.pedido(monto,fin);
        end loop;
    end Persona;
    task body coordinador is
        int total=0;
        int cont=0;
    begin
        for i in 1..4 loop
            accept llegada();
        end loop;
        while cont<60 loop
            accept pedido(monto:in int,fin:out bool);
            total:=total+monto;
            end pedido;
        cont++:
        end loop;
        while pedido´count>0 loop
            accept pedido(monto:in int,fin:out bool);
                fin:=true;
            end pedido;
        end loop;
    end coordinador;
begin
    null;
end Juego;
    