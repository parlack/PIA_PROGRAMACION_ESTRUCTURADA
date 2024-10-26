#include <stdio.h>
#include <stdbool.h>
#include "Validations.h"

void lecturaArticulo(FILE *archivo)
{
    struct infoArticulo Data;
    bool isValid;
    char ingresarMas;
    int mercados = 0, insumos = 0;

    do
    {
        printf("Ingrese la clave del articulo [1 - 1000] ~ ");
        scanf("%d", &Data.clave);

        bool isValid = isInRange( (float)Data.clave, 1, 1000);
        
        if (!isValid)
            printf("ERROR: Clave de empleado invalida.\t Ingrese la clave del empleado [1 - 1000] ~");

    } while (!isValid);
    
    do
    {
        do
        {
            printf("Ingrese la clave del mercado [ %d/10 mercados guardados] ~ ", mercados);

            if(scanf("%d", &Data.clavesMercado[mercados]) != 1) // FUNCION para ver que exista la clave del mercado
                isValid = false;
            else    
                isValid = true;
            

            if (!isValid)
                printf("ERROR: Clave de mercado invalida.\t Ingrese la clave del mercado [ %d/10] ~ ", mercados);
            else
                mercados++;

        } while (!isValid);
        
        printf("Ingresar información de otro mercado? [ %d/10 mercados guardados ] ~ ", mercados);
        fflush(stdin);
        scanf("%c", &ingresarMas);
        
    } while (mercados < 10 && ingresarMas == 'S');
    
}
 
void LecturaEmpleado(FILE *archivo)
{
    struct infoEmpleado Data;
    int distanciaCaracteres;
    bool isValid;
    do
    {
        printf("Ingrese la clave del empleado[1 - 1000]: ");
        scanf("%d", Data.clave);
    } while (!isInRange(Data.clave, 1, 1000));

    do
    {
        do
        {
            printf("Ingrese los nombres del empleado (Sin apellidos): ");
            scanf("%d", &Data.datosPersonales.nombres);

            isValid = isAlphabetic(Data.datosPersonales.nombres, false);
            if(!isValid) 
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
            


        } while (!isValid);
        
        do
        {
            printf("Ingrese apellido paterno del empleado: ");
            scanf("%d", Data.datosPersonales.apellidoPaterno);

            isValid =isAlphabetic(Data.datosPersonales.apellidoPaterno, false);
            if(!isValid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
        } while(!isValid);

        do
        {
            printf("Ingrese apellido materno del empleado: ");
            scanf("%d", Data.datosPersonales.apellidoMaterno);
            
            isValid =isAlphabetic(Data.datosPersonales.apellidoMaterno, false);
            if(!isValid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
        } while(!isValid);

        distanciaCaracteres = lengthChar(Data.datosPersonales.nombres) + 
        lengthChar(Data.datosPersonales.apellidoMaterno) + 
        lengthChar(Data.datosPersonales.apellidoPaterno);

        isValid = distanciaCaracteres > 20;
        if(!isValid)
            printf("ERROR: La distancia de caracteres es MENOR a 20. \n");

    } while (!isValid);
    

    //FALTA VALIDACION DE RFC DEL EMPLEADO

    /*do
    {
        printf("Ingrese el RFC del empleado[1 - 1000]: ");
        scanf("%d", Data.datosPersonales.RFC);


    } while (!isInRange(Data.clave, 1, 1000));*/

    
    
}
 