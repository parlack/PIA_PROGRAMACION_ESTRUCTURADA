
#include <stdio.h>
#include <stdbool.h>
#include "Validations.h"

void lecturaArticulo(FILE *archivoArticulos)
{
    struct infoArticulo Data;
    bool isValid;
    char ingresarMas, temporada[20];
    int i, mercados = 0, insumos = 0, numeroTemporada;
    Data.costoProduccion = 0;

    do
    {
        printf("\nIngrese la clave del articulo [1 - 1000] ~ ");
        if (scanf("%d", &Data.clave) != 1 || !isInRange((float)Data.clave, 1, 1000))
            isValid = false;
        else
            isValid = true;
        
        if (!isValid)
            printf("\nERROR: Clave de articulo invalida.\n");

    } while (!isValid);


    do
    {
        printf("\nDescripcion del articulo [50 caracteres max.] ~ ");
        fflush(stdin);
        scanf("%50s", Data.descripcion);

        isValid = minStringLength(Data.descripcion, 10);

        if (!isValid)
            printf("\nERROR: Descripcion muy corta.\n");

    } while (!isValid);

    do
    {
        printf("\nTemporada de siembra \n"
                "1 - Primavera\n"
                "2 - Verano\n"
                "3 - Otoño\n"
                "4 - Invierno\n"
                "[Ingresa el numero de la temporada] ~ ");


        if (scanf("%d", &numeroTemporada) != 1 || !isInRange((float)numeroTemporada, 1, 4))
            isValid = false;
        else
            isValid = true;
        
        if (!isValid)
            printf("\nERROR: Numero invalido.\n");

    } while (!isValid);
    
    switch (numeroTemporada)
    {
        case 1:
            strcpy(temporada, "Primavera");
            break;
        case 2:
            strcpy(temporada, "Verano");
            break;
        case 3:
            strcpy(temporada, "Otoño");
            break;
        case 4:
            strcpy(temporada, "Invierno");
            break;
    }
    
    strcpy(Data.temporadaSiembra, temporada);

    do
    {
        printf("\nTemporada de siembra \n"
                "1 - Primavera\n"
                "2 - Verano\n"
                "3 - Otoño\n"
                "4 - Invierno\n"
                "[Ingresa el numero de la temporada] ~ ");

        if (scanf("%d", &numeroTemporada) != 1 || !isInRange((float)numeroTemporada, 1, 4))
            isValid = false;
        else
            isValid = true;
        
        if (!isValid)
            printf("\nERROR: Numero invalido.\n");

    } while (!isValid);
    
    switch (numeroTemporada)
    {
        case 1:
            strcpy(temporada, "Primavera");
            break;
        case 2:
            strcpy(temporada, "Verano");
            break;
        case 3:
            strcpy(temporada, "Otoño");
            break;
        case 4:
            strcpy(temporada, "Invierno");
            break;
    }
    
    strcpy(Data.temporadaCosecha, temporada);

    do
    {
        printf("\nInventario del articulo [Mayor o igual a 0] ~ ");
        if (scanf("%d", &Data.inventario) != 1 || !moreThanZero((float)Data.inventario, true))
            isValid = false;
        else
            isValid = true;
        
        if (!isValid)
            printf("\nERROR: Cantidad invalida.\n");

    } while (!isValid);

    do
    {
        printf("\nPrecio de venta [Mayor a 0] ~ ");
        if (scanf("%f", &Data.precioVenta) != 1 || !moreThanZero(Data.precioVenta, true))
            isValid = false;
        else
            isValid = true;
        
        if (!isValid)
            printf("\nERROR: Clave de empleado invalida.\n");

    } while (!isValid);

    do
    {
        do
        {
            printf("Ingrese la clave del mercado [ %d/10 mercados guardados] ~ ", mercados);

            if(scanf("%d", &Data.clavesMercados[mercados]) != 1 && !existeMercado(&Data.clavesMercados[mercados])) // FUNCION para ver que exista la clave del mercado
                isValid = false;
            else    
                isValid = true;
            
            if (!isValid)
                printf("ERROR: Clave de mercado invalida.\t Ingrese la clave del mercado [ %d/10] ~ ", mercados);

        } while (!isValid);
        
        mercados++;

        printf("Ingresar información de otro mercado? [ %d/10 mercados guardados ] ~ ", mercados);
        fflush(stdin);
        scanf("%c", &ingresarMas);
        
    } while (mercados < 10 && ingresarMas == 'S');

    do
    {
        do
        {
            printf("Ingrese la clave del insumo [ %d/10 insumos guardados] ~ ", insumos);

            if(scanf("%d", &Data.clavesInsumos[insumos]) != 1 && !existeInsumo(&Data.clavesInsumos[insumos])) // FUNCION para ver que exista la clave del insumo
                isValid = false;
            else    
                isValid = true;
            
            if (!isValid)
                printf("ERROR: Clave de insumo invalida.\t Ingrese la clave del insumo [ %d/10] ~ ", insumos);

        } while (!isValid);

        insumos++;
        
        printf("Ingresar información de otro insumo? [ %d/10 insumos guardados ] ~ ", insumos);
        fflush(stdin);
        scanf("%c", &ingresarMas);
        
    } while (insumos < 10 && ingresarMas == 'S');
    /*
    Data.costoProduccion = obtenerCosto(Data.clavesInsumos);

    if ((archivoArticulos = fopen("./Data_files/Articulos.dat", "ab")) == NULL)
        printf("\nError al guardar la información en el archivo\n");
    else
    {
        fseek(archivoArticulos, (Data.clave - 1) * sizeof(Data), SEEK_SET);
        fwrite(&Data, sizeof(Data), 1, archivoArticulos);
        fclose(archivoArticulos);
    }
    */
}

void lecturaEmpleado(FILE *archivo)
{
    struct infoEmpleado Data;
    int distanciaCaracteres;
    bool isValid;

    do
    {
        printf("\nIngrese la clave del empleado [1 - 1000] ~ ");
        if (scanf("%d", &Data.clave) != 1 || !isInRange((float)Data.clave, 1, 1000))
            isValid = false;
        else
            isValid = true;
        
        if (!isValid)
            printf("\nERROR: Clave de empleado invalida.\n");

    } while (!isValid);

    do
    {
        do
        {
            printf("Ingrese los nombres del empleado (Sin apellidos): ");
            scanf("%s", &Data.datosPersonales.nombres);

            if (Data.datosPersonales.nombres)

            isValid = isAlphabetic(Data.datosPersonales.nombres, false);
            if(!isValid) 
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
            


        } while (!isValid);
        
        do
        {
            printf("Ingrese apellido paterno del empleado: ");
            scanf("%s", Data.datosPersonales.apellidoPaterno);

            isValid =isAlphabetic(Data.datosPersonales.apellidoPaterno, false);
            if(!isValid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
        } while(!isValid);

        do
        {
            printf("Ingrese apellido materno del empleado: ");
            scanf("%s", Data.datosPersonales.apellidoMaterno);
            
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

    do
    {
        printf("Ingrese el RFC del empleado[1 - 1000]: ");
        scanf("%d", Data.datosPersonales.RFC);


    } while (!isInRange(Data.clave, 1, 1000));



}
