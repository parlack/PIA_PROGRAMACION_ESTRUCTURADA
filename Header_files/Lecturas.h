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
    printf("LECTURA MERCADOS");
}

void lecturaEmpleado(FILE *archivoEmpleados)
{
    struct infoEmpleado DatosEmpleado;
    int distanciaCaracteres;
    bool isInvalid;

    do
    {
        printf("\nIngrese la clave del empleado [1 - 1000] ~ ");
        if (scanf("%d", &DatosEmpleado.clave) != 1 || !isInIntRange(&DatosEmpleado.clave, 1, 1000))
            isInvalid = true;
        else
            isInvalid = false;
        if (isInvalid)
            printf("\nERROR: Clave de empleado invalida.\n");
    } while (isInvalid);

    do
    {
        do
        {
            printf("Ingrese los nombres del empleado (Sin apellidos): ");
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.nombres, sizeof(DatosEmpleado.datosPersonales.nombres), stdin);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.nombres, false);
            if (isInvalid)
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        do
        {
            printf("Ingrese apellido paterno del empleado: ");
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.apellidoPaterno, sizeof(DatosEmpleado.datosPersonales.apellidoPaterno), stdin);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.apellidoPaterno, false);
            if (isInvalid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
        } while (isInvalid);

        do
        {
            printf("Ingrese apellido materno del empleado: ");
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
        printf("\nCorreo electronico del empleado [50 caracteres maximo] ~ ");
        fgets(DatosEmpleado.datosPersonales.correo, sizeof(DatosEmpleado.datosPersonales.correo), stdin);
        isInvalid = !esCorreoElectronico(DatosEmpleado.datosPersonales.correo);
        if (isInvalid)
            printf("\nERROR: Correo electronico invalido.\n");
    } while (isInvalid);

    do
    {
        printf("Comision del empleado [Entre 0 y 1] ~ ");
        if (scanf("%1.2f", &DatosEmpleado.comision) != 1 || !isInFloatRange(&DatosEmpleado.comision, 0, 1))
        {
            printf("\nERROR: Comision invalida.\n");
            isInvalid = true;
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {
        printf("Año de contratacion del empleado [formato YYYY] ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.year) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.year, 1990, 2024))
        {
            printf("\nERROR: Año invalido.\n");
            isInvalid = true;
        }
        else
            isInvalid = false;
    } while (isInvalid);

    do
    {
        printf("Mes de contratacion [formato MM] ~ ");
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
        printf("Dia de contratacion [formato dd] ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.day) != 1 || !isValidDate(&DatosEmpleado.datosPersonales.day, &DatosEmpleado.datosPersonales.month, &DatosEmpleado.datosPersonales.year))
        {
            printf("\nERROR: Día de contratación invalido.\n");
            isInvalid = true;
        }
        else
            isInvalid = false;
    } while (isInvalid);

    printf("\n\n\tDOMICILIO DEL EMPLEADO");

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
        printf("Colonia del empleado: ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.colonia, sizeof(DatosEmpleado.datosPersonales.colonia), stdin);
        isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.colonia, true);
        if (isInvalid)
            printf("ERROR: Colonia invalida.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Municipio del empleado: ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.municipio, sizeof(DatosEmpleado.datosPersonales.municipio), stdin);
        isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.municipio, false);
        if (isInvalid)
            printf("ERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
    } while (isInvalid);

    do
    {
        printf("Estado del empleado: ");
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
    printf("LECTURA PROVEEDORES");
}