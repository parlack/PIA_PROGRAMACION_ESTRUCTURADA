#include <stdio.h>
#include <stdbool.h>
#include "Lecturas.h"
void ReporteArticulos(FILE *archivoArticulos)
{
    int i, articulosimpresos = 0;
    struct infoArticulo DatosArticulo;

    printf("LISTA DE ARTICULOS:\n");
    printf("%-7s %-50s %-20s %-20s %-12s %-18s %-18s %-20s %-20s\n", 
           "Clave", "Descripcion", "Temporada Siembra", 
           "Temporada Cosecha", "Inventario", "Costo Produccion", 
           "Precio Venta", "Claves Mercados", "Claves Insumos");

    for(i = 0; i < 1000; i++)
    {
        fseek(archivoArticulos, i * sizeof(struct infoArticulo), SEEK_SET);
        fread(&DatosArticulo, sizeof(struct infoArticulo), 1, archivoArticulos);

        if(DatosArticulo.clave != 0)
        {
            printf("%-7d %-50s %-20s %-20s %-12d %-18.2f %-18.2f ", 
               DatosArticulo.clave, DatosArticulo.descripcion, 
               DatosArticulo.temporadaSiembra, DatosArticulo.temporadaCosecha, 
               DatosArticulo.inventario, DatosArticulo.costoProduccion, 
               DatosArticulo.precioVenta);
            printf("%-21d", DatosArticulo.clavesMercados[0]);
            printf("%-5d \n", DatosArticulo.clavesInsumos[0]);

            for (int j = 1; j < 10; j++) 
            {
                if ((DatosArticulo.clavesMercados[j] != 0) || (DatosArticulo.clavesInsumos[j] != 0)) 
                {
                    if(DatosArticulo.clavesMercados[j] == 0)
                        printf("%153s"," ");
                    else
                        printf("%153d", DatosArticulo.clavesMercados[j]);
                    
                    if(DatosArticulo.clavesInsumos[j] == 0)
                        printf("%21s\n", " ");
                    else
                        printf("%21d \n", DatosArticulo.clavesInsumos[j]);

                    
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
                    //printf(" %15d | %15d |\n", DatosCompra.claveProveedor, DatosCompra.entregado);
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