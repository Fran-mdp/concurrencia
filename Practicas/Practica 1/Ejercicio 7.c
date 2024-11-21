/*7.  Realice  una  solución  concurrente  de  grano  grueso  (utilizando  <>  y/o  <await  B;  S>)  el 
siguiente  problema.  Una  empresa  de  turismo  posee  UN  micro  con  capacidad  para  50 
personas. Hay un único vendedor donde C pasajeros (C > 50) intentan comprar un pasaje 
(de  acuerdo  al  orden  de  llegada);  si  aún  hay  lugar  se  dirige  al  micro  para  subir;  en  caso 
contrario se retira. El micro espera a que suban los 50 pasajeros (suben de a uno y sin importar 
el orden), luego realiza el viaje, y cuando llega al destino deja bajar a todos los pasajeros.*/
int capacidad=50;
cola fila;
bool libre=true;
process personas[id:1..C]{
    <if(libre=true) libre=false;
     else push(fila)>;

}
process vendedor{
    
}