//Ejercicio de await
bool libre=true;
int actual=0;
bool ok=false;
process personas[id:1..15]{
    <await(actial=id)>;//espero que el paciente sea igual que el que llamo el medico
    ok=true;//confirmo la llegada del paciente
    //atender
    <Await(listo)>;//termina la atencion
    listo=false;//el paciente se va
}
process medico{
    for(i=1;i<15;i++){
        i=actual;//me fijo el proximo paciente que le toca
        <Await(ok)>;//me quedo esperando a la llegada del paciente
        ok=false;
        //atiendo
        listo=true;//confirma que termino de atender
        <Await(libre=false)>;//espero hasta que el paciente se vaya
    }
}
//ejercicio de semaforos
sem mutex[4]=({4}0);
cola fila[4];
sem espera[100]=({100}0);
sem atencion[4]=({4}0);
string respuesta[100];
process persona[id:1..100]{
    int puesto=generarPuesto();//cada persona sabe a que puesto ir
    string tramite;//tramite para cada persona
    p(mutex[puesto]);//bloqueo el accesso a la sc para cada puesto
    push(fila[puesto]{id,tramite});//dejo el tramite de cada persona
    v(atencion[puesto]);//despiesto al puesto para que ateienda a la persona
    v(mutex[puesto]);//libero la sc
    p(espera[id]);//espero el resultado para irme
}
process puesto[id:1..4]{
    string res,tramite;
    int idP;
    for(int i=1;i<25;i++){
        p(atencion[id]);//me quedo bloqueado esperando a que me despierte una persona
        p(mutex[id]);
        pop(fila[id]{idP,tramite});//me guardo en la variables locales idP y tramite lo que dejo la persona
        v(mutex[id]);
        res=generaRespuesta(tramite);
        respuesta[idP]=res;
        v(espera[idP]);
    }
}

//Ejercicio de monitores
process persona[id:1..N]{
    string prioridad=generaPrioridad();
    telefono.llegada(prioridad,id);
    usar_telefono();
    telefono.salir();
}
monitor telefono{
    int esperando=0;
    cola fila_con_priordad;
    cond c[n];
    int aux;
    bool libre;
    string prioridad;
    procedure llegada(tipo:in string,idP:in int){
        if(libre=false){
            push(fila_con_prioridad(tipo,idP));
            esperando++;
            wait(c[idP]);
        }else
            libre=false
    }
}
    procedure termine(){
        if(esperando>0){
            pop(fila_con_prioridad(tipo,aux)):
            esperando--;
            signal(c[aux]);
        }else
            libre=true;
    }

