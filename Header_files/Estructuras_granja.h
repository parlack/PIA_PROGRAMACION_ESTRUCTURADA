#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct infoDireccion
{
    char calle[40], colonia[40], municipio[40], estado[40];
    int numero;
};

struct infoDatosPersonales
{
	int year, month, day;
    char nombres[30], apellidoPaterno[30], apellidoMaterno[30], RFC[14], correo[50];
};
    
struct infoArticulo
{
	int clave, clavesMercados[10], clavesInsumos[10], inventario;
	char descripcion[50], temporadaSiembra[20], temporadaCosecha[20];
	float costoProduccion, precioVenta;
};

struct infoInsumo
{
	int clave, clavesProveedores[10], puntoReorden, inventario;
	char descripcion[50];
	float precioSurtido[10];
};

struct infoProveedor
{
    int clave;
    struct infoDatosPersonales datosPersonales;
    float descuento;
    struct infoDireccion direccion;
};

struct infoMercado
{
    int clave;
    struct infoDatosPersonales datosPersonales;
    float descuento;
    struct infoDireccion direccion;
};

struct infoEmpleado
{
    int clave;
    struct infoDatosPersonales datosPersonales;
    float comision;
    struct infoDireccion direccion;
};

struct infoVenta
{
	int claveMercado, claveArticulo, claveEmpleado, cantidad;
	float precioTotal;
	bool solicitaFactura;
};

struct infoCompra
{
	int claveProveedor, claveInsumo, cantidad;
	float precioTotal;
};

bool inicializarArchivo(int numeroArchivo)
{
    FILE *fPtr;
    int i, n_registros;
    char *nombreArchivo;
    struct infoDireccion direccionVacia = {"", "", "", "", 0};
    struct infoDatosPersonales datosVacios = {0, 0, 0, "", "", "", "", ""};

    void *estructuraVacia;
    size_t sizeEstructura = 0;

    switch(numeroArchivo)
	{
        case 1:
		{
			n_registros = 1000;
			nombreArchivo = "./Data_files/Articulos.dat";
            struct infoArticulo articuloVacio = {0, {0}, {0}, 0, "", "", "", 0, 0};
            estructuraVacia = &articuloVacio;
            sizeEstructura = sizeof(articuloVacio);
            break;
        }
        case 2:
		{
			n_registros = 100;
			nombreArchivo = "./Data_files/Insumos.dat";
            struct infoInsumo insumoVacio = {0, {0}, 0, 0, "", {0}};
            estructuraVacia = &insumoVacio;
            sizeEstructura = sizeof(insumoVacio);
            break;
        }
        case 3:
		{
			n_registros = 100;
			nombreArchivo = "./Data_files/Proveedores.dat";
            struct infoProveedor proveedorVacio = {0, datosVacios, 0, direccionVacia};
            estructuraVacia = &proveedorVacio;
            sizeEstructura = sizeof(proveedorVacio);
            break;
        }
        case 4:
		{
			n_registros = 100; //Temporal
			nombreArchivo = "./Data_files/Mercados.dat";
            struct infoMercado mercadoVacio = {0, datosVacios, 0, direccionVacia};
            estructuraVacia = &mercadoVacio;
            sizeEstructura = sizeof(mercadoVacio);
            break;
        }
        case 5:
		{
			n_registros = 1000;
			nombreArchivo = "./Data_files/Empleados.dat";
            struct infoEmpleado empleadoVacio = {0, datosVacios, 0, direccionVacia};
            estructuraVacia = &empleadoVacio;
            sizeEstructura = sizeof(empleadoVacio);
            break;
        }
    }

    if((fPtr = fopen(nombreArchivo, "r")) == NULL)
	{
        if((fPtr = fopen(nombreArchivo, "w")) == NULL)
            return false;
        else
		{
            for(i = 0; i < n_registros; i++)
                fwrite(estructuraVacia, sizeEstructura, 1, fPtr);
                
            fclose(fPtr);
            return true;
        }
    }
	else
	{
        fclose(fPtr);
        return true;
    }
}


bool existeMercado(int *key)
{
    FILE *archivoMercados;
    struct infoMercado mercadoActual;
    bool existe;

    if ((archivoMercados = fopen("./Data_files/Mercados.dat", "rb")) == NULL)
        return false;
    else
    {
        fseek(archivoMercados, (*key - 1) * sizeof(mercadoActual), SEEK_SET);
        fread(&mercadoActual, sizeof(mercadoActual), 1, archivoMercados);

        if(mercadoActual.clave == 0)
            existe = false;
        else
            existe = true;
        
        fclose(archivoMercados);
    }
    return existe;
}

bool existeInsumo(int *key)
{
    FILE *archivoInsumos;
    struct infoInsumo insumoActual;
    bool existe;

    if ((archivoInsumos = fopen("./Data_files/Insumos.dat", "rb")) == NULL)
        return false;
    else
    {
        fseek(archivoInsumos, (*key - 1) * sizeof(insumoActual), SEEK_SET);
        fread(&insumoActual, sizeof(insumoActual), 1, archivoInsumos);

        if(insumoActual.clave == 0)
            existe = false;
        else
            existe = true;

        fclose(archivoInsumos);
    }
    return existe;
}

/*
float obtenerCosto(int *Insumos)
{
    FILE *archivoInsumos;
    struct infoInsumo insumoActual;
    int i;
    float costoTotal = 0;

    if ((archivoInsumos = fopen("./Data_files/Insumos.dat", "rb")) == NULL)
        return 0;
    else
    {
        
        while (*(Insumos + i) != 0)
        {
            fseek(archivoInsumos, (*(Insumos + i) - 1) * sizeof(insumoActual), SEEK_SET);
            fread(&insumoActual, sizeof(insumoActual), 1, archivoInsumos);

            costoTotal += insumoActual.precioSurtido;
        }

        fclose(archivoInsumos);
    }
    
    return costoTotal;
}
*/
