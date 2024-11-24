//Ejercicio de pma
chan pedido[4](string,int);
chan siguiente(int);
chan respuesta[N](string);
process personas[id:1..N]{
    int idE;
    receive siguiente(idE);
    send pedido[idE](presupuesto,id);
    receive respuesta[id] (res);
}
process empleado[id:1..5]{
    string presupuesto,res;
    int idP;
    for (int i=1;i<N;i++){
        send siguiente(id);
        recive pedido[id](presupuesto,idP);
        res=HacerPresupuesto(presupuesto);
        send respuesta[idP](res);
}
}
//Ejercicio de pms

process cliente[id:1..N]{
    string tipo_nafta=generarTipo();
    int cantidad=generaCantidad();
    admin!pedido(tipo_nafta,cantidad,id);
    empleado?termine();
}
process empleado{
    string tipo;
    int idC;

    admin!siguiente();
    admin?carga(tipo,cantidad,idC);
    while(idC<>-1){
        //carga nafta
        cliente[idC]!termine();
        admin!siguiente();
        admin?carga(tipo,cantidad,idC);
}
}
process admin{
    int idC;
    string tipo;
    int cantidad=0;
    int cant=0;
    cola fila;
    do(cant<N);cliente[*]?pedido(tipo,cantidad,idC)->push(fila{tipo,cantidad,idC})
    [](not empty(fila));siguiente?empleado();->pop(fila{tipo,cantidad,idC});
        empleado!carga(tipo,cantidad,idc);
        cant++;
    empleado?siguiente();
    empleado!carga(tipo,cantidad,-1);

}

//ejercicio de ada
procedure ada is
    task type cliente;
    task empleado is
        entry mail(lista:in string,presupuesto:out string);
        entry presencial(lista:in string,presupuesto:out string);
    end empleado;
    arraClientes=array(1..n)of cliente;
    task body cliente is
        string lista,presupuesto;
    begin
        lista=generaListaProductos();
        if(Presencial){
            empleado.presencial(lista,presupuesto);
        }else
            empleado.mail(lista,presupuesto);
    end cliente;
    task body empleado is
    begin
        loop
            select
                accept presencial(lista:in string,presupuesto:out string)do
                    presupuesto=HacerPresupuesto(lista);
                end presencial;
            or
                when(presencial´count=0)=> accept mail(lista:in string,presupuesto:out string) do
                                            presupuesto=HacerPresupuesto(lista);
                                            end mail;
            or  delay(600);
                acomodarLocal();
            end select;
        end loop;
    end empleado;
begin
    null;
end ada;