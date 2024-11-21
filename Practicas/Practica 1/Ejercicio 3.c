/* Realice una solución concurrente de grano grueso (utilizando <> y/o <await B; S>) para el 
siguiente problema. Un sistema operativo mantiene 5 instancias de un recurso almacenadas 
en una cola, cuando un proceso necesita usar una instancia del recurso la saca de la cola, la 
usa y cuando termina de usarla la vuelve a deposita*/
cola instancias;
process So{
    <if(not empty(instancias);pop(cintancias))>;
    //usar
    <push(instancias)>;

}