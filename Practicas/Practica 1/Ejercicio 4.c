/*Realice  una  solución  concurrente  de  grano  grueso  (utilizando  <>  y/o  <await  B;  S>)  el 
siguiente problema. Se debe calcular el valor promedio de un vector de 1000 números por 
medio de 10 procesos. Al finalizar todos los procesos deben guardar en una variable local el 
resultado final.*/
vector=[1000](int)//vector de numeros enteros
int termine=0;
int total=0;
int promedio=0;
process worker[id:0..9]{
    int inicio=id*100;
    int fin=inicio+100;
    int suma=0;
    for(int i=inicio; i<fin;i++){
        suma:=suma+vector[i];
    }
    <total=total+suma>;
    <termine++>;
    <Await(termine==10)>
    <promedio=total/1000>;
}