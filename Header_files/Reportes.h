#include <stdio.h>
#include <stdbool.h>
#include "Lecturas.h"

void reporteArticulos(FILE *archivoArticulos)
{
    int i, articulosimpresos = 0;
    struct infoArticulo DatosArticulo;

    printf("LISTA DE ARTICULOS:\n");
    printf("%-7s %-50s %-20s %-20s %-12s %-18s %-18s %-20s %-20s\n", 
           "Clave", "Descripcion", "Temporada Siembra", 
           "Temporada Cosecha", "Inventario", "Costo Produccion", 
           "Precio Venta", "Claves Mercados", "Claves Insumos");

    while(fread(&DatosArticulo, sizeof(struct infoArticulo), 1, archivoArticulos))
    {
        if(DatosArticulo.clave != 0)
        {
            printf("%-7d %-50s %-20s %-20s %-12d %-18.2f %-18.2f ", 
               DatosArticulo.clave, DatosArticulo.descripcion, 
               DatosArticulo.temporadaSiembra, DatosArticulo.temporadaCosecha, 
               DatosArticulo.inventario, DatosArticulo.costoProduccion, 
               DatosArticulo.precioVenta);
            printf("%-21d", DatosArticulo.clavesMercados[0]);
            printf("%-5d \n", DatosArticulo.clavesInsumos[0]);

            for (i = 1; i < 10; i++) 
            {
                if ((DatosArticulo.clavesMercados[i] != 0) || (DatosArticulo.clavesInsumos[i] != 0)) 
                {
                    if(DatosArticulo.clavesMercados[i] == 0)
                        printf("%153s"," ");
                    else
                        printf("%153d", DatosArticulo.clavesMercados[i]);
                    
                    if(DatosArticulo.clavesInsumos[i] == 0)
                        printf("%21s\n", " ");
                    else
                        printf("%21d \n", DatosArticulo.clavesInsumos[i]);

                    
                } 
            }
            printf("\n");
            articulosimpresos++;
        }
    }



}

void insumosPorSolicitar(FILE *archivoInsumos)
{
    FILE *archivoCompras;
    struct infoInsumo DatosInsumo;
    struct infoCompra DatosCompra;
    int i, j;
    bool insumoEncontrado, letreroImpreso = false;
    char separador;


    if ((archivoCompras = fopen("Data_files/Compras.txt", "r")) == NULL)
        printf("Error al calcular las comisiones de los empleados.\n");
    else
    {
        for (i = 0; i < 100; i++)
        {
            insumoEncontrado = false;
            fseek(archivoInsumos, i * sizeof(struct infoInsumo), SEEK_SET);
            fread(&DatosInsumo, sizeof(struct infoInsumo), 1, archivoInsumos);
            if (DatosInsumo.clave != 0 && DatosInsumo.inventario <= DatosInsumo.puntoReorden)
            {
                while (fscanf(archivoCompras, "%d-%d%c", 
                            &DatosCompra.claveProveedor, 
                            &DatosCompra.entregado, 
                            &separador) == 3 
                            && insumoEncontrado == false)
                {
                    if (DatosCompra.entregado == 0)
                    {   
                        while (separador == '#')
                        {
                            fscanf(archivoCompras, "%[^-]-%d-%d%c", 
                                DatosCompra.descripcion, 
                                &DatosCompra.claveInsumo, 
                                &DatosCompra.cantidad, 
                                &separador);
                            if (DatosCompra.claveInsumo == DatosInsumo.clave)
                            {
                                insumoEncontrado = true;
                            }
                        }

                        fscanf(archivoCompras, "%*f$");
                    }
                }
                
                if (!insumoEncontrado)
                {
                    if(!letreroImpreso)
                    {
                        printf("\n##### ARTICULOS A SOLICITAR #####\n\n");
                        printf("| %15s | %15s | %15s |\n", "CLAVE INSUMO", "DESCRIPCION", "PROVEEDORES");
                        printf("-------------------------------------------------------\n");
                        letreroImpreso = true;
                    }
                    printf("| %15s | %15d |", DatosInsumo.descripcion, DatosInsumo.clave);

                    j = 0;
                    while(j < 10 && DatosInsumo.clavesProveedores[j] != 0)
                    {
                        if (DatosInsumo.clavesProveedores[j] != 0)
                            printf(" %15d |", DatosInsumo.clavesProveedores[j]);
                        else
                            printf(" %15s |", " ");

                        j++;
                    }
                    printf("\n");
                }

                rewind(archivoCompras);
            }
        }

        if(!letreroImpreso)
        {
            printf("\n----- Busqueda realizada -----");
            printf("\n##### NO HAY ARTICULOS A SOLICITAR #####\n");
        }

        fclose(archivoCompras);
    }
}

void calculoDeComision(FILE *archivoEmpleados)
{
    FILE *archivoVentas;
    struct infoEmpleado DatosEmpleado;
    float totalPorEmpleado, monto;
    int claveEmpleadoVenta;
    int i;

    if ((archivoVentas = fopen("Data_files/Ventas.txt", "r")) == NULL)
        printf("Error al calcular las comisiones de los empleados.\n");
    else
    {
        printf("\nTOTAL DE COMISIONES POR EMPLEADO\n\n");
        printf("| %15s | %-15s |\n", "ID EMPLEADO", "COMISION");
        printf("-------------------------------------\n");

        for (i = 0; i < 1000; i++)
        {
            totalPorEmpleado = 0;
            fread(&DatosEmpleado, sizeof(struct infoEmpleado), 1, archivoEmpleados);

            if (DatosEmpleado.comision != 0)
            {
                while(fscanf(archivoVentas, "%*[^-]-%d-%*[^~]~%f", &claveEmpleadoVenta, &monto) == 2)
                    if (DatosEmpleado.clave == claveEmpleadoVenta)
                        totalPorEmpleado += monto;
                
                if (totalPorEmpleado != 0)
                {
                    printf("| %15d | $%-15.3f|\n", DatosEmpleado.clave, totalPorEmpleado);
                }
                rewind(archivoVentas);
            }
        }

        fclose(archivoVentas);
    }
}

void comprasConRecepcionPendiente(FILE *archivoCompras)
{
    struct infoCompra DatosCompra;
    int i = 0;
    int resultados = 0;
    bool isInvalid, letreroImpreso = false;
    char separador;

    while (fscanf(archivoCompras, "%d-%d%c", &DatosCompra.claveProveedor, &DatosCompra.entregado, &separador) == 3)
    {
        if (DatosCompra.entregado == 0)
        {
            if (!letreroImpreso)
            {
                printf("\nCOMPRAS CON RECEPCION PENDIENTE\n");
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
            resultados++;
        }
        i++;
    }

    if(letreroImpreso)
        printf("\nResultados: %d\n", resultados);
    else
        printf("\nNo hay resultados para esta busqueda. \n");
}

void ventasFecha(FILE *archivoVentas)
{
    int anioBuscado, mesBuscado, diaBuscado, diaRegistro, mesRegistro, anioRegistro;
    float venta, total = 0;
    bool isInvalid;

    do
    {
        do
        {
            printf("Dia de venta ~ ");
            fflush(stdin);

            if(scanf("%d", &diaBuscado) != 1)
            {
                printf("\nERROR: Dia invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while(isInvalid);

        do
        {
            printf("Mes de venta ~ ");
            fflush(stdin);

            if(scanf("%d", &mesBuscado) != 1)
            {
                printf("\nERROR: Mes invalido.\n");
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while(isInvalid);

        do
        {
            printf("A%co de venta ~ ", 164);
            fflush(stdin);

            if(scanf("%d", &anioBuscado) != 1)
            {
                printf("\nERROR: A%co invalido.\n", 164);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while(isInvalid);

        isInvalid = !validarFecha(&diaBuscado, &mesBuscado, &anioBuscado);

        if (isInvalid)
            printf("\nERROR: Fecha invalida.\n");

    } while(isInvalid);

    while(fscanf(archivoVentas, "%*[^-]-%*[^-]-%d-%d-%d%*[^*]*%f", &diaRegistro, &mesRegistro, &anioRegistro, &venta) == 4)
    {
        if(diaRegistro == diaBuscado && mesRegistro == mesBuscado && anioRegistro == anioBuscado)
            total += venta;
    }

    printf("\nTotal de ventas de la fecha %d/%d/%d: $%.2f\n", anioBuscado, mesBuscado, anioBuscado, total);
}

void ventasArticulo(FILE *archivoVentas)
{
    int articuloBuscado, articuloRegistro;
    float venta, total = 0;
    bool isInvalid;

    do
    {        
        printf("Clave del articulo a buscar ~ ");
        fflush(stdin);

        if(scanf("%d", &articuloBuscado) != 1)
        {
            printf("ERROR: Articulo invalido.\n\n");
            isInvalid = true;
        }
        else if(!existeClave(1, &articuloBuscado))
        {
            printf("ERROR: Articulo buscado no esta registrado.\n\n");
            isInvalid = true;
        }
        else
            isInvalid = false;

    } while(isInvalid);

    while(fscanf(archivoVentas, "%*[^#]#%d", &articuloRegistro) == 1)
    {
        if(articuloRegistro == articuloBuscado)
        {
            fscanf(archivoVentas, "%*[^*]*%f", &venta);
            total += venta;
        }
    }

    printf("\nTotal de ventas del articulo con clave %d: $%.2f\n", articuloBuscado, total);
}

void SaldosPendientes(FILE *ArchivoProv)
{
    struct infoProveedor infoProv;
    int CantidadSaldos = 0;
    char nombreCompleto[80]; // Cadena temporal para nombre completo

    while (fread(&infoProv, sizeof(struct infoProveedor), 1, ArchivoProv))
    {
        if (infoProv.saldo != 0)
        {
            if (CantidadSaldos == 0)
            {
                printf("\tINFORMACION DE PROVEEDORES CON SALDOS PENDIENTES:\n\n");
                printf("%-10s %-60s %-40s %s\n", "CLAVE", "NOMBRE CLIENTE", "SALDO PENDIENTE", "DIRECCION");
                printf("-------------------------------------------------------------------------------------------------------------\n");
            }

            // Concatenar nombre completo en una sola cadena
            snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s %s",
                     infoProv.datosPersonales.nombres,
                     infoProv.datosPersonales.apellidoPaterno,
                     infoProv.datosPersonales.apellidoMaterno);

            // Información básica de cada proveedor
            printf("%-10d %-60s %8.2f %40s %d,\n",
                   infoProv.clave,
                   nombreCompleto,
                   infoProv.saldo,
                   infoProv.datosPersonales.calle,
                   infoProv.datosPersonales.numeroDomicilio);

            // Imprimir las partes de la dirección alineadas debajo de la columna "DIRECCION"
            printf("%114s%s,\n", "", infoProv.datosPersonales.colonia);
            printf("%114s%s,\n", "", infoProv.datosPersonales.municipio);
            printf("%114s%s.\n\n", "", infoProv.datosPersonales.estado);

            CantidadSaldos++;
        }
    }

    if (CantidadSaldos == 0)
        printf("No existen cuentas con saldos pendientes.");
}

void generarFactura(FILE *archivoVentas)
{
    struct infoVenta ventaActual;
    rewind(archivoVentas);

    while (fscanf(archivoVentas, "%d-%d-%d-%d-%d#", 
                            DatosVentas.claveMercado, 
                            DatosVentas.claveEmpleado,
                            DatosVentas.day, 
                            DatosVentas.month, 
                            DatosVentas.year) == 5)
    {
        fscanf(archivoVentas, "%*[^$]$");
    }
}
