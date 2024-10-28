#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Validations.h"

void lecturaArticulo(FILE *archivoArticulos)
{
    FILE *archivo_NuevoRegistro;
    struct infoArticulo DatosArticulo;
    bool isValid, isValid_opcionRegistrar;
    char ingresarMas, opcionRegistrar;
    int i, mercados = 0, insumos = 0, numeroTemporada;

    do
    {
        printf("\nIngrese la clave del articulo [1 - 1000] ~ ");
        fflush(stdin);
        if (scanf("%d", &DatosArticulo.clave) != 1 || !isInIntRange(&DatosArticulo.clave, 1, 1000))
        {
            isValid = false;
            printf("\nERROR: Clave de articulo invalida.\n");
        }
        else
            isValid = true;

    } while (!isValid);


    do
    {
        printf("\nDescripcion del articulo [50 caracteres max.] ~ ");
        fflush(stdin);
        fgets(DatosArticulo.descripcion, sizeof(DatosArticulo.descripcion), stdin);

        isValid = minStringLength(DatosArticulo.descripcion, 10);

        if (!isValid)
            printf("\nERROR: Descripcion invalida, [10 - 50 caracteres].\n");
        
    } while (!isValid);

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
            isValid = false;
            printf("\nERROR: Numero invalido.\n");
        }
        else
            isValid = true;

    } while (!isValid);
    
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
            isValid = false;
            printf("\nERROR: Numero invalido.\n");
        }
        else
            isValid = true;

    } while (!isValid);
    
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
            isValid = false;
            printf("\nERROR: Cantidad invalida.\n");
        }
        else
            isValid = true;

    } while (!isValid);

    do
    {
        printf("\nPrecio de venta [Mayor a 0] ~ ");
        fflush(stdin);
        if (scanf("%f", &DatosArticulo.precioVenta) != 1 || !floatMoreThanZero(&DatosArticulo.precioVenta, false))
        {
            isValid = false;
            printf("\nERROR: Precio invalido.\n");
        }
        else
            isValid = true;          

    } while (!isValid);

    do
    {
        do
        {
            printf("\nIngrese la clave del mercado [ %d/10 mercados guardados] ~ ", mercados);
            fflush(stdin);
            if(scanf("%d", &DatosArticulo.clavesMercados[mercados]) != 1 || !isInIntRange(&DatosArticulo.clavesMercados[mercados], 1, 100))
            {
                isValid = false;
                printf("\nERROR: Clave de mercado invalida.\n");
            }
            else if (!existeClave(3, &DatosArticulo.clavesMercados[mercados]))
            {
                isValid = false;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el mercado? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    isValid_opcionRegistrar = opcionRegistrar == 's' || opcionRegistrar == 'n';

                    if(!isValid_opcionRegistrar)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while(!isValid_opcionRegistrar);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Mercados.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaMercado(archivo_NuevoRegistro);

                        fclose(archivo_NuevoRegistro);

                        if(!existeClave(3, &DatosArticulo.clavesMercados[mercados]))
                            isValid = true;
                        else
                            printf("\nLa clave ingresada y el mercado registrado no coinciden.\n");
                    }
                }
            }
            else    
                isValid = true;

        } while (!isValid);
        
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
                isValid = false;
                printf("\nERROR: Clave de insumo invalida.\n");
            }
            else if (!existeClave(2, &DatosArticulo.clavesInsumos[insumos]))
            {
                isValid = false;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el insumo? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    
                    isValid_opcionRegistrar = opcionRegistrar =='s' || opcionRegistrar == 'n';

                    if(!isValid_opcionRegistrar)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while(!isValid_opcionRegistrar);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Insumos.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaInsumo(archivo_NuevoRegistro);
                        fclose(archivo_NuevoRegistro);

                        if(!existeClave(2, &DatosArticulo.clavesInsumos[insumos]))
                            isValid = true;
                        else
                            printf("\nLa clave ingresada y el insumo registrado no coinciden.\n");
                    }
                }
            }
            else
                isValid = true;
                
        } while (!isValid);

        insumos++;
        
        printf("\nIngresar informacion de otro insumo? [ %d/10 insumos guardados ] ~ ", insumos);
        fflush(stdin);
        scanf("%c", &ingresarMas);

        ingresarMas = tolower(ingresarMas);
        
    } while (insumos < 10 && ingresarMas == 's');

    /*
    DatosArticulo.costoProduccion = obtenerCosto(DatosArticulo.clavesInsumos);
    */

    fseek(archivoArticulos, (DatosArticulo.clave - 1) * sizeof(DatosArticulo), SEEK_SET);
    fwrite(&DatosArticulo, sizeof(DatosArticulo), 1, archivoArticulos);
}

void lecturaInsumo(FILE *archivoInsumos)
{
    FILE *archivo_NuevoRegistro;
    struct infoInsumo DatosInsumo;
    bool isValid, isValid_opcionRegistrar;
    char ingresarMas, opcionRegistrar;
    int i, proveedores = 0;

    do
    {
        printf("\nIngrese la clave del insumo [1 - 100] ~ ");
        fflush(stdin);
        if (scanf("%d", &DatosInsumo.clave) != 1 || !isInIntRange(&DatosInsumo.clave, 1, 100))
        {
            isValid = false;
            printf("\nERROR: Clave de insumo invalida.\n");
        }
        else
            isValid = true;

    } while (!isValid);

    do
    {
        printf("\nDescripcion del insumo [50 caracteres max.] ~ ");
        fflush(stdin);
        fgets(DatosInsumo.descripcion, sizeof(DatosInsumo.descripcion), stdin);

        isValid = minStringLength(DatosInsumo.descripcion, 10);

        if (!isValid)
            printf("\nERROR: Descripcion invalida, [10 - 50 caracteres].\n");
        
    } while (!isValid);

    do
    {
        printf("\nPunto de reorden [Mayor a 0] ~ ");
        fflush(stdin);
        if (scanf("%d", &DatosInsumo.puntoReorden) != 1 || !intMoreThanZero(&DatosInsumo.puntoReorden, false))
        {
            isValid = false;
            printf("\nERROR: Cantidad invalida.\n");
        }
        else
            isValid = true;

    } while (!isValid);

    do
    {
        printf("\nInventario del insumo [Mayor o igual a 0] ~ ");
        fflush(stdin);
        if (scanf("%d", &DatosInsumo.inventario) != 1 || !intMoreThanZero(&DatosInsumo.inventario, true))
        {
            isValid = false;
            printf("\nERROR: Cantidad invalida.\n");
        }
        else
            isValid = true;

    } while (!isValid);

    do
    {
        do
        {
            printf("\nIngrese la clave del proveedor [ %d/10 proveedores guardados] ~ ", proveedores);
            fflush(stdin);
            
            if(scanf("%d", &DatosInsumo.clavesProveedores[proveedores]) != 1 || !isInIntRange(&DatosInsumo.clavesProveedores[proveedores], 1, 100))
            {
                isValid = false;
                printf("\nERROR: Clave de proveedor invalida.\n");
            }
            else if (!existeClave(5, &DatosInsumo.clavesProveedores[proveedores]))
            {
                isValid = false;

                do
                {
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el proveedor? [s/n]");
                    fflush(stdin);
                    scanf("%c", &opcionRegistrar);

                    opcionRegistrar = tolower(opcionRegistrar);
                    isValid_opcionRegistrar = opcionRegistrar == 's' || opcionRegistrar == 'n';

                    if(!isValid_opcionRegistrar)
                        printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);

                } while(!isValid_opcionRegistrar);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("./Data_files/Proveedores.dat","rb+")) == NULL)
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    else
                    {
                        lecturaProveedor(archivo_NuevoRegistro);
                        fclose(archivo_NuevoRegistro);

                        if(existeClave(5, &DatosInsumo.clavesProveedores[proveedores]))
                            isValid = true;
                        else
                            printf("\nLa clave ingresada y el proveedor registrado no coinciden.\n");
                    }
                }
            }
            else    
                isValid = true;

        } while (!isValid);
        
        proveedores++;

        printf("\nIngresar información de otro proveedor? [ %d/10 proveedores guardados ] ~ ", proveedores);
        fflush(stdin);
        scanf("%c", &ingresarMas);
        
    } while (proveedores < 10 && ingresarMas == 'S');


    //FALTA LECTURA DE PRECIOS SURTIDOS 

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
    bool isValid;

    
    do
    {
        printf("\nIngrese la clave del empleado [1 - 1000] ~ ");
        if (scanf("%d", &DatosEmpleado.clave) != 1 || !isInIntRange(&DatosEmpleado.clave, 1, 1000))
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
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.nombres, sizeof(DatosEmpleado.datosPersonales.nombres), stdin);

            isValid = isAlphabetic(DatosEmpleado.datosPersonales.nombres, false);
            if (!isValid)
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
        } while (!isValid);

        // Lectura de apellidos
        do
        {
            printf("Ingrese apellido paterno del empleado: ");
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.apellidoPaterno, sizeof(DatosEmpleado.datosPersonales.apellidoPaterno), stdin);

            isValid = isAlphabetic(DatosEmpleado.datosPersonales.apellidoPaterno, false);

            if (!isValid)
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
        } while (!isValid);

        do
        {
            printf("Ingrese apellido materno del empleado: ");
            fflush(stdin);
            fgets(DatosEmpleado.datosPersonales.apellidoMaterno, sizeof(DatosEmpleado.datosPersonales.apellidoMaterno), stdin);

            isValid = isAlphabetic(DatosEmpleado.datosPersonales.apellidoMaterno, false);
            
            if (!isValid)
                printf("ERROR: Apellido materno invalido.(No ingresar caracteres especiales) \n");
        } while (!isValid);

        // Verificación de la distancia de caracteres
        distanciaCaracteres = lengthChar(DatosEmpleado.datosPersonales.nombres) +
                              lengthChar(DatosEmpleado.datosPersonales.apellidoMaterno) +
                              lengthChar(DatosEmpleado.datosPersonales.apellidoPaterno);

        isValid = distanciaCaracteres > 20;
        if (!isValid)
            printf("ERROR: La distancia de caracteres es MENOR a 20. \n");

    } while (!isValid);

    // Validación de RFC del empleado (agregada por ti, se sugiere incluir una validación)
    /*
    do {
        printf("Ingrese el RFC del empleado[1 - 1000]: ");
        scanf("%s", DatosEmpleado.datosPersonales.RFC);
    } while (!isInIntRange(&DatosEmpleado.clave, 1, 1000)); // Aquí necesitas lógica para validar RFC
    */

    // Lectura de correo electrónico
    do
    {
        printf("\nCorreo electronico del empleado [50 caracteres maximo] ~ ");
        fgets(DatosEmpleado.datosPersonales.correo, sizeof(DatosEmpleado.datosPersonales.correo), stdin);
        
        isValid = esCorreoElectronico(DatosEmpleado.datosPersonales.correo);
        
        if (!isValid)
            printf("\nERROR: Correo electronico invalido.\n");
        
    } while (!isValid);
    
    do
    {
        printf("Comision del empleado [Entre 0 y 1] ~ ");
        if (scanf("%1.2f", &DatosEmpleado.comision) != 1 || !isInFloatRange(&DatosEmpleado.comision, 0, 1)) {
            printf("\nERROR: Comision invalida.\n");
            isValid = false;
        } else {
            isValid = true;
        }
    } while (!isValid);

    
    do
    {
        printf("Año de contratacion del empleado [formato YYYY] ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.year) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.year, 1990, 2024)) {
            printf("\nERROR: Año invalido.\n");
            isValid = false;
        } else {
            isValid = true;
        }
    } while (!isValid);

    
    do
    {
        printf("Mes de contratacion [formato MM] ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.month) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.month, 1, 12)) {
            printf("\nERROR: Mes invalido.\n");
            isValid = false;
        } else {
            isValid = true;
        }
    } while (!isValid);

    
    do
    {
        printf("Dia de contratacion [formato dd] ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.day) != 1 || !isValidDate(&DatosEmpleado.datosPersonales.day, &DatosEmpleado.datosPersonales.month, &DatosEmpleado.datosPersonales.year)) {
            printf("\nERROR: Día de contratación invalido.\n");
            isValid = false;
        } else {
            isValid = true;
        }
    } while (!isValid);

    
    printf("\n\n\tDOMICILIO DEL EMPLEADO");

    do
    {
        printf("Calle [Solo letras, espacios y numeros] ~ ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.calle, sizeof(DatosEmpleado.datosPersonales.calle), stdin);
        isValid = isAlphabetic(DatosEmpleado.datosPersonales.calle, true);
        if (!isValid)
            printf("ERROR: Calle invalida.(No ingresar caracteres especiales) \n");
    } while (!isValid);

    do
    {
        printf("Numero [Entero mayor a 0] ~ ");
        if (scanf("%d", &DatosEmpleado.datosPersonales.numeroDomicilio) != 1 || !intMoreThanZero(&DatosEmpleado.datosPersonales.numeroDomicilio, false)) {
            isValid = false;
            printf("ERROR: Numero invalido.(Entero mayor a 0) \n");
        } else {
            isValid = true;
        }
    } while (!isValid);

    do
    {
        printf("Colonia del empleado: ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.colonia, sizeof(DatosEmpleado.datosPersonales.colonia), stdin);
        isValid = isAlphabetic(DatosEmpleado.datosPersonales.colonia, true);
        if (!isValid)
            printf("ERROR: Colonia invalida.(No ingresar caracteres especiales) \n");
    } while (!isValid);

    do
    {
        printf("Municipio del empleado: ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.municipio, sizeof(DatosEmpleado.datosPersonales.municipio), stdin);
        isValid = isAlphabetic(DatosEmpleado.datosPersonales.municipio, false);
        if (!isValid)
            printf("ERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
    } while (!isValid);

    do
    {
        printf("Estado del empleado: ");
        fflush(stdin);
        fgets(DatosEmpleado.datosPersonales.estado, sizeof(DatosEmpleado.datosPersonales.estado), stdin);
        
        isValid = isAlphabetic(DatosEmpleado.datosPersonales.estado, false);
        
        if (!isValid)
            printf("ERROR: Estado invalido.(No ingresar caracteres especiales) \n");
        
    } while (!isValid);

    
    fseek(archivoEmpleados, (DatosEmpleado.clave - 1) * sizeof(DatosEmpleado), SEEK_SET);
    fwrite(&DatosEmpleado, sizeof(DatosEmpleado), 1, archivoEmpleados);
}

void lecturaProveedor(FILE *archivoProveedores)
{
    printf("LECTURA PROVEEDORES");
}