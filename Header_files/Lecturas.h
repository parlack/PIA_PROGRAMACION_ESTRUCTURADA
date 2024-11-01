#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Validations.h"

void lecturaArticulo(FILE *archivoArticulos)
{
    FILE *archivo_NuevoRegistro;
    struct infoArticulo DatosArticulo;
    bool isInvalid, opcionRegistrarInvalida;
    char ingresarMas, opcionRegistrar;
    int i, mercados = 0, insumos = 0, numeroTemporada;

    do
    {
        printf("\nIngrese la clave del articulo [1 - 1000] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosArticulo.clave) != 1 || !isInIntRange(&DatosArticulo.clave, 1, 1000))
        {
            isInvalid = true;
            printf("\nERROR: Clave de articulo invalida.\n");
        }
        else
            isInvalid = false;

    } while (isInvalid);


    do
    {
        printf("\nDescripcion del articulo [50 caracteres max.] ~ ");
        fflush(stdin);
        fgets(DatosArticulo.descripcion, sizeof(DatosArticulo.descripcion), stdin);

        isInvalid = !minStringLength(DatosArticulo.descripcion, 10);

        if (isInvalid)
            printf("\nERROR: Descripcion invalida, [10 - 50 caracteres].\n");
        
    } while (isInvalid);

    do
    {
        printf("\nTemporada de siembra \n"
                "1 - Primavera\n"
                "2 - Verano\n"
                "3 - Otoño\n"
                "4 - Invierno\n"
                "[Ingresa el numero de la temporada] ~ ");

        fflush(stdin);

        if (scanf("%d", &numeroTemporada) != 1 || !isInIntRange(&numeroTemporada, 1, 4))
        {
            isInvalid = true;
            printf("\nERROR: Numero invalido.\n");
        }
        else
            isInvalid = false;

    } while (isInvalid);
    
    switch (numeroTemporada)
    {
        case 1:
            strcpy(DatosArticulo.temporadaSiembra, "Primavera");
            break;
        case 2:
            strcpy(DatosArticulo.temporadaSiembra, "Verano");
            break;
        case 3:
            strcpy(DatosArticulo.temporadaSiembra, "Otoño");
            break;
        case 4:
            strcpy(DatosArticulo.temporadaSiembra, "Invierno");
            break;
    }
    
    do
    {
        printf("\nTemporada de cosecha \n"
                "1 - Primavera\n"
                "2 - Verano\n"
                "3 - Otoño\n"
                "4 - Invierno\n"
                "[Ingresa el numero de la temporada] ~ ");

        fflush(stdin);

        if (scanf("%d", &numeroTemporada) != 1 || !isInIntRange(&numeroTemporada, 1, 4))
        {
            isInvalid = true;
            printf("\nERROR: Numero invalido.\n");
        }
        else
            isInvalid = false;

    } while (isInvalid);
    
    switch (numeroTemporada)
    {
        case 1:
            strcpy(DatosArticulo.temporadaCosecha, "Primavera");
            break;
        case 2:
            strcpy(DatosArticulo.temporadaCosecha, "Verano");
            break;
        case 3:
            strcpy(DatosArticulo.temporadaCosecha, "Otoño");
            break;
        case 4:
            strcpy(DatosArticulo.temporadaCosecha, "Invierno");
            break;
    }

    do
    {
        printf("\nInventario del articulo [Mayor o igual a 0] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosArticulo.inventario) != 1 || !intMoreThanZero(&DatosArticulo.inventario, true))
        {
            isInvalid = true;
            printf("\nERROR: Cantidad invalida.\n");
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nPrecio de venta [Mayor a 0] ~ ");
        fflush(stdin);
        if (scanf("%f", &DatosArticulo.precioVenta) != 1 || !floatMoreThanZero(&DatosArticulo.precioVenta, false))
        {
            isInvalid = true;
            printf("\nERROR: Precio invalido.\n");
        }
        else
            isInvalid = false;          

    } while (isInvalid);

    do
    {
        do
        {
            printf("\nIngrese la clave del mercado [ %d/10 mercados guardados] ~ ", mercados);
            fflush(stdin);
            if(scanf("%d", &DatosArticulo.clavesMercados[mercados]) != 1 || !isInIntRange(&DatosArticulo.clavesMercados[mercados], 1, 100))
            {
                isInvalid = true;
                printf("\nERROR: Clave de mercado invalida.\n");
            }
            else if (!existeClave(3, &DatosArticulo.clavesMercados[mercados]))
            {
                isInvalid = true;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el mercado? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';

                    if(opcionRegistrarInvalida)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Mercados.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaMercado(archivo_NuevoRegistro);

                        fclose(archivo_NuevoRegistro);

                        if(!existeClave(3, &DatosArticulo.clavesMercados[mercados]))
                            isInvalid = false;
                        else
                            printf("\nLa clave ingresada y el mercado registrado no coinciden.\n");
                    }
                }
            }
            else    
                isInvalid = false;

        } while (isInvalid);
        
        mercados++;

        printf("\nIngresar información de otro mercado? [ %d/10 mercados guardados ] ~ ", mercados);
        fflush(stdin);
        scanf("%c", &ingresarMas);
        
    } while (mercados < 10 && ingresarMas == 'S');

    do
    {
        do
        {
            printf("\nIngrese la clave del insumo [ %d/10 insumos guardados] ~ ", insumos);
            fflush(stdin);

            if(scanf("%d", &DatosArticulo.clavesInsumos[insumos]) != 1 || !isInIntRange(&DatosArticulo.clavesInsumos[insumos], 1, 100))
            {
                isInvalid = true;
                printf("\nERROR: Clave de insumo invalida.\n");
            }
            else if (!existeClave(2, &DatosArticulo.clavesInsumos[insumos]))
            {
                isInvalid = true;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el insumo? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    
                    opcionRegistrarInvalida = opcionRegistrar !='s' && opcionRegistrar != 'n';

                    if(opcionRegistrarInvalida)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Insumos.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaInsumo(archivo_NuevoRegistro);
                        fclose(archivo_NuevoRegistro);

                        if(!existeClave(2, &DatosArticulo.clavesInsumos[insumos]))
                            isInvalid = false;
                        else
                            printf("\nLa clave ingresada y el insumo registrado no coinciden.\n");
                    }
                }
            }
            else
                isInvalid = false;
                
        } while (isInvalid);

        insumos++;
        
        printf("\nIngresar informacion de otro insumo? [ %d/10 insumos guardados ] ~ ", insumos);
        fflush(stdin);
        scanf("%c", &ingresarMas);

        ingresarMas = tolower(ingresarMas);
        
    } while (insumos < 10 && ingresarMas == 's');

    
    DatosArticulo.costoProduccion = obtenerCosto(DatosArticulo.clavesInsumos, &insumos);

    fseek(archivoArticulos, (DatosArticulo.clave - 1) * sizeof(DatosArticulo), SEEK_SET);
    fwrite(&DatosArticulo, sizeof(DatosArticulo), 1, archivoArticulos);
}

void lecturaInsumo(FILE *archivoInsumos)
{
    FILE *archivo_NuevoRegistro;
    struct infoInsumo DatosInsumo;
    bool isInvalid, opcionRegistrarInvalida;
    char ingresarMas, opcionRegistrar;
    int i, proveedores = 0;

    do
    {
        printf("\nIngrese la clave del insumo [1 - 100] ~ ");
        fflush(stdin);
        if (scanf("%d", &DatosInsumo.clave) != 1 || !isInIntRange(&DatosInsumo.clave, 1, 100))
        {
            isInvalid = true;
            printf("\nERROR: Clave de insumo invalida.\n");
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nDescripcion del insumo [50 caracteres max.] ~ ");
        fflush(stdin);
        fgets(DatosInsumo.descripcion, sizeof(DatosInsumo.descripcion), stdin);

        isInvalid = !minStringLength(DatosInsumo.descripcion, 10);

        if (isInvalid)
            printf("\nERROR: Descripcion invalida, [10 - 50 caracteres].\n");
        
    } while (isInvalid);

    do
    {
        printf("\nPunto de reorden [Mayor a 0] ~ ");
        fflush(stdin);
        if (scanf("%d", &DatosInsumo.puntoReorden) != 1 || !intMoreThanZero(&DatosInsumo.puntoReorden, false))
        {
            isInvalid = true;
            printf("\nERROR: Cantidad invalida.\n");
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nInventario del insumo [Mayor o igual a 0] ~ ");
        fflush(stdin);
        if (scanf("%d", &DatosInsumo.inventario) != 1 || !intMoreThanZero(&DatosInsumo.inventario, true))
        {
            isInvalid = true;
            printf("\nERROR: Cantidad invalida.\n");
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        do
        {
            printf("\nIngrese la clave del proveedor [ %d/10 proveedores guardados] ~ ", proveedores);
            fflush(stdin);
            
            if(scanf("%d", &DatosInsumo.clavesProveedores[proveedores]) != 1 || !isInIntRange(&DatosInsumo.clavesProveedores[proveedores], 1, 100))
            {
                isInvalid = true;
                printf("\nERROR: Clave de proveedor invalida.\n");
            }
            else if (!existeClave(5, &DatosInsumo.clavesProveedores[proveedores]))
            {
                isInvalid = true;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el proveedor? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';

                    if (opcionRegistrarInvalida)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while (opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Proveedores.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaProveedor(archivo_NuevoRegistro);
                        fclose(archivo_NuevoRegistro);

                        if (existeClave(5, &DatosInsumo.clavesProveedores[proveedores]))
                            isInvalid = false;
                        else
                            printf("\nLa clave ingresada y el proveedor registrado no coinciden.\n");
                    }
                }
            }
            else    
                isInvalid = false;

        } while (isInvalid);
        
        proveedores++;

        printf("\nIngresar información de otro proveedor? [ %d/10 proveedores guardados ] ~ ", proveedores);
        fflush(stdin);
        scanf("%c", &ingresarMas);
        
    } while (proveedores < 10 && ingresarMas == 'S');


    printf("\n\tLECTURA DE PRECIOS POR PROVEEDOR\n");

    for( i = 0; i < proveedores; i++)
    {
        printf("\nPrecio del insumo para el proveedor %d: $", DatosInsumo.clavesProveedores[i]);

        do
        {
            if (scanf("%f", &DatosInsumo.precioSurtido[i]) != 1 || !floatMoreThanZero(&DatosInsumo.precioSurtido[i], false))
            {
                isInvalid = true;
                printf("\nERROR: Precio invalido.\n");
            }
            else
                isInvalid = false;          

        } while (isInvalid);
    }

    fseek(archivoInsumos, (DatosInsumo.clave - 1) * sizeof(DatosInsumo), SEEK_SET);
    fwrite(&DatosInsumo, sizeof(DatosInsumo), 1, archivoInsumos);
}

void lecturaMercado(FILE *archivoMercados)
{
    struct infoMercado DatosMercado;
    int distanciaCaracteres;
    bool isInvalid, fechaInvalida;

    printf("\n\n\t##### DATOS DE MERCADO #####");

    do
    {
        printf("\nClave del mercado [1 - 1000] ~ ");
        if (scanf("%d", &DatosMercado.clave) != 1 || !isInIntRange(&DatosMercado.clave, 1, 1000))
            isInvalid = true;
        else
            isInvalid = false;
        if (isInvalid)
            printf("\nERROR: Clave de mercado invalida.\n");
    } while (isInvalid);

    printf("\n\n\t----- NOMBRE COMPLETO DEL CLIENTE -----");

    do
    {
        do
        {
            printf("Nombres [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosMercado.datosPersonales.nombres, sizeof(DatosMercado.datosPersonales.nombres), stdin);
            isInvalid = !isAlphabetic(DatosMercado.datosPersonales.nombres, false);

            if (isInvalid)
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        do
        {
            printf("Apellido Paterno [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosMercado.datosPersonales.apellidoPaterno, sizeof(DatosMercado.datosPersonales.apellidoPaterno), stdin);
            isInvalid = !isAlphabetic(DatosMercado.datosPersonales.apellidoPaterno, false);

            if (isInvalid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        do
        {
            printf("Apellido Materno [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosMercado.datosPersonales.apellidoMaterno, sizeof(DatosMercado.datosPersonales.apellidoMaterno), stdin);
            isInvalid = !isAlphabetic(DatosMercado.datosPersonales.apellidoMaterno, false);

            if (isInvalid)
                printf("ERROR: Apellido materno invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        distanciaCaracteres = lengthChar(DatosMercado.datosPersonales.nombres) +
                              lengthChar(DatosMercado.datosPersonales.apellidoMaterno) +
                              lengthChar(DatosMercado.datosPersonales.apellidoPaterno);
        isInvalid = distanciaCaracteres <= 20;
        if (isInvalid)
            printf("ERROR: La distancia de caracteres es MENOR o IGUAL a 20. \n");
    } while (isInvalid);

    printf("\n\n\t-------------------------------------------------------------\n");

    do
    {
        printf("\nCorreo electronico del mercado [50 caracteres maximo] ~ ");
        fgets(DatosMercado.datosPersonales.correo, sizeof(DatosMercado.datosPersonales.correo), stdin);
        isInvalid = !esCorreoElectronico(DatosMercado.datosPersonales.correo);
        if (isInvalid)
            printf("\nERROR: Correo electronico invalido.\n");
    } while (isInvalid);

    do
    {
        printf("Descuento para el mercado [Entre 0 y 1] ~ ");
        if (scanf("%f", &DatosMercado.descuento) != 1 || !isInFloatRange(&DatosMercado.descuento, 0, 1))
        {
            printf("\nERROR: Valor invalido para el descuento.\n");
            isInvalid = true;
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {        
        printf("\n\n\t##### FECHA DE NACIMIENTO DEL CLIENTE #####");

        do
        {
            printf("Año [1990 - 2024] ~ ");
            if (scanf("%d", &DatosMercado.datosPersonales.year) != 1 || !isInIntRange(&DatosMercado.datosPersonales.year, 1990, 2024))
            {
                printf("\nERROR: Anio invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        do
        {
            printf("Mes [1- 12] ~ ");
            if (scanf("%d", &DatosMercado.datosPersonales.month) != 1 || !isInIntRange(&DatosMercado.datosPersonales.month, 1, 12))
            {
                printf("\nERROR: Mes invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        do
        {
            printf("Dia [1 - 31] ~ ");
            if (scanf("%d", &DatosMercado.datosPersonales.day) != 1 || !isInIntRange(&DatosMercado.datosPersonales.day, 1, 31))
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosMercado.datosPersonales.day, &DatosMercado.datosPersonales.month, &DatosMercado.datosPersonales.year);

        if (fechaInvalida)
            printf("\nERROR: Fecha invalida.\n");
    } while (fechaInvalida);

    printf("\n\n##### DOMICILIO DEL MERCADO #####");

    do
    {
        printf("Calle [Solo letras, espacios y numeros] ~ ");
        fflush(stdin);
        fgets(DatosMercado.datosPersonales.calle, sizeof(DatosMercado.datosPersonales.calle), stdin);
        isInvalid = !isAlphabetic(DatosMercado.datosPersonales.calle, true);
        if (isInvalid)
            printf("ERROR: Calle invalida.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Numero [Entero mayor a 0] ~ ");
        if (scanf("%d", &DatosMercado.datosPersonales.numeroDomicilio) != 1 || !intMoreThanZero(&DatosMercado.datosPersonales.numeroDomicilio, false))
        {
            isInvalid = true;
            printf("ERROR: Numero invalido.(Entero mayor a 0) \n");
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {
        printf("Colonia ~ ");
        fflush(stdin);
        fgets(DatosMercado.datosPersonales.colonia, sizeof(DatosMercado.datosPersonales.colonia), stdin);
        isInvalid = !isAlphabetic(DatosMercado.datosPersonales.colonia, true);
        if (isInvalid)
            printf("ERROR: Colonia invalida.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Municipio ~ ");
        fflush(stdin);
        fgets(DatosMercado.datosPersonales.municipio, sizeof(DatosMercado.datosPersonales.municipio), stdin);
        isInvalid = !isAlphabetic(DatosMercado.datosPersonales.municipio, false);
        if (isInvalid)
            printf("ERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Estado ~ ");
        fflush(stdin);
        fgets(DatosMercado.datosPersonales.estado, sizeof(DatosMercado.datosPersonales.estado), stdin);
        isInvalid = !isAlphabetic(DatosMercado.datosPersonales.estado, false);
        if (isInvalid)
            printf("ERROR: Estado invalido.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    fseek(archivoMercados, (DatosMercado.clave - 1) * sizeof(DatosMercado), SEEK_SET);
    fwrite(&DatosMercado, sizeof(DatosMercado), 1, archivoMercados);
}

void lecturaEmpleado(FILE *archivoEmpleados)
{
    struct infoEmpleado DatosEmpleado;
    int distanciaCaracteres;
    bool isInvalid, fechaInvalida;

    printf("\n\n\t##### DATOS DE EMPLEADO #####");

    do
    {
        printf("\nClave del empleado [1 - 1000] ~ ");
        if (scanf("%d", &DatosEmpleado.clave) != 1 || !isInIntRange(&DatosEmpleado.clave, 1, 1000))
            isInvalid = true;
        else
            isInvalid = false;
        if (isInvalid)
            printf("\nERROR: Clave de empleado invalida.\n");
    } while (isInvalid);

    printf("\n\n\t----- NOMBRE COMPLETO DEL EMPLEADO -----");

    do
    {
        do
        {
            printf("Nombres [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.nombres, sizeof(DatosEmpleado.datosPersonales.nombres), stdin);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.nombres, false);

            if (isInvalid)
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        do
        {
            printf("Apellido Paterno [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.apellidoPaterno, sizeof(DatosEmpleado.datosPersonales.apellidoPaterno), stdin);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.apellidoPaterno, false);

            if (isInvalid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        do
        {
            printf("Apellido Materno [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.apellidoMaterno, sizeof(DatosEmpleado.datosPersonales.apellidoMaterno), stdin);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.apellidoMaterno, false);

            if (isInvalid)
                printf("ERROR: Apellido materno invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        distanciaCaracteres = lengthChar(DatosEmpleado.datosPersonales.nombres) +
                              lengthChar(DatosEmpleado.datosPersonales.apellidoMaterno) +
                              lengthChar(DatosEmpleado.datosPersonales.apellidoPaterno);
        isInvalid = distanciaCaracteres <= 20;
        if (isInvalid)
            printf("ERROR: La distancia de caracteres es MENOR o IGUAL a 20. \n");
    } while (isInvalid);

    printf("\n\n\t-------------------------------------------------------------\n");

    do
    {
        printf("\nCorreo electronico del empleado [50 caracteres maximo] ~ ");
        fgets(DatosEmpleado.datosPersonales.correo, sizeof(DatosEmpleado.datosPersonales.correo), stdin);
        isInvalid = !esCorreoElectronico(DatosEmpleado.datosPersonales.correo);
        if (isInvalid)
            printf("\nERROR: Correo electronico invalido.\n");
    } while (isInvalid);

    do
    {
        printf("Comision para el empleado [Entre 0 y 1] ~ ");
        if (scanf("%f", &DatosEmpleado.comision) != 1 || !isInFloatRange(&DatosEmpleado.comision, 0, 1))
        {
            printf("\nERROR: Valor invalido para la comision.\n");
            isInvalid = true;
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {        
        printf("\n\n\t##### FECHA DE CONTRATACION DEL EMPLEADO #####");

        do
        {
            printf("Año [1990 - 2024] ~ ");
            if (scanf("%d", &DatosEmpleado.datosPersonales.year) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.year, 1990, 2024))
            {
                printf("\nERROR: Anio invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        do
        {
            printf("Mes [1- 12] ~ ");
            if (scanf("%d", &DatosEmpleado.datosPersonales.month) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.month, 1, 12))
            {
                printf("\nERROR: Mes invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        do
        {
            printf("Dia [1 - 31] ~ ");
            if (scanf("%d", &DatosEmpleado.datosPersonales.day) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.day, 1, 31))
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosEmpleado.datosPersonales.day, &DatosEmpleado.datosPersonales.month, &DatosEmpleado.datosPersonales.year);

        if (fechaInvalida)
            printf("\nERROR: Fecha invalida.\n");
    } while (fechaInvalida);

    printf("\n\n##### DOMICILIO DEL EMPLEADO #####");

    do
    {
        printf("Calle [Solo letras, espacios y numeros] ~ ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.calle, sizeof(DatosEmpleado.datosPersonales.calle), stdin);
        isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.calle, true);
        if (isInvalid)
            printf("ERROR: Calle invalida.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Numero [Entero mayor a 0] ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.numeroDomicilio) != 1 || !intMoreThanZero(&DatosEmpleado.datosPersonales.numeroDomicilio, false))
        {
            isInvalid = true;
            printf("ERROR: Numero invalido.(Entero mayor a 0) \n");
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {
        printf("Colonia ~ ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.colonia, sizeof(DatosEmpleado.datosPersonales.colonia), stdin);
        isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.colonia, true);
        if (isInvalid)
            printf("ERROR: Colonia invalida.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Municipio ~ ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.municipio, sizeof(DatosEmpleado.datosPersonales.municipio), stdin);
        isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.municipio, false);
        if (isInvalid)
            printf("ERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Estado ~ ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.estado, sizeof(DatosEmpleado.datosPersonales.estado), stdin);
        isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.estado, false);
        if (isInvalid)
            printf("ERROR: Estado invalido.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    fseek(archivoEmpleados, (DatosEmpleado.clave - 1) * sizeof(DatosEmpleado), SEEK_SET);
    fwrite(&DatosEmpleado, sizeof(DatosEmpleado), 1, archivoEmpleados);
}

void lecturaProveedor(FILE *archivoProveedores)
{
    struct infoProveedor DatosProveedor;
    int distanciaCaracteres;
    bool isInvalid, fechaInvalida;

    printf("\n\n\t##### DATOS DE PROVEEDOR #####");

    do
    {
        printf("\nClave del proveedor [1 - 1000] ~ ");
        if (scanf("%d", &DatosProveedor.clave) != 1 || !isInIntRange(&DatosProveedor.clave, 1, 1000))
            isInvalid = true;
        else
            isInvalid = false;
        if (isInvalid)
            printf("\nERROR: Clave de empleado invalida.\n");
    } while (isInvalid);

    printf("\n\n\t----- NOMBRE COMPLETO DEL PROVEEDOR -----");

    do
    {
        do
        {
            printf("Nombres [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosProveedor.datosPersonales.nombres, sizeof(DatosProveedor.datosPersonales.nombres), stdin);

            isInvalid = !isAlphabetic(Dato sProveedor.datosPersonales.nombres, false);

            if (isInvalid)
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");

        } while (isInvalid);

        do
        {
            printf("Apellido Paterno [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosProveedor.datosPersonales.apellidoPaterno, sizeof(DatosProveedor.datosPersonales.apellidoPaterno), stdin);

            isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.apellidoPaterno, false);

            if (isInvalid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");

        } while (isInvalid);

        do
        {
            printf("Apellido Materno [Maximo 30 caracteres]: ");
            fflush(stdin);
            fgets(DatosProveedor.datosPersonales.apellidoMaterno, sizeof(DatosProveedor.datosPersonales.apellidoMaterno), stdin);
            isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.apellidoMaterno, false);
            if (isInvalid)
                printf("ERROR: Apellido materno invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        distanciaCaracteres = lengthChar(DatosProveedor.datosPersonales.nombres) +
                              lengthChar(DatosProveedor.datosPersonales.apellidoMaterno) +
                              lengthChar(DatosProveedor.datosPersonales.apellidoPaterno);
        isInvalid = distanciaCaracteres <= 20;
        if (isInvalid)
            printf("ERROR: La distancia de caracteres es MENOR o IGUAL a 20. \n");
    } while (isInvalid);

    printf("\n\n\t-------------------------------------------------------------\n");

    do
    {
        printf("\nCorreo electronico del proveedor [50 caracteres maximo] ~ ");
        fgets(DatosProveedor.datosPersonales.correo, sizeof(DatosProveedor.datosPersonales.correo), stdin);
        isInvalid = !esCorreoElectronico(DatosProveedor.datosPersonales.correo);
        if (isInvalid)
            printf("\nERROR: Correo electronico invalido.\n");
    } while (isInvalid);

    do
    {
        printf("Descuento para el proveedor [Entre 0 y 1] ~ ");
        if (scanf("%f", &DatosProveedor.descuento) != 1 || !isInFloatRange(&DatosProveedor.descuento, 0, 1))
        {
            printf("\nERROR: Valor invalido para el descuento.\n");
            isInvalid = true;
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {        
        printf("\n\n\t##### FECHA DE NACIMIENTO DEL PROVEEDOR #####");

        do
        {
            printf("Año [1990 - 2024] ~ ");
            if (scanf("%d", &DatosProveedor.datosPersonales.year) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.year, 1990, 2024))
            {
                printf("\nERROR: Anio invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        do
        {
            printf("Mes [1- 12] ~ ");
            if (scanf("%d", &DatosProveedor.datosPersonales.month) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.month, 1, 12))
            {
                printf("\nERROR: Mes invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        do
        {
            printf("Dia [1 - 31] ~ ");
            if (scanf("%d", &DatosProveedor.datosPersonales.day) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.day, 1, 31))
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosProveedor.datosPersonales.day, &DatosProveedor.datosPersonales.month, &DatosProveedor.datosPersonales.year);

        if (fechaInvalida)
            printf("\nERROR: Fecha invalida.\n");

    } while (fechaInvalida);

    printf("\n\n##### DOMICILIO DEL PROVEEDOR #####");

    do
    {
        printf("Calle [Solo letras, espacios y numeros] ~ ");
        fflush(stdin);
        fgets(DatosProveedor.datosPersonales.calle, sizeof(DatosProveedor.datosPersonales.calle), stdin);
        isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.calle, true);
        if (isInvalid)
            printf("ERROR: Calle invalida.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Numero [Entero mayor a 0] ~ ");
        if (scanf("%d", &DatosProveedor.datosPersonales.numeroDomicilio) != 1 || !intMoreThanZero(&DatosProveedor.datosPersonales.numeroDomicilio, false))
        {
            isInvalid = true;
            printf("ERROR: Numero invalido.(Entero mayor a 0) \n");
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {
        printf("Colonia ~ ");
        fflush(stdin);
        fgets(DatosProveedor.datosPersonales.colonia, sizeof(DatosProveedor.datosPersonales.colonia), stdin);
        isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.colonia, true);
        if (isInvalid)
            printf("ERROR: Colonia invalida.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Municipio ~ ");
        fflush(stdin);
        fgets(DatosProveedor.datosPersonales.municipio, sizeof(DatosProveedor.datosPersonales.municipio), stdin);
        isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.municipio, false);
        if (isInvalid)
            printf("ERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Estado ~ ");
        fflush(stdin);
        fgets(DatosProveedor.datosPersonales.estado, sizeof(DatosProveedor.datosPersonales.estado), stdin);
        isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.estado, false);
        if (isInvalid)
            printf("ERROR: Estado invalido.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    fseek(archivoProveedores, (DatosProveedor.clave - 1) * sizeof(DatosProveedor), SEEK_SET);
    fwrite(&DatosProveedor, sizeof(DatosProveedor), 1, archivoProveedores);
}