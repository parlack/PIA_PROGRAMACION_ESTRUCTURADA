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
            printf("%-7d %-50s ", DatosArticulo.clave, DatosArticulo.descripcion);

            switch(DatosArticulo.temporadaSiembra)
            {
                case 1:
                    printf("Primavera %-11s", " ");
                    break;
                case 2:
                    printf("Verano %-14s", " ");
                    break;
                case 3:
                    printf("Oto%co %-15s",164 , " ");
                    break;
                case 4:
                    printf("Invierno %-12s", " ");
                    break;
            }

            switch(DatosArticulo.temporadaCosecha)
            {
                case 1:
                    printf("Primavera %-11s", " ");
                    break;
                case 2:
                    printf("Verano %-14s", " ");
                    break;
                case 3:
                    printf("Oto%co %-15s",164 , " ");
                    break;
                case 4:
                    printf("Invierno %-12s", " ");
                    break;
            }

            printf("%-12d %-18.2f %-18.2f ", DatosArticulo.inventario, 
                    DatosArticulo.costoProduccion, DatosArticulo.precioVenta);
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


    if ((archivoCompras = fopen("Compras.txt", "r")) == NULL)
    {
        setColor(4);
        printf("Error al calcular las comisiones de los empleados.\n");
        setColor(7);
    }
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
    bool letreroImpreso = false;

    if ((archivoVentas = fopen("Ventas.txt", "r")) == NULL)
    {
        setColor(4);
        printf("Error al calcular las comisiones de los empleados.\n");
        setColor(7);

    }
    else
    {

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
                    if(!letreroImpreso)
                    {
                        printf("\nTOTAL DE COMISIONES POR EMPLEADO\n\n");
                        printf("| %15s | %-15s |\n", "ID EMPLEADO", "COMISION");
                        printf("-------------------------------------\n");
                        letreroImpreso = true;
                    }

                    printf("| %15d | $%-15.3f|\n", DatosEmpleado.clave, totalPorEmpleado);
                }
                rewind(archivoVentas);
            }
        }

        if(!letreroImpreso)
            printf("\nNo se encontraron empleados con comisi%cn.\n",162);

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
                setColor(4);
                printf("\nERROR: Dia invalido.\n");
                setColor(7);
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
                setColor(4);
                printf("\nERROR: Mes invalido.\n");
                setColor(7);
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
                setColor(4);
                printf("\nERROR: A%co invalido.\n", 164);
                setColor(7);
                isInvalid = true;
            }
            else
                isInvalid = false;

        } while(isInvalid);

        isInvalid = !validarFecha(&diaBuscado, &mesBuscado, &anioBuscado);

        if (isInvalid)
        {

            setColor(4);
            printf("\nERROR: Fecha invalida.\n");
            setColor(7);
        }

    } while(isInvalid);

    while(fscanf(archivoVentas, "%*[^-]-%*[^-]-%d-%d-%d%*[^*]*%f", &diaRegistro, &mesRegistro, &anioRegistro, &venta) == 4)
    {
        if(diaRegistro == diaBuscado && mesRegistro == mesBuscado && anioRegistro == anioBuscado)
            total += venta;
    }

    printf("\nTotal de ventas de la fecha %d/%d/%d: $%.2f\n", diaBuscado, mesBuscado, anioBuscado, total);
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
            setColor(4);
            printf("ERROR: Articulo invalido.\n\n");
            setColor(7);
            isInvalid = true;
        }
        else if(!existeClave(1, &articuloBuscado))
        {
            setColor(4);
            printf("ERROR: Articulo buscado no esta registrado.\n\n");
            setColor(7);
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
    struct infoProveedor proveedoresConSaldos[100];
    int CantidadSaldos = 0;
    char nombreCompleto[80];

    
    while (fread(&infoProv, sizeof(struct infoProveedor), 1, ArchivoProv))
    {
        if (infoProv.saldo != 0)
        {
            proveedoresConSaldos[CantidadSaldos++] = infoProv;
        }
    }

    
    if (CantidadSaldos > 0)
    {
        printf("\tINFORMACION DE PROVEEDORES CON SALDOS PENDIENTES:\n\n");
        printf("%-10s %-60s %-40s %s\n", "CLAVE", "NOMBRE CLIENTE", "SALDO PENDIENTE", "DIRECCION");
        printf("-------------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < CantidadSaldos; i++)
        {
            snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s %s",
                     proveedoresConSaldos[i].datosPersonales.nombres,
                     proveedoresConSaldos[i].datosPersonales.apellidoPaterno,
                     proveedoresConSaldos[i].datosPersonales.apellidoMaterno);

            printf("%-10d %-60s %8.2f %40s %d,\n",
                   proveedoresConSaldos[i].clave,
                   nombreCompleto,
                   proveedoresConSaldos[i].saldo,
                   proveedoresConSaldos[i].datosPersonales.calle,
                   proveedoresConSaldos[i].datosPersonales.numeroDomicilio);

            printf("%114s%s,\n", "", proveedoresConSaldos[i].datosPersonales.colonia);
            printf("%114s%s,\n", "", proveedoresConSaldos[i].datosPersonales.municipio);
            printf("%114s%s.\n\n", "", proveedoresConSaldos[i].datosPersonales.estado);
        }
    }
    else
    {
        printf("No existen cuentas con saldos pendientes.");
    }
}



void generarFactura(FILE *archivoVentas)
{
    FILE *filePtr;
    struct infoVenta ventaActual;
    struct infoMercado mercadoActual;
    struct infoEmpleado empleadoActual;
    char c, separador;
    int contador = 0;
    float precioUnitario, total = 0;

    fseek(archivoVentas, 0, SEEK_END);
    long pos = ftell(archivoVentas);


    while (pos > 0 && contador < 2)
    {
        fseek(archivoVentas, --pos, SEEK_SET);
        c = fgetc(archivoVentas);

        if (c == '$')
        {
            contador++;
            if (contador == 2)
            {
                fseek(archivoVentas, pos + 1, SEEK_SET);
            }
        }
    }

    
    if (contador < 2)
    {
        fseek(archivoVentas, 0, SEEK_SET);
    }

    fscanf(archivoVentas, "%d-%d-%d-%d-%d%c", 
                            &ventaActual.claveMercado,
                            &ventaActual.claveEmpleado,
                            &ventaActual.day, 
                            &ventaActual.month, 
                            &ventaActual.year, 
                            &separador);


    if ((filePtr = fopen("Mercados.dat", "rb")) == NULL)
    {
        setColor(4);
        printf("No se pudo abrir el archivo de mercados\n");
        setColor(7);   
    }
    else
    {
        fseek(filePtr, (ventaActual.claveMercado - 1) * sizeof(struct infoMercado), SEEK_SET);
        fread(&mercadoActual, sizeof(struct infoMercado), 1, filePtr);
        fclose(filePtr);
    }

    if ((filePtr = fopen("Empleados.dat", "rb")) == NULL)
    {
        setColor(4);
        printf("No se pudo abrir el archivo de empleados\n");
        setColor(7);
    }
    else
    {
        fseek(filePtr, (ventaActual.claveEmpleado - 1) * sizeof(struct infoEmpleado), SEEK_SET);
        fread(&empleadoActual, sizeof(struct infoEmpleado), 1, filePtr);
        fclose(filePtr);
    }

    
    printf("\n=====================================\n");
    printf("              FACTURA                \n");
    printf("=====================================\n");
    printf("Negocio: Granja S.A.\n");
    printf("-------------------------------------\n");
    printf("Cliente: %s %s %s\n", mercadoActual.datosPersonales.nombres,
                                mercadoActual.datosPersonales.apellidoPaterno,
                                mercadoActual.datosPersonales.apellidoMaterno);
    printf("RFC del cliente: %s\n", mercadoActual.datosPersonales.RFC);
    printf("Fecha de venta: %02d/%02d/%d\n", ventaActual.day, ventaActual.month, ventaActual.year);
    printf("-------------------------------------\n");
    printf("Vendedor: %s %s %s\n", empleadoActual.datosPersonales.nombres,
                                empleadoActual.datosPersonales.apellidoPaterno,
                                empleadoActual.datosPersonales.apellidoMaterno);
    printf("RFC del vendedor: %s\n", empleadoActual.datosPersonales.RFC);
    printf("-------------------------------------\n");
    printf("%-5s | %-5s | %-20s | %-8s | %-10s\n", "Cant.", "Clave", "Descripcion", "P.Unit", "Subtotal");
    while (separador == '#')
    {
        fscanf(archivoVentas, "%d-%d%c", &ventaActual.claveArticulo, &ventaActual.cantidad, &separador);
        obtenerDatosArticulo(&ventaActual.claveArticulo, 
                            &precioUnitario, 
                            ventaActual.descripcion);

        printf("%-5d | %-5d | %-20s | %-8.2f | %-8.2f\n", ventaActual.cantidad,
                                ventaActual.claveArticulo, 
                                ventaActual.descripcion, 
                                precioUnitario, 
                                ventaActual.cantidad * precioUnitario);
        total += ventaActual.cantidad * precioUnitario;
    }

    fscanf(archivoVentas, "%f~%f$", &ventaActual.precioTotal, &ventaActual.comision);
    printf("-------------------------------------\n");
    printf("%-35s $%-10.2f\n", "Subtotal de la compra:", total);
    printf("%-35s $%-10.2f\n", "Subtotal con descuento aplicado:", ventaActual.precioTotal);
    printf("%-35s $%-10.2f\n", "IVA (0.16):", ventaActual.precioTotal * 0.16);
    printf("%-35s $%-10.2f\n", "Total:", ventaActual.precioTotal * 1.16);
}


