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

            for (int j = 1; j < 11; j++) 
            {
                //if (DatosArticulo.clavesMercados[j] != 0) 
                //{
                    printf("%153d", DatosArticulo.clavesMercados[j]);
                    printf("%21d \n", DatosArticulo.clavesInsumos[j]);
               // } 
            }
            articulosimpresos++;
        }
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