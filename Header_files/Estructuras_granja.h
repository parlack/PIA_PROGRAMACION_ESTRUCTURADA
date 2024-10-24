#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct infoDireccion
{
    char calle[40], colonia[40], municipio[40], estado[40];
    int numero;
};
    
struct infoArticulo
{
	int clave, clavesMercado[10], clavesInsumos[10], inventario;
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
    int clave, year, month, day;
    char nombre[50], RFC[14], correo[50];
    float descuento;
    struct infoDireccion direccion;
};

struct infoMercado
{
    int clave, year, month, day;
    char nombre[50], RFC[14], correo[50];
    float descuento;
    struct infoDireccion direccion;
};

struct infoEmpleado
{
    int clave, year, month, day;
    char nombre[50], RFC[14], correo[50];
    float comision;
	struct infoDireccion direccion;
};

bool inicializarArchivo(int numeroArchivo)
{
    FILE *fPtr;
    int i, n_registros;
    char *nombreArchivo;
    struct infoDireccion direccionVacia = {"", "", "", "", 0};

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
            struct infoProveedor proveedorVacio = {0, 0, 0, 0, "", "", "", 0, direccionVacia};
            estructuraVacia = &proveedorVacio;
            sizeEstructura = sizeof(proveedorVacio);
            break;
        }
        case 4:
		{
			n_registros = 100; //Temporal
			nombreArchivo = "./Data_files/Mercados.dat";
            struct infoMercado mercadoVacio = {0, 0, 0, 0, "", "", "", 0, direccionVacia};
            estructuraVacia = &mercadoVacio;
            sizeEstructura = sizeof(mercadoVacio);
            break;
        }
        case 5:
		{
			n_registros = 1000;
			nombreArchivo = "./Data_files/Empleados.dat";
            struct infoEmpleado empleadoVacio = {0, 0, 0, 0, "", "", "", 0, direccionVacia};
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



