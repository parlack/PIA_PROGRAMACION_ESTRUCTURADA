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