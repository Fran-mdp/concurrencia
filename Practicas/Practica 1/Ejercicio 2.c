/* Realice una solución concurrente de grano grueso (utilizando <> y/o <await B; S>) para el 
siguiente problema. Dado un numero N verifique cuantas veces aparece ese número en un 
arreglo de longitud M. Escriba las condiciones que considere necesarias.*/
vector=array[m](int) //arreglo de n elementos de enteros
int cant=0;
int numero;
process verificacion{
    for (int i=0;i<m;i++){
        if(numero==vector[i]){
            <cant++>;
        }
    } 
}