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

                        if(existeClave(3, &DatosArticulo.clavesMercados[mercados]))
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

                        if(existeClave(2, &DatosArticulo.clavesInsumos[insumos]))
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
    int distanciaCaracteres, i;
    bool isInvalid, fechaInvalida;

    printf("\n\n\t##### DATOS DE MERCADO #####");

    do
    {
        printf("\nClave del mercado [1 - 100] ~ ");
        if (scanf("%d", &DatosMercado.clave) != 1 || !isInIntRange(&DatosMercado.clave, 1, 1000))
        {
            isInvalid = true;
            printf("\nERROR: Clave de mercado invalida.\n");
        }else
            isInvalid = false;
            
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
            if (scanf("%d", &DatosMercado.datosPersonales.yearBirth) != 1 || !isInIntRange(&DatosMercado.datosPersonales.yearBirth, 1990, 2024))
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
            if (scanf("%d", &DatosMercado.datosPersonales.monthBirth) != 1 || !isInIntRange(&DatosMercado.datosPersonales.monthBirth, 1, 12))
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
            if (scanf("%d", &DatosMercado.datosPersonales.dayBirth) != 1 || !isInIntRange(&DatosMercado.datosPersonales.dayBirth, 1, 31))
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosMercado.datosPersonales.dayBirth, &DatosMercado.datosPersonales.monthBirth, &DatosMercado.datosPersonales.yearBirth);

        if (fechaInvalida)
            printf("\nERROR: Fecha invalida.\n");
    } while (fechaInvalida);


    do
    {
        printf("RFC: ~ ");
        if (scanf("%d", &DatosMercado.datosPersonales.RFC) != 1 || !isAlphabetic(DatosMercado.datosPersonales.RFC, true))
        {
            printf("\nERROR: RFC INVALIDO.\n");
            isInvalid = true;
        }
        else
        {
            for (i = 0; i < strlen(DatosMercado.datosPersonales.RFC); i++) 
                 DatosMercado.datosPersonales.RFC[i] = toupper(DatosMercado.datosPersonales.RFC[i]);
            if(validarRFC(&DatosMercado.datosPersonales))
            {
                isInvalid = false;
                printf("\nERROR: EL RFC NO COINCIDE CON LOS DATOS PROPORCIONADOS.\n");
            }
            else
                isInvalid = true;
        }
    } while (isInvalid);


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
    int distanciaCaracteres, i;
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


    do
    {        
        printf("\n\n\t##### FECHA DE NACIMIENTO DEL EMPLEADO #####");

        do
        {
            printf("Año [1990 - 2024] ~ ");
            if (scanf("%d", &DatosEmpleado.datosPersonales.yearBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.yearBirth, 1990, 2024))
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
            if (scanf("%d", &DatosEmpleado.datosPersonales.monthBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.monthBirth, 1, 12))
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
            if (scanf("%d", &DatosEmpleado.datosPersonales.dayBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.dayBirth, 1, 31))
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosEmpleado.datosPersonales.dayBirth, &DatosEmpleado.datosPersonales.monthBirth, &DatosEmpleado.datosPersonales.yearBirth);

        if (fechaInvalida)
            printf("\nERROR: Fecha invalida.\n");

    } while (fechaInvalida);


    printf("\n\n\t-------------------------------------------------------------\n");

    printf("\n\n##### RFC DEL EMPLEADO #####");

    do
    {
        printf("RFC ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.RFC) != 1 || !isAlphabetic(DatosEmpleado.datosPersonales.RFC, true))
        {
            printf("\nERROR: RFC INVALIDO.\n");
            isInvalid = true;
        }
        else
        {
            for (i = 0; i < strlen(DatosEmpleado.datosPersonales.RFC); i++) 
                 DatosEmpleado.datosPersonales.RFC[i] = toupper(DatosEmpleado.datosPersonales.RFC[i]);
            if(validarRFC(&DatosEmpleado.datosPersonales))
            {
                isInvalid = false;
                printf("\nERROR: EL RFC NO COINCIDE CON LOS DATOS PROPORCIONADOS.\n");
            }
            else
                isInvalid = true;
        }
    } while (isInvalid);

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
            if (scanf("%d", &DatosEmpleado.datosPersonales.yearBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.yearBirth, 1990, 2024))
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
            if (scanf("%d", &DatosEmpleado.datosPersonales.monthBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.monthBirth, 1, 12))
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
            if (scanf("%d", &DatosEmpleado.datosPersonales.dayBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.dayBirth, 1, 31))
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosEmpleado.datosPersonales.dayBirth, &DatosEmpleado.datosPersonales.dayBirth, &DatosEmpleado.datosPersonales.dayBirth);

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
    int distanciaCaracteres,i;
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

            isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.nombres, false);

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
            if (scanf("%d", &DatosProveedor.datosPersonales.yearBirth) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.yearBirth, 1990, 2024))
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
            if (scanf("%d", &DatosProveedor.datosPersonales.monthBirth) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.monthBirth, 1, 12))
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
            if (scanf("%d", &DatosProveedor.datosPersonales.dayBirth) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.dayBirth, 1, 31))
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosProveedor.datosPersonales.dayBirth, &DatosProveedor.datosPersonales.monthBirth, &DatosProveedor.datosPersonales.yearBirth);

        if (fechaInvalida)
            printf("\nERROR: Fecha invalida.\n");

    } while (fechaInvalida);
    
    printf("\n\n##### RFC DEL PROVEEDOR #####");

    do
    {
        printf("RFC: ~ ");
        if (scanf("%d", &DatosProveedor.datosPersonales.RFC) != 1 || !isAlphabetic(DatosProveedor.datosPersonales.RFC, true))
        {
            printf("\nERROR: RFC INVALIDO.\n");
            isInvalid = true;
        }
        else
        {
            for (i = 0; i < strlen(DatosProveedor.datosPersonales.RFC); i++) 
                 DatosProveedor.datosPersonales.RFC[i] = toupper(DatosProveedor.datosPersonales.RFC[i]);
            if(validarRFC(&DatosProveedor.datosPersonales))
            {
                isInvalid = false;
                printf("\nERROR: EL RFC NO COINCIDE CON LOS DATOS PROPORCIONADOS.\n");
            }
            else
                isInvalid = true;
        }
    } while (isInvalid);


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

void lecturaVentas(FILE *archivoVentas)
{
    FILE *archivo_NuevoRegistro;
    int inventarioActual;
    struct infoVenta DatosVentas;
    bool isInvalid, opcionRegistrarInvalida;
    char agregarMasArticulos, opcionRegistrar;
    float precioUnitario, subtotalPorArticulo;
    DatosVentas.precioTotal = 0;

    time_t t = time(NULL);
    struct tm *fechaActual = localtime(&t);

    int anioActual = fechaActual->tm_year + 1900;
    int mesActual = fechaActual->tm_mon + 1;
    int diaActual = fechaActual->tm_mday;

    do
    {
        printf("\nClave del empleado [1 - 1000] ~ ");
        if(scanf("%d", &DatosVentas.claveEmpleado) != 1 || !isInIntRange(&DatosVentas.claveEmpleado, 1, 1000))
        {
            isInvalid = true;
            printf("\nERROR: Clave de empleado invalida.\n");
        }
        else if (!existeClave(4, &DatosVentas.claveEmpleado))
        {
            isInvalid = true;

            do
            {
                printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el empleado? [s/n]");
                fflush(stdin);
                scanf("%c", &opcionRegistrar);

                opcionRegistrar = tolower(opcionRegistrar);
                opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';

                if(opcionRegistrarInvalida)
                    printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

            } while(opcionRegistrarInvalida);
            
            if(opcionRegistrar == 's')
            {
                if((archivo_NuevoRegistro = fopen("./Data_files/Empleados.dat","rb+")) == NULL)
                    printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                else
                {
                    lecturaEmpleado(archivo_NuevoRegistro);

                    fclose(archivo_NuevoRegistro);

                    if(existeClave(4, &DatosVentas.claveEmpleado))
                        isInvalid = false;
                    else
                        printf("\nLa clave ingresada y el empleado registrado no coinciden, ingresala de nuevo.\n");
                }
            }
        }
        else
            isInvalid = false;
            
    } while (isInvalid);

    do
    {
        printf("\nClave del mercado [1 - 100] ~ ");
        if(scanf("%d", &DatosVentas.claveMercado) != 1 || !isInIntRange(&DatosVentas.claveMercado, 1, 100))
        {
            isInvalid = true;
            printf("\nERROR: Clave de mercado invalida.\n");
        }
        else if (!existeClave(3, &DatosVentas.claveMercado))
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

                    if(existeClave(3, &DatosVentas.claveMercado))
                        isInvalid = false;
                    else
                        printf("\nLa clave ingresada y el mercado registrado no coinciden, ingresala de nuevo.\n");
                }
            }
        }
        else    
            isInvalid = false;
            
    } while (isInvalid);


    fprintf(archivoVentas, "%d-%d-%d-%d-%d", 
                            DatosVentas.claveMercado, 
                            DatosVentas.claveEmpleado,
                            diaActual, mesActual, anioActual);

    do
    {
        precioUnitario = 0;
        subtotalPorArticulo = 0;

        do
        {
            printf("\nIngrese la clave del articulo [1 - 1000] ~ ");
            fflush(stdin);

            if(scanf("%d", &DatosVentas.claveArticulo) != 1 || !isInIntRange(&DatosVentas.claveArticulo, 1, 100))
            {
                isInvalid = true;
                printf("\nERROR: Clave de articulo invalida.\n");
            }
            else if (!existeClave(1, &DatosVentas.claveArticulo) || !verificarInventario(&DatosVentas.claveArticulo, 1, &precioUnitario, false))
            {
                isInvalid = true;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el articulo? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';

                    if(opcionRegistrarInvalida)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Articulos.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaArticulo(archivo_NuevoRegistro);

                        fclose(archivo_NuevoRegistro);

                        if(existeClave(1, &DatosVentas.claveArticulo))
                            isInvalid = false;
                        else
                            printf("\nLa clave ingresada y el articulo registrado no coinciden, ingresala de nuevo.\n");
                    }
                }
            }
            else    
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("\nCantidad del producto [Mayor a 0] ~ ");
            fflush(stdin);

            if(scanf("%d", &DatosVentas.cantidad) != 1 || !intMoreThanZero(&DatosVentas.cantidad, false))
            {
                isInvalid = true;
                printf("\nERROR: Cantidad invalida.\n");
            } 
            else if (!verificarInventario(&DatosVentas.claveArticulo, &DatosVentas.cantidad, &precioUnitario, true))
            {
                isInvalid = true;
                printf("\nLa cantidad ingresada supera al inventario actual de este articulo, ingresa otra cantidad.\n");
            }
            else
                isInvalid = false;

        } while (isInvalid);

        subtotalPorArticulo = precioUnitario * DatosVentas.cantidad;

        printf("\nPrecio unitario del articulo: %.2f\n", precioUnitario);
        printf("Subtotal de este articulo: %.2f\n", subtotalPorArticulo);

        DatosVentas.precioTotal += subtotalPorArticulo;

        fprintf(archivoVentas, "#%d-%d", DatosVentas.claveArticulo, DatosVentas.cantidad);

        do
        {
            printf("\nDesea agregar mas articulos a la venta? [s/n]");
            fflush(stdin);
            scanf("%c", &agregarMasArticulos);

            if(agregarMasArticulos != 's' && agregarMasArticulos != 'n')
            {
                printf("\nERROR: Opci%cn inv%clida.\n", 162, 160);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);
        
    } while (agregarMasArticulos == 's');

    fprintf(archivoVentas, "♥%f$", DatosVentas.precioTotal);

    printf("\n----------------- PAGO TOTAL DE LA VENTA: %.2f\n", DatosVentas.precioTotal);
}

void lecturaCompras(FILE *archivoCompras)
{
    FILE *archivo_NuevoRegistro;
    struct infoCompra DatosCompra;
    bool isInvalid, opcionRegistrarInvalida;
    char agregarMasInsumos, opcionRegistrar;
    float precioUnitario, subtotalPorInsumo;
    DatosCompra.totalDeCompra = 0;

    do
    {
        printf("\nIngrese la clave del proveedor ~ ");
        fflush(stdin);
        
        if(scanf("%d", &DatosCompra.claveProveedor) != 1 || !isInIntRange(&DatosCompra.claveProveedor, 1, 100))
        {
            isInvalid = true;
            printf("\nERROR: Clave de proveedor invalida.\n");
        }
        else if (!existeClave(5, &DatosCompra.claveProveedor))
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

                    if (existeClave(5, &DatosCompra.claveProveedor))
                        isInvalid = false;
                    else
                        printf("\nLa clave ingresada y el proveedor registrado no coinciden.\n");
                }
            }
        }
        else    
            isInvalid = false;

    } while (isInvalid);

    fprintf(archivoCompras, "%d-%d", DatosCompra.claveProveedor, 0);

    do
    {
        precioUnitario = 0;
        subtotalPorInsumo = 0;

        do
        {
            printf("\nIngrese la clave del insumo [1 - 1000] ~ ");
            fflush(stdin);

            if(scanf("%d", &DatosCompra.claveInsumo) != 1 || !isInIntRange(&DatosCompra.claveInsumo, 1, 100))
            {
                isInvalid = true;
                printf("\nERROR: Clave de insumo invalida.\n");
            }
            else if (!existeClave(2, &DatosCompra.claveInsumo))
            {
                isInvalid = true;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el insumo? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';

                    if(opcionRegistrarInvalida)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Articulos.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaArticulo(archivo_NuevoRegistro);

                        fclose(archivo_NuevoRegistro);

                        if(existeClave(1, &DatosCompra.claveInsumo))
                            isInvalid = false;
                        else
                            printf("\nLa clave ingresada y el articulo registrado no coinciden, ingresala de nuevo.\n");
                    }
                }
            }
            else if (!esInsumoValido(&DatosCompra.claveProveedor, &DatosCompra.claveInsumo, &precioUnitario))
            {
                isInvalid = true;
                printf("\nEste insumo no tiene a este proveedor registrado.\n");
            }
            else    
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("\nCantidad del insumo [Mayor a 0] ~ ");
            fflush(stdin);

            if(scanf("%d", &DatosCompra.cantidad) != 1 || !intMoreThanZero(&DatosCompra.cantidad, false))
            {
                isInvalid = true;
                printf("\nERROR: Cantidad invalida.\n");
            } 
            else
                isInvalid = false;

        } while (isInvalid);

        subtotalPorInsumo = precioUnitario * DatosCompra.cantidad;

        printf("\nPrecio unitario del articulo: %.2f\n", precioUnitario);
        printf("Subtotal de este articulo: %.2f\n", subtotalPorInsumo);

        DatosCompra.totalDeCompra += subtotalPorInsumo;

        fprintf(archivoCompras, "#%d-%d", DatosCompra.claveInsumo, DatosCompra.cantidad);

        do
        {
            printf("\nDesea agregar mas insumos a la compra? [s/n]");
            fflush(stdin);
            scanf("%c", &agregarMasInsumos);

            if(agregarMasInsumos != 's' && agregarMasInsumos != 'n')
            {
                printf("\nERROR: Opci%cn inv%clida.\n", 162, 160);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);
        
    } while (agregarMasInsumos == 's');

    fprintf(archivoCompras, "♥%f$", DatosCompra.totalDeCompra);

    printf("\n----------------- PAGO TOTAL DE LA COMPRA: %.2f\n", DatosCompra.totalDeCompra);
}