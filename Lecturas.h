#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Validations.h"


void lecturaArticulo(FILE *);
void lecturaInsumo(FILE *);
void lecturaMercado(FILE *);
void lecturaEmpleado(FILE *);
void lecturaProveedor(FILE *);
void lecturaVentas(FILE *);
void lecturaCompras(FILE *);
void controlInventario(FILE *);


void lecturaArticulo(FILE *archivoArticulos)
{
    FILE *archivo_NuevoRegistro;
    struct infoArticulo DatosArticulo = {0, {0}, {0}, 0, 0, 0, "", 0, 0};
    bool isInvalid, opcionRegistrarInvalida;
    char ingresarMas, opcionRegistrar;
    int i, mercados = 0, insumos = 0;

    do
    {
        printf("\nIngrese la clave del articulo [1 - 1000] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosArticulo.clave) != 1 || !isInIntRange(&DatosArticulo.clave, 1, 1000))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Clave de articulo invalida.\n");
            setColor(7);
        }
        else if (existeClave(1, &DatosArticulo.clave))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Clave de articulo ya existe.\n");
            setColor(7);
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nDescripcion del articulo [50 caracteres max.] ~ ");
        fflush(stdin);

        if (fgets(DatosArticulo.descripcion, sizeof(DatosArticulo.descripcion), stdin) != NULL)
        {
            retirarSaltoLinea(DatosArticulo.descripcion);
            isInvalid = !minStringLength(DatosArticulo.descripcion, 10);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Descripcion invalida, [10 - 50 caracteres].\n");
            setColor(7);
        }
        
    } while (isInvalid);

    do
    {
        printf("\nTemporada de siembra \n"
                "1 - Primavera\n"
                "2 - Verano\n"
                "3 - Oto%co\n"
                "4 - Invierno\n"
                "[Ingresa el numero de la temporada] ~ ",164);

        fflush(stdin);

        if (scanf("%d", &DatosArticulo.temporadaSiembra) != 1 || !isInIntRange(&DatosArticulo.temporadaSiembra, 1, 4))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Numero invalido.\n");
            setColor(7);
        }
        else
            isInvalid = false;

    } while (isInvalid);
    
    do
    {
        printf("\nTemporada de cosecha \n"
                "1 - Primavera\n"
                "2 - Verano\n"
                "3 - Oto%co\n"
                "4 - Invierno\n"
                "[Ingresa el numero de la temporada] ~ ",164);

        fflush(stdin);

        if (scanf("%d", &DatosArticulo.temporadaCosecha) != 1 || !isInIntRange(&DatosArticulo.temporadaCosecha, 1, 4))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Numero invalido.\n");
            setColor(7);
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nInventario del articulo [Mayor o igual a 0] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosArticulo.inventario) != 1 || !intMoreThanZero(&DatosArticulo.inventario, true))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Cantidad invalida.\n");
            setColor(7);
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
            setColor(4);
            printf("\nERROR: Precio invalido.\n");
            setColor(7);
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
                setColor(4);
                printf("\nERROR: Clave de mercado invalida.\n");
                setColor(7);
            }
            else if (!existeClave(3, &DatosArticulo.clavesMercados[mercados]))
            {
                isInvalid = true;

                do
                {
                    setColor(4);
                    printf("\nERROR: La clave ingresada no esta registrada.\n");
                    setColor(7);
                    printf("Desea registrar el mercado? [s/n] ~ ");
                    
                    fflush(stdin);

                    if(scanf("%c", &opcionRegistrar) != 1)
                        opcionRegistrarInvalida = true;
                    else
                    {
                        opcionRegistrar = tolower(opcionRegistrar);
                        opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                    }
                    
                    if (opcionRegistrarInvalida)
                    {
                        setColor(4);
                        printf("ERROR. Respuesta invalida [s/n].\n");
                        setColor(7);
                    }

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("Mercados.dat","rb+")) == NULL)
                    {
                        setColor(4);
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                        setColor(7);
                    }
                    else
                    {
                        lecturaMercado(archivo_NuevoRegistro);

                        fclose(archivo_NuevoRegistro);

                        if(existeClave(3, &DatosArticulo.clavesMercados[mercados]))
                            isInvalid = false;
                        else
                        {
                            setColor(4);
                            printf("\nLa clave ingresada y el mercado registrado no coinciden.\n");
                            setColor(7);
                        }
                    }
                }
            }
            else
                isInvalid = false;

            i = 0;

            while(i < mercados && !isInvalid)
            {
                if(DatosArticulo.clavesMercados[mercados] == DatosArticulo.clavesMercados[i])
                {
                    setColor(4);
                    printf("\nLa clave ingresada ya esta registrada para este articulo.\n");
                    setColor(7);

                    isInvalid = true;
                }
                i++;
            }

        } while (isInvalid);
        
        mercados++;

        do
        {
            printf("\nIngresar informaci%cn de otro mercado? [ %d/10 mercados guardados ] [s/n] ~ ", 162, mercados);
            fflush(stdin);

            if(scanf("%c", &ingresarMas) != 1)
                isInvalid = true;
            else
            {
                ingresarMas = tolower(ingresarMas);
                isInvalid = ingresarMas != 's' && ingresarMas != 'n';
            }
            
            if (isInvalid)
            {
                setColor(4);
                printf("ERROR. Respuesta invalida [s/n].\n");
                setColor(7);
            }

        } while (isInvalid);
        
    } while (mercados < 10 && ingresarMas == 's');

    do
    {
        do
        {
            printf("\nIngrese la clave del insumo [ %d/10 insumos guardados] ~ ", insumos);
            fflush(stdin);

            if(scanf("%d", &DatosArticulo.clavesInsumos[insumos]) != 1 || !isInIntRange(&DatosArticulo.clavesInsumos[insumos], 1, 100))
            {
                isInvalid = true;
                setColor(4);
                printf("\nERROR: Clave de insumo invalida.\n");
                setColor(7);
            }
            else if (!existeClave(2, &DatosArticulo.clavesInsumos[insumos]))
            {
                isInvalid = true;

                do
                {
                    setColor(4);
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el insumo? [s/n] ~ ");
                    setColor(7);
                    fflush(stdin);

                    if(scanf("%c", &opcionRegistrar) != 1)
                        opcionRegistrarInvalida = true;
                    else
                    {
                        opcionRegistrar = tolower(opcionRegistrar);
                        opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                    }
                    
                    if (opcionRegistrarInvalida)
                    {
                        setColor(4);
                        printf("ERROR. Respuesta invalida [s/n].\n");
                        setColor(7);
                    }

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("Insumos.dat","rb+")) == NULL)
                    {
                        setColor(4);
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                        setColor(7);
                    }
                    else
                    {
                        lecturaInsumo(archivo_NuevoRegistro);
                        
                        fclose(archivo_NuevoRegistro);

                        if(existeClave(2, &DatosArticulo.clavesInsumos[insumos]))
                            isInvalid = false;
                        else
                        {
                            setColor(4);
                            printf("\nLa clave ingresada y el insumo registrado no coinciden.\n");
                            setColor(7);
                        }
                    }
                }
            }
            else
                isInvalid = false;

            i = 0;
                
            while(i < insumos && !isInvalid)
            {
                if(DatosArticulo.clavesInsumos[insumos] == DatosArticulo.clavesInsumos[i])
                {
                    setColor(4);
                    printf("\nLa clave ingresada ya esta registrada para este articulo.\n");
                    setColor(7);
                    
                    isInvalid = true;
                }
                i++;
            }
                
        } while (isInvalid);

        insumos++;

        do
        {
            printf("\nIngresar informaci%cn de otro insumo? [ %d/10 insumos guardados ] [s/n] ~ ", 162, insumos);
            fflush(stdin);

            if(scanf("%c", &ingresarMas) != 1)
                isInvalid = true;
            else
            {
                ingresarMas = tolower(ingresarMas);
                isInvalid = ingresarMas != 's' && ingresarMas != 'n';
            }
            
            if (isInvalid)
            {
                setColor(4);
                printf("ERROR. Respuesta invalida [s/n].\n");
                setColor(7);
            }
            
        } while (isInvalid);
        
    } while (insumos < 10 && ingresarMas == 's');

    
    DatosArticulo.costoProduccion = obtenerCosto(DatosArticulo.clavesInsumos, &insumos);

    fseek(archivoArticulos, (DatosArticulo.clave - 1) * sizeof(DatosArticulo), SEEK_SET);
    fwrite(&DatosArticulo, sizeof(DatosArticulo), 1, archivoArticulos);
}

void lecturaInsumo(FILE *archivoInsumos)
{
    FILE *archivo_NuevoRegistro;
    struct infoInsumo DatosInsumo = {0, {0}, 0, 0, "", {0}};
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
            setColor(4);
            printf("\nERROR: Clave de insumo invalida.\n");
            setColor(7);
        }
        else if(existeClave(2, &DatosInsumo.clave))
        {
            isInvalid = true;
            setColor(4);
            printf("\nLa clave ingresada ya esta registrada.\n");
            setColor(7);
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nDescripcion del insumo [50 caracteres max.] ~ ");
        fflush(stdin);

        if(fgets(DatosInsumo.descripcion, sizeof(DatosInsumo.descripcion), stdin) != NULL)
        {
            retirarSaltoLinea(DatosInsumo.descripcion);
            isInvalid = !minStringLength(DatosInsumo.descripcion, 10);
        }
        else
            isInvalid = true;
        
        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Descripcion invalida, [10 - 50 caracteres].\n");
            setColor(7);
        }
        
    } while (isInvalid);

    do
    {
        printf("\nPunto de reorden [Mayor a 0] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosInsumo.puntoReorden) != 1 || !intMoreThanZero(&DatosInsumo.puntoReorden, false))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Cantidad invalida.\n");
            setColor(7);
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
            setColor(4);
            printf("\nERROR: Cantidad invalida.\n");
            setColor(7);
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
                setColor(4);
                printf("\nERROR: Clave de proveedor invalida.\n");
                setColor(7);
            }
            else if (!existeClave(5, &DatosInsumo.clavesProveedores[proveedores]))
            {
                isInvalid = true;

                do
                {
                    setColor(4);
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el proveedor? [s/n] ~ ");
                    setColor(7);
                    fflush(stdin);

                    if(scanf("%c", &opcionRegistrar) != 1)
                        opcionRegistrarInvalida = true;
                    else
                    {
                        opcionRegistrar = tolower(opcionRegistrar);
                        opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                    }
                    
                    if (opcionRegistrarInvalida)
                    {
                        setColor(4);
                        printf("ERROR. Respuesta invalida [s/n].\n");
                        setColor(7);
                    }

                } while (opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("Proveedores.dat","rb+")) == NULL)
                    {
                        setColor(4);
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                        setColor(7);
                    }
                    else
                    {
                        lecturaProveedor(archivo_NuevoRegistro);
                        fclose(archivo_NuevoRegistro);

                        if (existeClave(5, &DatosInsumo.clavesProveedores[proveedores]))
                            isInvalid = false;
                        else
                        {
                            setColor(4);
                            printf("\nLa clave ingresada y el proveedor registrado no coinciden.\n");
                            setColor(7);
                        }
                    }
                }
            }
            else
                isInvalid = false;

            i = 0;

            while(i < proveedores && !isInvalid)
            {
                if(DatosInsumo.clavesProveedores[proveedores] == DatosInsumo.clavesProveedores[i])
                {
                    setColor(4);
                    printf("\nLa clave ingresada ya esta registrada para este articulo.\n");
                    setColor(7);

                    isInvalid = true;
                }
                i++;
            }

        } while (isInvalid);
        
        proveedores++;

        do
        {
            printf("\nIngresar informacion de otro proveedor? [ %d/10 proveedores guardados ] (s/n) ~ ", proveedores);
            fflush(stdin);

            if(scanf("%c", &ingresarMas) != 1)
                isInvalid = true;
            else
            {
                ingresarMas = tolower(ingresarMas);
                isInvalid = ingresarMas != 's' && ingresarMas != 'n';
            }
            
            if (isInvalid)
            {
                setColor(4);
                printf("ERROR. Respuesta invalida [s/n].\n");
                setColor(7);
            }
            
        } while (isInvalid);
        
    } while (proveedores < 10 && ingresarMas == 's');


    printf("\n\tLECTURA DE PRECIOS POR PROVEEDOR\n");

    for(i = 0; i < proveedores; i++)
    {
        printf("\nPrecio del insumo para el proveedor %d: $", DatosInsumo.clavesProveedores[i]);
        
        do
        {
            fflush(stdin);
            if (scanf("%f", &DatosInsumo.precioSurtido[i]) != 1 || !floatMoreThanZero(&DatosInsumo.precioSurtido[i], false))
            {
                isInvalid = true;

                setColor(4);
                printf("\nERROR: Precio invalido.\n");
                setColor(7);
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

    printf("\n\n\t########## DATOS DE MERCADO ##########\n\n");

    do
    {
        printf("Clave del mercado [1 - 100] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosMercado.clave) != 1 || !isInIntRange(&DatosMercado.clave, 1, 100))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Clave de mercado invalida.\n");
            setColor(7);
        }
        else if(existeClave(3, &DatosMercado.clave))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: La clave ingresada ya esta registrada.\n");
            setColor(7);
        }
        else
            isInvalid = false;
            
    } while (isInvalid);


    printf("\n\n\t----- NOMBRE COMPLETO DEL CLIENTE -----\n\n");

    do
    {
        do
        {
            printf("Nombres [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosMercado.datosPersonales.nombres, sizeof(DatosMercado.datosPersonales.nombres), stdin) != NULL)
            {
                retirarSaltoLinea(DatosMercado.datosPersonales.nombres);
                isInvalid = !isAlphabetic(DatosMercado.datosPersonales.nombres, false);
            }
            else
                isInvalid = true;
            
            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        do
        {
            printf("Apellido Paterno [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosMercado.datosPersonales.apellidoPaterno, sizeof(DatosMercado.datosPersonales.apellidoPaterno), stdin) != NULL)
            {
                retirarSaltoLinea(DatosMercado.datosPersonales.apellidoPaterno);
                isInvalid = !isAlphabetic(DatosMercado.datosPersonales.apellidoPaterno, false);
            }
            else
                isInvalid = true;

            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        do
        {
            printf("Apellido Materno [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosMercado.datosPersonales.apellidoMaterno, sizeof(DatosMercado.datosPersonales.apellidoMaterno), stdin) != NULL)
            {
                retirarSaltoLinea(DatosMercado.datosPersonales.apellidoMaterno);
                isInvalid = !isAlphabetic(DatosMercado.datosPersonales.apellidoMaterno, false);
            }
            else
                isInvalid = true;

            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Apellido materno invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }
            
        } while (isInvalid);

        distanciaCaracteres = stringLength(DatosMercado.datosPersonales.nombres) +
                              stringLength(DatosMercado.datosPersonales.apellidoMaterno) +
                              stringLength(DatosMercado.datosPersonales.apellidoPaterno) + 2;
        
        isInvalid = distanciaCaracteres <= 20;

        if (isInvalid)
        {
            setColor(4);
            printf("ERROR: La distancia de caracteres es MENOR o IGUAL a 20. \n");
            setColor(7);
        }

    } while (isInvalid);


    printf("\n\n\t----- FECHA DE NACIMIENTO DEL CLIENTE -----\n");

    do
    {        
        do
        {
            printf("A%co [1950 - 2006] ~ ", 164);
            fflush(stdin);

            if (scanf("%d", &DatosMercado.datosPersonales.yearBirth) != 1 || !isInIntRange(&DatosMercado.datosPersonales.yearBirth, 1950, 2006))
            {
                setColor(4);
                printf("\nERROR: A%co invalido.\n", 164);
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("Mes [1 - 12] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosMercado.datosPersonales.monthBirth) != 1 || !isInIntRange(&DatosMercado.datosPersonales.monthBirth, 1, 12))
            {
                setColor(4);
                printf("\nERROR: Mes invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        do
        {
            printf("Dia [1 - 31] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosMercado.datosPersonales.dayBirth) != 1 || !isInIntRange(&DatosMercado.datosPersonales.dayBirth, 1, 31))
            {
                setColor(4);
                printf("\nERROR: Dia invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;
        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosMercado.datosPersonales.dayBirth, &DatosMercado.datosPersonales.monthBirth, &DatosMercado.datosPersonales.yearBirth);

        if (fechaInvalida)
        {
            setColor(4);
            printf("\nERROR: Fecha invalida.\n");
            setColor(7);
        }

    } while (fechaInvalida);
    
    printf("\n\n----- RFC DEL CLIENTE -----\n");

    do
    {
        printf("\nRFC: ~ ");
        fflush(stdin);

        if (fgets(DatosMercado.datosPersonales.RFC, sizeof(DatosMercado.datosPersonales.RFC), stdin) != NULL)
        {
            retirarSaltoLinea(DatosMercado.datosPersonales.RFC);

            for (i = 0; i < strlen(DatosMercado.datosPersonales.RFC); i++) 
                DatosMercado.datosPersonales.RFC[i] = toupper(DatosMercado.datosPersonales.RFC[i]);
                
            if(validarRFC(&DatosMercado.datosPersonales))
                isInvalid = false;
            else
            {
                setColor(4);
                printf("\nERROR: EL RFC NO COINCIDE CON LOS DATOS PROPORCIONADOS.\n");
                setColor(7);
                isInvalid = true;
            }
        }
        else
        {
            setColor(4);
            printf("\nERROR: RFC INVALIDO.\n");
            setColor(7);
            isInvalid = true;
        }

    } while (isInvalid);

    printf("\n\n----- DOMICILIO DEL CLIENTE -----\n");

    do
    {
        printf("\nCalle [Solo letras, espacios y numeros] ~ ");
        fflush(stdin);

        if (fgets(DatosMercado.datosPersonales.calle, sizeof(DatosMercado.datosPersonales.calle), stdin) != NULL)
        {
            retirarSaltoLinea(DatosMercado.datosPersonales.calle);
            isInvalid = !isAlphabetic(DatosMercado.datosPersonales.calle, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Calle invalida.(No ingresar caracteres especiales) \n");
            setColor(7);
        }
        
    } while (isInvalid);

    do
    {
        printf("\nNumero [Entero mayor a 0] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosMercado.datosPersonales.numeroDomicilio) != 1 || !intMoreThanZero(&DatosMercado.datosPersonales.numeroDomicilio, false))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Numero invalido.(Entero mayor a 0) \n");
            setColor(7);
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nColonia ~ ");
        fflush(stdin);

        if (fgets(DatosMercado.datosPersonales.colonia, sizeof(DatosMercado.datosPersonales.colonia), stdin) != NULL)
        {
            retirarSaltoLinea(DatosMercado.datosPersonales.colonia);
            isInvalid = !isAlphabetic(DatosMercado.datosPersonales.colonia, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Colonia invalida (No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("\nMunicipio ~ ");
        fflush(stdin);

        if (fgets(DatosMercado.datosPersonales.municipio, sizeof(DatosMercado.datosPersonales.municipio), stdin) != NULL)
        {
            retirarSaltoLinea(DatosMercado.datosPersonales.municipio);
            isInvalid = !isAlphabetic(DatosMercado.datosPersonales.municipio, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("\nEstado ~ ");
        fflush(stdin);

        if (fgets(DatosMercado.datosPersonales.estado, sizeof(DatosMercado.datosPersonales.estado), stdin) != NULL)
        {
            retirarSaltoLinea(DatosMercado.datosPersonales.estado);
            isInvalid = !isAlphabetic(DatosMercado.datosPersonales.estado, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Estado invalido.(No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    printf("\n\n----- OTROS DATOS -----\n");

    do
    {
        printf("\nCorreo electronico del cliente [50 caracteres maximo] ~ ");
        fflush(stdin);

        if (fgets(DatosMercado.datosPersonales.correo, sizeof(DatosMercado.datosPersonales.correo), stdin) != NULL)
        {
            retirarSaltoLinea(DatosMercado.datosPersonales.correo);
            isInvalid = !esCorreoElectronico(DatosMercado.datosPersonales.correo);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Correo electronico invalido.\n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("Descuento para el cliente [Entre 0 y 1] ~ ");
        fflush(stdin);

        if (scanf("%f", &DatosMercado.descuento) != 1 || !isInFloatRange(&DatosMercado.descuento, 0, 1))
        {
            setColor(4);
            printf("\nERROR: Valor invalido para el descuento.\n");
            setColor(7);
            isInvalid = true;
        }
        else
            isInvalid = false;

    } while (isInvalid);

    fseek(archivoMercados, (DatosMercado.clave - 1) * sizeof(DatosMercado), SEEK_SET);
    fwrite(&DatosMercado, sizeof(DatosMercado), 1, archivoMercados);
}

void lecturaEmpleado(FILE *archivoEmpleados)
{
    struct infoEmpleado DatosEmpleado;
    int distanciaCaracteres, i;
    bool isInvalid, fechaInvalida;

    printf("\n\n\t########## DATOS DE EMPLEADO ##########\n\n");

    do
    {
        printf("Clave del empleado [1 - 1000] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosEmpleado.clave) != 1 || !isInIntRange(&DatosEmpleado.clave, 1, 1000))
        {
            setColor(4);
            printf("\nERROR: Clave de empleado invalida.\n");
            setColor(7);
            isInvalid = true;
        }
        else if(existeClave(4, &DatosEmpleado.clave))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: La clave ingresada ya esta registrada.\n");
            setColor(7);
        }
        else
            isInvalid = false;
            
    } while (isInvalid);


    printf("\n\n\t----- NOMBRE COMPLETO DEL EMPLEADO -----\n\n");

    do
    {
        do
        {
            printf("Nombres [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosEmpleado.datosPersonales.nombres, sizeof(DatosEmpleado.datosPersonales.nombres), stdin) != NULL)
            {
                retirarSaltoLinea(DatosEmpleado.datosPersonales.nombres);
                isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.nombres, false);
            }
            else
                isInvalid = true;
            
            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        do
        {
            printf("Apellido Paterno [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosEmpleado.datosPersonales.apellidoPaterno, sizeof(DatosEmpleado.datosPersonales.apellidoPaterno), stdin) != NULL)
            {
                retirarSaltoLinea(DatosEmpleado.datosPersonales.apellidoPaterno);
                isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.apellidoPaterno, false);
            }
            else
                isInvalid = true;

            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        do
        {
            printf("Apellido Materno [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosEmpleado.datosPersonales.apellidoMaterno, sizeof(DatosEmpleado.datosPersonales.apellidoMaterno), stdin) != NULL)
            {
                retirarSaltoLinea(DatosEmpleado.datosPersonales.apellidoMaterno);
                isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.apellidoMaterno, false);
            }
            else
                isInvalid = true;

            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Apellido materno invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        distanciaCaracteres = stringLength(DatosEmpleado.datosPersonales.nombres) +
                              stringLength(DatosEmpleado.datosPersonales.apellidoMaterno) +
                              stringLength(DatosEmpleado.datosPersonales.apellidoPaterno) + 2;

        isInvalid = distanciaCaracteres <= 20;

        if (isInvalid)
        {
            setColor(4);
            printf("ERROR: La distancia de caracteres es MENOR o IGUAL a 20. \n");
            setColor(7);
        }

    } while (isInvalid);


    printf("\n\n\t----- FECHA DE NACIMIENTO DEL EMPLEADO -----\n");

    do
    {        
        do
        {
            printf("A%co [1950 - 2006] ~ ", 164);
            fflush(stdin);

            if (scanf("%d", &DatosEmpleado.datosPersonales.yearBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.yearBirth, 1950, 2006))
            {
                setColor(4);
                printf("\nERROR: A%co invalido.\n", 164);
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("Mes [1- 12] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosEmpleado.datosPersonales.monthBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.monthBirth, 1, 12))
            {
                setColor(4);
                printf("\nERROR: Mes invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("Dia [1 - 31] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosEmpleado.datosPersonales.dayBirth) != 1 || !isInIntRange(&DatosEmpleado.datosPersonales.dayBirth, 1, 31))
            {
                setColor(4);
                printf("\nERROR: Dia invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosEmpleado.datosPersonales.dayBirth, &DatosEmpleado.datosPersonales.monthBirth, &DatosEmpleado.datosPersonales.yearBirth);

        if (fechaInvalida)
        {
            setColor(4);
            printf("\nERROR: Fecha invalida.\n");
            setColor(7);
        }

    } while (fechaInvalida);
    
    printf("\n\n----- RFC DEL EMPLEADO -----\n");

    do
    {
        printf("\nRFC: ~ ");
        fflush(stdin);

        if (fgets(DatosEmpleado.datosPersonales.RFC, sizeof(DatosEmpleado.datosPersonales.RFC), stdin) != NULL)
        {
            retirarSaltoLinea(DatosEmpleado.datosPersonales.RFC);
            
            for (i = 0; i < strlen(DatosEmpleado.datosPersonales.RFC); i++) 
                DatosEmpleado.datosPersonales.RFC[i] = toupper(DatosEmpleado.datosPersonales.RFC[i]);

            if(validarRFC(&DatosEmpleado.datosPersonales))
                isInvalid = false;
            else
            {
                setColor(4);
                printf("\nERROR: EL RFC NO COINCIDE CON LOS DATOS PROPORCIONADOS.\n");
                setColor(7);
                isInvalid = true;
            }
        }
        else
        {
            setColor(4);
            printf("\nERROR: RFC INVALIDO.\n");
            setColor(7);
            isInvalid = true;
        }

    } while (isInvalid);

    printf("\n\n\t----- FECHA DE CONTRATACION DEL EMPLEADO -----\n");

    do
    {        
        do
        {
            printf("A%co [1990 - 2024] ~ ", 164);
            fflush(stdin);

            if (scanf("%d", &DatosEmpleado.yearContratacion) != 1 || !isInIntRange(&DatosEmpleado.yearContratacion, 1990, 2024))
            {
                setColor(4);
                printf("\nERROR: A%co invalido.\n", 164);
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("Mes [1- 12] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosEmpleado.monthContratacion) != 1 || !isInIntRange(&DatosEmpleado.monthContratacion, 1, 12))
            {
                setColor(4);
                printf("\nERROR: Mes invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("Dia [1 - 31] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosEmpleado.dayContratacion) != 1 || !isInIntRange(&DatosEmpleado.dayContratacion, 1, 31))
            {
                setColor(4);
                printf("\nERROR: Dia invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosEmpleado.dayContratacion, &DatosEmpleado.monthContratacion, &DatosEmpleado.yearContratacion);

        if (fechaInvalida)
        {
            setColor(4);
            printf("\nERROR: Fecha invalida.\n");
            setColor(7);
        }

    } while (fechaInvalida);


    printf("\n\n----- DOMICILIO DEL EMPLEADO -----\n");

    do
    {
        printf("\nCalle [Solo letras, espacios y numeros] ~ ");
        fflush(stdin);

        if (fgets(DatosEmpleado.datosPersonales.calle, sizeof(DatosEmpleado.datosPersonales.calle), stdin) != NULL)
        {
            retirarSaltoLinea(DatosEmpleado.datosPersonales.calle);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.calle, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Calle invalida.(No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("\nNumero [Entero mayor a 0] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosEmpleado.datosPersonales.numeroDomicilio) != 1 || !intMoreThanZero(&DatosEmpleado.datosPersonales.numeroDomicilio, false))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Numero invalido.(Entero mayor a 0) \n");
            setColor(7);
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nColonia ~ ");
        fflush(stdin);

        if (fgets(DatosEmpleado.datosPersonales.colonia, sizeof(DatosEmpleado.datosPersonales.colonia), stdin) != NULL)
        {
            retirarSaltoLinea(DatosEmpleado.datosPersonales.colonia);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.colonia, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Colonia invalida (No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("\nMunicipio ~ ");
        fflush(stdin);

        if (fgets(DatosEmpleado.datosPersonales.municipio, sizeof(DatosEmpleado.datosPersonales.municipio), stdin) != NULL)
        {
            retirarSaltoLinea(DatosEmpleado.datosPersonales.municipio);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.municipio, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("\nEstado ~ ");
        fflush(stdin);

        if (fgets(DatosEmpleado.datosPersonales.estado, sizeof(DatosEmpleado.datosPersonales.estado), stdin) != NULL)
        {
            retirarSaltoLinea(DatosEmpleado.datosPersonales.estado);
            isInvalid = !isAlphabetic(DatosEmpleado.datosPersonales.estado, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Estado invalido.(No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    printf("\n\n----- OTROS DATOS -----\n");

    do
    {
        printf("\nCorreo electronico del empleado [50 caracteres maximo] ~ ");
        if (fgets(DatosEmpleado.datosPersonales.correo, sizeof(DatosEmpleado.datosPersonales.correo), stdin) != NULL)
        {
            retirarSaltoLinea(DatosEmpleado.datosPersonales.correo);
            isInvalid = !esCorreoElectronico(DatosEmpleado.datosPersonales.correo);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Correo electronico invalido.\n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("\nComision para el empleado [Entre 0 y 1] ~ ");
        fflush(stdin);

        if (scanf("%f", &DatosEmpleado.comision) != 1 || !isInFloatRange(&DatosEmpleado.comision, 0, 1))
        {
            setColor(4);
            printf("\nERROR: Valor invalido para la comision.\n");
            setColor(7);
            isInvalid = true;
        }
        else
            isInvalid = false;

    } while (isInvalid);

    fseek(archivoEmpleados, (DatosEmpleado.clave - 1) * sizeof(DatosEmpleado), SEEK_SET);
    fwrite(&DatosEmpleado, sizeof(DatosEmpleado), 1, archivoEmpleados);
}

void lecturaProveedor(FILE *archivoProveedores)
{
    struct infoProveedor DatosProveedor;
    int distanciaCaracteres, i;
    bool isInvalid, fechaInvalida;

    printf("\n\n\t########## DATOS DE PROVEEDOR ##########\n\n");

    do
    {
        printf("Clave del proveedor [1 - 100] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosProveedor.clave) != 1 || !isInIntRange(&DatosProveedor.clave, 1, 100))
        {
            setColor(4);
            printf("\nERROR: Clave de proveedor invalida.\n");
            setColor(7);
            isInvalid = true;
        }
        else if(existeClave(5, &DatosProveedor.clave))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: La clave ingresada ya esta registrada.\n");
            setColor(7);
        }
        else
            isInvalid = false;
            
    } while (isInvalid);


    printf("\n\n\t----- NOMBRE COMPLETO DEL PROVEEDOR -----\n\n");

    do
    {
        do
        {
            printf("Nombres [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosProveedor.datosPersonales.nombres, sizeof(DatosProveedor.datosPersonales.nombres), stdin) != NULL)
            {
                retirarSaltoLinea(DatosProveedor.datosPersonales.nombres);
                isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.nombres, false);
            }
            else
                isInvalid = true;
            
            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Nombre invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        do
        {
            printf("Apellido Paterno [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosProveedor.datosPersonales.apellidoPaterno, sizeof(DatosProveedor.datosPersonales.apellidoPaterno), stdin) != NULL)
            {
                retirarSaltoLinea(DatosProveedor.datosPersonales.apellidoPaterno);
                isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.apellidoPaterno, false);
            }
            else
                isInvalid = true;

            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Apellido paterno invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        do
        {
            printf("Apellido Materno [Maximo 30 caracteres]: ");
            fflush(stdin);

            if (fgets(DatosProveedor.datosPersonales.apellidoMaterno, sizeof(DatosProveedor.datosPersonales.apellidoMaterno), stdin) != NULL)
            {
                retirarSaltoLinea(DatosProveedor.datosPersonales.apellidoMaterno);
                isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.apellidoMaterno, false);
            }
            else
                isInvalid = true;

            if (isInvalid)
            {
                setColor(4);
                printf("ERROR: Apellido materno invalido.(No ingresar caracteres especiales) \n");
                setColor(7);
            }

        } while (isInvalid);

        distanciaCaracteres = stringLength(DatosProveedor.datosPersonales.nombres) +
                              stringLength(DatosProveedor.datosPersonales.apellidoMaterno) +
                              stringLength(DatosProveedor.datosPersonales.apellidoPaterno) + 2;

        isInvalid = distanciaCaracteres <= 20;

        if (isInvalid)
        {
            setColor(4);
            printf("ERROR: La distancia de caracteres es MENOR o IGUAL a 20. \n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {        
        printf("\n\n\t----- FECHA DE NACIMIENTO DEL PROVEEDOR -----\n");
        do
        {
            printf("A%co [1950 - 2006] ~ ", 164);
            fflush(stdin);

            if (scanf("%d", &DatosProveedor.datosPersonales.yearBirth) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.yearBirth, 1950, 2006))
            {
                setColor(4);
                printf("\nERROR: A%co invalido.\n", 164);
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("Mes [1- 12] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosProveedor.datosPersonales.monthBirth) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.monthBirth, 1, 12))
            {
                setColor(4);
                printf("\nERROR: Mes invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        do
        {
            printf("Dia [1 - 31] ~ ");
            fflush(stdin);

            if (scanf("%d", &DatosProveedor.datosPersonales.dayBirth) != 1 || !isInIntRange(&DatosProveedor.datosPersonales.dayBirth, 1, 31))
            {
                setColor(4);
                printf("\nERROR: Dia invalido.\n");
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while (isInvalid);

        fechaInvalida = !validarFecha(&DatosProveedor.datosPersonales.dayBirth, &DatosProveedor.datosPersonales.monthBirth, &DatosProveedor.datosPersonales.yearBirth);

        if (fechaInvalida)
        {
            setColor(4);
            printf("\nERROR: Fecha invalida.\n");
            setColor(7);
        }

    } while (fechaInvalida);
    
    printf("\n\n----- RFC DEL PROVEEDOR -----\n");

    do
    {
        printf("\nRFC: ~ ");
        fflush(stdin);

        if (fgets(DatosProveedor.datosPersonales.RFC, sizeof(DatosProveedor.datosPersonales.RFC), stdin) != NULL)
        {
            retirarSaltoLinea(DatosProveedor.datosPersonales.RFC);

            for (i = 0; i < strlen(DatosProveedor.datosPersonales.RFC); i++) 
                DatosProveedor.datosPersonales.RFC[i] = toupper(DatosProveedor.datosPersonales.RFC[i]);
            
            if(validarRFC(&DatosProveedor.datosPersonales))
                isInvalid = false;
            else
            {
                setColor(4);
                printf("\nERROR: EL RFC NO COINCIDE CON LOS DATOS PROPORCIONADOS.\n");
                setColor(7);
                isInvalid = true;
            }
        }
        else
        {
            setColor(4);
            printf("\nERROR: RFC INVALIDO.\n");
            setColor(7);
            isInvalid = true;
        }

    } while (isInvalid);

    printf("\n\n----- DOMICILIO DEL PROVEEDOR -----\n");

    do
    {
        printf("\nCalle [Solo letras, espacios y numeros] ~ ");
        fflush(stdin);

        if (fgets(DatosProveedor.datosPersonales.calle, sizeof(DatosProveedor.datosPersonales.calle), stdin) != NULL)
        {
            retirarSaltoLinea(DatosProveedor.datosPersonales.calle);
            isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.calle, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Calle invalida.(No ingresar caracteres especiales) \n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("\nNumero [Entero mayor a 0] ~ ");
        fflush(stdin);

        if (scanf("%d", &DatosProveedor.datosPersonales.numeroDomicilio) != 1 || !intMoreThanZero(&DatosProveedor.datosPersonales.numeroDomicilio, false))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Numero invalido.(Entero mayor a 0) \n");
            setColor(7);
        }
        else
            isInvalid = false;

    } while (isInvalid);

    do
    {
        printf("\nColonia ~ ");
        fflush(stdin);

        if (fgets(DatosProveedor.datosPersonales.colonia, sizeof(DatosProveedor.datosPersonales.colonia), stdin) != NULL)
        {
            retirarSaltoLinea(DatosProveedor.datosPersonales.colonia);
            isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.colonia, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Colonia invalida (No ingresar caracteres especiales) \n");
            setColor(7);

        }

    } while (isInvalid);

    do
    {
        printf("\nMunicipio ~ ");
        fflush(stdin);

        if (fgets(DatosProveedor.datosPersonales.municipio, sizeof(DatosProveedor.datosPersonales.municipio), stdin) != NULL)
        {
            retirarSaltoLinea(DatosProveedor.datosPersonales.municipio);
            isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.municipio, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Municipio invalido.(No ingresar caracteres especiales) \n");
            setColor(7);

        }

    } while (isInvalid);

    do
    {
        printf("\nEstado ~ ");
        fflush(stdin);

        if (fgets(DatosProveedor.datosPersonales.estado, sizeof(DatosProveedor.datosPersonales.estado), stdin) != NULL)
        {
            retirarSaltoLinea(DatosProveedor.datosPersonales.estado);
            isInvalid = !isAlphabetic(DatosProveedor.datosPersonales.estado, true);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Estado invalido.(No ingresar caracteres especiales) \n");
            setColor(7);   
        }

    } while (isInvalid);

    printf("\n\n----- OTROS DATOS -----\n");

    do
    {
        printf("\nCorreo electronico del proveedor [50 caracteres maximo] ~ ");
        fflush(stdin);

        if (fgets(DatosProveedor.datosPersonales.correo, sizeof(DatosProveedor.datosPersonales.correo), stdin) != NULL)
        {
            retirarSaltoLinea(DatosProveedor.datosPersonales.correo);
            isInvalid = !esCorreoElectronico(DatosProveedor.datosPersonales.correo);
        }
        else
            isInvalid = true;

        if (isInvalid)
        {
            setColor(4);
            printf("\nERROR: Correo electronico invalido.\n");
            setColor(7);
        }

    } while (isInvalid);

    do
    {
        printf("Descuento para el proveedor [Entre 0 y 1] ~ ");
        fflush(stdin);

        if (scanf("%f", &DatosProveedor.descuento) != 1 || !isInFloatRange(&DatosProveedor.descuento, 0, 1))
        {
            setColor(4);
            printf("\nERROR: Valor invalido para el descuento.\n");
            setColor(7);
            isInvalid = true;
        }
        else
            isInvalid = false;

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
    float precioUnitario, subtotalPorArticulo, porcentajeComision;
    DatosVentas.precioTotal = 0;

    time_t t = time(NULL);
    struct tm *fechaActual = localtime(&t);

    DatosVentas.year = fechaActual->tm_year + 1900;
    DatosVentas.month = fechaActual->tm_mon + 1;
    DatosVentas.day = fechaActual->tm_mday;

    do
    {
        printf("\nClave del empleado [1 - 1000] ~ ");
        fflush(stdin);

        if(scanf("%d", &DatosVentas.claveEmpleado) != 1 || !isInIntRange(&DatosVentas.claveEmpleado, 1, 1000))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Clave de empleado invalida.\n");
            setColor(7);
        }
        else if (!existeClave(4, &DatosVentas.claveEmpleado))
        {
            isInvalid = true;

            do
            {
                setColor(4);
                printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el empleado? [s/n]");
                setColor(7);
                fflush(stdin);

                if(scanf("%c", &opcionRegistrar) != 1)
                    opcionRegistrarInvalida = true;
                else
                {
                    opcionRegistrar = tolower(opcionRegistrar);
                    opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                }
                
                if (opcionRegistrarInvalida)
                {
                    setColor(4);
                    printf("ERROR. Respuesta invalida [s/n].\n");
                    setColor(7);   
                }

            } while(opcionRegistrarInvalida);
            
            if(opcionRegistrar == 's')
            {
                if((archivo_NuevoRegistro = fopen("Empleados.dat","rb+")) == NULL)
                {
                    setColor(4);
                    printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    setColor(7);
                }
                else
                {
                    lecturaEmpleado(archivo_NuevoRegistro);

                    fclose(archivo_NuevoRegistro);

                    if(existeClave(4, &DatosVentas.claveEmpleado))
                        isInvalid = false;
                    else
                    {
                        setColor(4);
                        printf("\nLa clave ingresada y el empleado registrado no coinciden, ingresala de nuevo.\n");
                        setColor(7);

                    }
                }
            }
        }
        else
            isInvalid = false;
            
    } while (isInvalid);

    do
    {
        printf("\nClave del mercado [1 - 100] ~ ");
        fflush(stdin);

        if(scanf("%d", &DatosVentas.claveMercado) != 1 || !isInIntRange(&DatosVentas.claveMercado, 1, 100))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Clave de mercado invalida.\n");
            setColor(7);
        }
        else if (!existeClave(3, &DatosVentas.claveMercado))
        {
            isInvalid = true;

            do
            {
                setColor(4);
                printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el mercado? [s/n]");
                setColor(7);
                fflush(stdin);

                if(scanf("%c", &opcionRegistrar) != 1)
                    opcionRegistrarInvalida = true;
                else
                {
                    opcionRegistrar = tolower(opcionRegistrar);
                    opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                }
                
                if (opcionRegistrarInvalida)
                {
                    setColor(4);
                    printf("ERROR. Respuesta invalida [s/n].\n");
                    setColor(7);
                }

            } while(opcionRegistrarInvalida);
            
            if(opcionRegistrar == 's')
            {
                if((archivo_NuevoRegistro = fopen("Mercados.dat","rb+")) == NULL)
                {   
                    setColor(4);
                    printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    setColor(7);
                }
                else
                {
                    lecturaMercado(archivo_NuevoRegistro);

                    fclose(archivo_NuevoRegistro);

                    if(existeClave(3, &DatosVentas.claveMercado))
                        isInvalid = false;
                    else
                    {
                        setColor(4);
                        printf("\nLa clave ingresada y el mercado registrado no coinciden, ingresala de nuevo.\n");
                        setColor(7);

                    }
                }
            }
        }
        else    
            isInvalid = false;
            
    } while (isInvalid);


    fprintf(archivoVentas, "%d-%d-%d-%d-%d#", 
                            DatosVentas.claveMercado, 
                            DatosVentas.claveEmpleado,
                            DatosVentas.day, 
                            DatosVentas.month, 
                            DatosVentas.year);

    do
    {
        precioUnitario = 0;
        subtotalPorArticulo = 0;

        do
        {
            printf("\nIngrese la clave del articulo [1 - 1000] ~ ");
            fflush(stdin);

            if(scanf("%d", &DatosVentas.claveArticulo) != 1 || !isInIntRange(&DatosVentas.claveArticulo, 1, 1000))
            {
                isInvalid = true;
                setColor(4);
                printf("\nERROR: Clave de articulo invalida.\n");
                setColor(7);
            }
            else if (!existeClave(1, &DatosVentas.claveArticulo))
            {
                isInvalid = true;

                do
                {
                    setColor(4);
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el articulo? [s/n]\n");
                    setColor(7);
                    fflush(stdin);

                    if(scanf("%c", &opcionRegistrar) != 1)
                        opcionRegistrarInvalida = true;
                    else
                    {
                        opcionRegistrar = tolower(opcionRegistrar);
                        opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                    }
                    
                    if (opcionRegistrarInvalida)
                    {
                        setColor(4);
                        printf("ERROR. Respuesta invalida [s/n].\n");
                        setColor(7);

                    }

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("Articulos.dat","rb+")) == NULL)
                    {
                        setColor(4);
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                        setColor(7);

                    }
                    else
                    {
                        lecturaArticulo(archivo_NuevoRegistro);

                        fclose(archivo_NuevoRegistro);

                        if(existeClave(1, &DatosVentas.claveArticulo))
                            isInvalid = false;
                        else
                            setColor(4);
                            printf("\nLa clave ingresada y el articulo registrado no coinciden, ingresala de nuevo.\n");
                            setColor(7);
                    }
                }
            }
            else if(inventarioRestante(&DatosVentas.claveArticulo) == 0)
            {
                isInvalid = true;
                printf("\nEl inventario actual de este articulo esta vacio.\n");
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
                setColor(4);
                printf("\nERROR: Cantidad invalida.\n");
                setColor(7);
            } 
            else if ((inventarioActual = inventarioRestante(&DatosVentas.claveArticulo)) < DatosVentas.cantidad)
            {
                isInvalid = true;
                printf("\nLa cantidad ingresada supera al inventario actual de este articulo, ingresa otra cantidad.\n");
                printf("Inventario actual: %d unidades\n", inventarioActual);
            }
            else
                isInvalid = false;

        } while (isInvalid);

        obtenerDatosArticulo(&DatosVentas.claveArticulo, &precioUnitario, DatosVentas.descripcion);

        subtotalPorArticulo = precioUnitario * DatosVentas.cantidad;
        DatosVentas.precioTotal += subtotalPorArticulo;

        printf("\nDescripcion del articulo: %s\n", DatosVentas.descripcion);
        printf("Precio unitario del articulo: %.2f\n", precioUnitario);
        printf("Subtotal de este articulo: %.2f\n", subtotalPorArticulo);
        printf("\nSubtotal actual de la compra: %.2f\n", DatosVentas.precioTotal);

        fprintf(archivoVentas, "%d-%d", DatosVentas.claveArticulo, DatosVentas.cantidad);

        restarInventarioArticulos(&DatosVentas.claveArticulo, &DatosVentas.cantidad);

        do
        {
            printf("\nDesea agregar mas articulos a la venta? [s/n] ~ ");
            fflush(stdin);

            if(scanf("%c", &agregarMasArticulos) != 1)
                isInvalid = true;
            else
            {
                agregarMasArticulos = tolower(agregarMasArticulos);
                isInvalid = agregarMasArticulos != 's' && agregarMasArticulos != 'n';
            }
            
            if (isInvalid)
                setColor(4);
                printf("ERROR. Respuesta invalida [s/n].\n");
                setColor(7);

        } while (isInvalid);

        if(agregarMasArticulos == 's')
            fprintf(archivoVentas, "#");
        else
            fprintf(archivoVentas, "*");
        
    } while (agregarMasArticulos == 's');

    printf("\nSubtotal de la venta: $%.2f", DatosVentas.precioTotal);

    DatosVentas.descuento = obtenerDescuento(&DatosVentas.claveMercado, 2);
    DatosVentas.precioTotal *= 1 - DatosVentas.descuento;
    porcentajeComision = obtenerComision(&DatosVentas.claveEmpleado);
    DatosVentas.comision *= porcentajeComision;

    printf("\nDescuento para este cliente: %.2f", DatosVentas.descuento);
    printf("\nTotal de la venta: $%.2f", DatosVentas.precioTotal);

    fprintf(archivoVentas, "%f~%f$", DatosVentas.precioTotal, DatosVentas.comision);

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
        printf("\nIngrese la clave del proveedor [1 - 100] ~ ");
        fflush(stdin);
        
        if(scanf("%d", &DatosCompra.claveProveedor) != 1 || !isInIntRange(&DatosCompra.claveProveedor, 1, 100))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Clave de proveedor invalida.\n");
            setColor(7);
        }
        else if (!existeClave(5, &DatosCompra.claveProveedor))
        {
            isInvalid = true;

            do
            {
                setColor(4);
                printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el proveedor? [s/n] ~ ");
                setColor(7);
                fflush(stdin);

                if(scanf("%c", &opcionRegistrar) != 1)
                    opcionRegistrarInvalida = true;
                else
                {
                    opcionRegistrar = tolower(opcionRegistrar);
                    opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                }
                
                if (opcionRegistrarInvalida)
                {
                    setColor(4);
                    printf("ERROR. Respuesta invalida [s/n].\n");
                    setColor(7);

                }

            } while (opcionRegistrarInvalida);
            
            if(opcionRegistrar == 's')
            {
                if((archivo_NuevoRegistro = fopen("Proveedores.dat","rb+")) == NULL)
                {
                    setColor(4);
                    printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    setColor(7);
                }
                else
                {
                    lecturaProveedor(archivo_NuevoRegistro);
                    fclose(archivo_NuevoRegistro);

                    if (existeClave(5, &DatosCompra.claveProveedor))
                        isInvalid = false;
                    else
                    {
                        setColor(4);
                        printf("\nLa clave ingresada y el proveedor registrado no coinciden.\n");
                        setColor(7);

                    }
                }
            }
        }
        else    
            isInvalid = false;

    } while (isInvalid);


    fprintf(archivoCompras, "%d-0#", DatosCompra.claveProveedor);

    do
    {

        do
        {
            printf("\nIngrese la clave del insumo [1 - 100] ~ ");
            fflush(stdin);

            if(scanf("%d", &DatosCompra.claveInsumo) != 1 || !isInIntRange(&DatosCompra.claveInsumo, 1, 100))
            {
                isInvalid = true;
                setColor(4);
                printf("\nERROR: Clave de insumo invalida.\n");
                setColor(7);
            }
            else if (!existeClave(2, &DatosCompra.claveInsumo))
            {
                isInvalid = true;

                do
                {   
                    setColor(4);
                    printf("\nERROR: La clave ingresada no esta registrada.\nDesea registrar el insumo? [s/n] ~ ");
                    setColor(7);
                    fflush(stdin);
                    
                    if(scanf("%c", &opcionRegistrar) != 1)
                        opcionRegistrarInvalida = true;
                    else
                    {
                        opcionRegistrar = tolower(opcionRegistrar);
                        opcionRegistrarInvalida = opcionRegistrar != 's' && opcionRegistrar != 'n';
                    }
                    
                    if (opcionRegistrarInvalida)
                    {
                        setColor(4);
                        printf("ERROR. Respuesta invalida [s/n].\n");
                        setColor(7);
                    }

                } while(opcionRegistrarInvalida);
                
                if(opcionRegistrar == 's')
                {
                    if((archivo_NuevoRegistro = fopen("Insumos.dat","rb+")) == NULL)
                    {
                        setColor(4);
                        printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                        setColor(7);
                    }
                    else
                    {
                        lecturaInsumo(archivo_NuevoRegistro);

                        fclose(archivo_NuevoRegistro);

                        if(existeClave(2, &DatosCompra.claveInsumo))
                            isInvalid = false;
                        else
                        {
                            setColor(4);
                            printf("\nLa clave ingresada y el insumo registrado no coinciden, ingresala de nuevo.\n");
                            setColor(7);
                        }
                    }
                }
            }
            else if (!verificarProveedorInsumo(&DatosCompra.claveProveedor, &DatosCompra.claveInsumo))
            {
                isInvalid = true;
                setColor(4);
                printf("\nEste insumo no tiene a este proveedor registrado.\n");
                setColor(7);
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
                setColor(4);
                printf("\nERROR: Cantidad invalida.\n");
                setColor(7);
            } 
            else
                isInvalid = false;

        } while (isInvalid);

        obtenerDatosInsumo(&DatosCompra.claveProveedor, &DatosCompra.claveInsumo, &precioUnitario, DatosCompra.descripcion);

        subtotalPorInsumo = precioUnitario * DatosCompra.cantidad;
        DatosCompra.totalDeCompra += subtotalPorInsumo;

        printf("\nDescripcion del insumo: %s\n", DatosCompra.descripcion);
        printf("Precio unitario del insumo: %.2f\n", precioUnitario);
        printf("Subtotal de este insumo: %.2f\n", subtotalPorInsumo);
        printf("\nSubtotal actual de la compra: $%.2f\n", DatosCompra.totalDeCompra);


        fprintf(archivoCompras, "%s-%d-%d", DatosCompra.descripcion, DatosCompra.claveInsumo, DatosCompra.cantidad);

        do
        {
            printf("\nDesea agregar mas insumos a la compra? [s/n] ~ ");
            fflush(stdin);

            if(scanf("%c", &agregarMasInsumos) != 1)
                isInvalid = true;
            else
            {
                agregarMasInsumos = tolower(agregarMasInsumos);
                isInvalid = agregarMasInsumos != 's' && agregarMasInsumos != 'n';
            }
            
            if (isInvalid)
            {
                setColor(4);
                printf("ERROR. Respuesta invalida [s/n].\n");
                setColor(7);
            }

        } while (isInvalid);

        if(agregarMasInsumos == 's')
            fprintf(archivoCompras, "#");
        else
            fprintf(archivoCompras, "*");
        
    } while (agregarMasInsumos == 's');

    printf("\nSubtotal de la compra: $%.2f", DatosCompra.totalDeCompra);

    DatosCompra.descuento = obtenerDescuento(&DatosCompra.claveProveedor, 1);
    DatosCompra.totalDeCompra *= 1 - DatosCompra.descuento;

    printf("\nDescuento con este proveedor: %.2f", DatosCompra.descuento);
    printf("\nTotal de la compra: $%.2f", DatosCompra.totalDeCompra);

    modificarSaldo(&DatosCompra.claveProveedor, &DatosCompra.totalDeCompra, '+');

    fprintf(archivoCompras, "%f$", DatosCompra.totalDeCompra);
    printf("\n----------------- PAGO TOTAL DE LA COMPRA: %.2f\n", DatosCompra.totalDeCompra);
}

void controlInventario(FILE *archivoCompras)
{
    rewind(archivoCompras);
    struct infoCompra DatosCompra;
    int i = 0, claveProveedorBuscado, claveCompraBuscada, claveInsumo, cantidadInsumo, resultados = 0;
    bool isInvalid, letreroImpreso = false;
    char separador, marcarEntrega;

    printf("\t----- CONTROL DE INVENTARIO ----- \n\n");

    do
    {
        printf("\nIngrese la clave del proveedor [1 - 100] ~ ");
        fflush(stdin);
        
        if(scanf("%d", &claveProveedorBuscado) != 1 || !isInIntRange(&claveProveedorBuscado, 1, 100))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: Clave de proveedor invalida.\n");
            setColor(7);

        }
        else if (!existeClave(5, &claveProveedorBuscado))
        {
            isInvalid = true;
            setColor(4);
            printf("\nERROR: La clave ingresada no esta registrada.\n");
            setColor(7);
        }
        else    
            isInvalid = false;

    } while (isInvalid);

    while (fscanf(archivoCompras, "%d-%d%c", &DatosCompra.claveProveedor, &DatosCompra.entregado, &separador) == 3)
    {
        if (DatosCompra.entregado == 0 && DatosCompra.claveProveedor == claveProveedorBuscado)
        {
            if (!letreroImpreso)
            {
                printf("\nCompras con entrega pendiente para el proveedor con clave: %d\n", DatosCompra.claveProveedor);
                printf("\n| %15s | %15s | %50s | %15s |\n", "ID COMPRA", "INSUMO", "DESCRIPCION", "CANTIDAD");
                printf(" ___________________________________________________________________________________________________________\n");
                letreroImpreso = true;
            }

            
            while (separador == '#')
            {
                if (fscanf(archivoCompras, "%[^-]-%d-%d%c", DatosCompra.descripcion, &DatosCompra.claveInsumo, &DatosCompra.cantidad, &separador) == 4)
                {
                    printf("| %15d | %15d | %50s | %15d |\n", i + 1, DatosCompra.claveInsumo, DatosCompra.descripcion, DatosCompra.cantidad);
                }
            }

            
            if (separador == '*')
            {
                fscanf(archivoCompras, "%f$", &DatosCompra.totalDeCompra);
                printf("%80s: $%.2f\n", "TOTAL DE COMPRA", DatosCompra.totalDeCompra);
                printf(" -----------------------------------------------------------------------------------------------------------\n");
            }
            
            resultados ++;
        }
        else
        {
            fscanf(archivoCompras, "%*[^$]$");
        }
        i++;
    }

    printf("\n\tResultados de la busqueda: %d\n", resultados);

    if (resultados > 0)
    {
        do
        {
            printf("\nIngrese la clave de la compra ~ ");
            fflush(stdin);
            
            if(scanf("%d", &claveCompraBuscada) != 1 || !isInIntRange(&claveCompraBuscada, 1, i))
            {
                isInvalid = true;
                setColor(4);
                printf("ERROR: Clave de compra fuera del rango.\n\n");
                setColor(7);

            }
            else    
            {
                rewind(archivoCompras);

                for (i = 0; i < claveCompraBuscada - 1; i++)
                {
                    fscanf(archivoCompras, "%*[^$]$");
                }
                
                fscanf(archivoCompras, "%d-%d", &DatosCompra.claveProveedor, &DatosCompra.entregado);

                if(DatosCompra.claveProveedor != claveProveedorBuscado)
                {
                    isInvalid = true;
                    setColor(4);
                    printf("ERROR: Clave de compra no coincide con el proveedor ingresado.\n\n");
                    setColor(7);
                }
                else
                    isInvalid = false;
            }

        }
        while(isInvalid);

        if (DatosCompra.entregado == 0)
        {
            do
            {
                printf("Marcar como entregada? [s/n] ~ ");
                fflush(stdin);

                if(scanf("%c", &marcarEntrega) != 1 || (marcarEntrega != 's' && marcarEntrega != 'n'))
                {
                    setColor(4);
                    printf("Respuesta invalida [s/n].\n");
                    setColor(7);
                    isInvalid = true;
                }
                else
                    isInvalid = false;
                
            } while (isInvalid);

            if (marcarEntrega == 's')
            {
                fseek(archivoCompras, -1, SEEK_CUR);
                fprintf(archivoCompras, "1");

                fflush(archivoCompras);
                fseek(archivoCompras, 0, SEEK_CUR);

                fscanf(archivoCompras, "%c", &separador);

                while (separador == '#')
                {
                    if (fscanf(archivoCompras, "%*[^-]-%d-%d%c", &claveInsumo, &cantidadInsumo, &separador) == 3)
                    {
                        agregarInventarioInsumos(&claveInsumo, &cantidadInsumo);
                    }
                }

                fscanf(archivoCompras, "%f$", &DatosCompra.totalDeCompra);
                modificarSaldo(&DatosCompra.claveProveedor, &DatosCompra.totalDeCompra, '-');
                

                printf("\nENTREGA DE COMPRA REGISTRADA.\n");
            }
            else
            {
                printf("\nRegresando al menu de reportes ...\n");
            }
        }
        else
        {
            setColor(4);
            printf("\nCLAVE INVALIDA. Esta compra ya se ha entregado.\n");
            setColor(7);
        }
    }
}
