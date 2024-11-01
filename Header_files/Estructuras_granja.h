#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct infoDatosPersonales
{
	int year, month, day, numeroDomicilio;
    char nombres[31],
         apellidoPaterno[31],
         apellidoMaterno[31],
         RFC[14], correo[51],
         calle[41], colonia[41],
         municipio[41], estado[41];
};
    
struct infoArticulo
{
	int clave, clavesMercados[11], clavesInsumos[11], inventario;
	char descripcion[51], temporadaSiembra[21], temporadaCosecha[21];
	float costoProduccion, precioVenta;
};

struct infoInsumo
{
	int clave, clavesProveedores[11], puntoReorden, inventario;
	char descripcion[51];
	float precioSurtido[11];
};

struct infoProveedor
{
    int clave;
    struct infoDatosPersonales datosPersonales;
    float descuento;
};

struct infoMercado
{
    int clave;
    struct infoDatosPersonales datosPersonales;
    float descuento;
};

struct infoEmpleado
{
    int clave, yearContratacion, monthContratacion, dayContratacion;
    struct infoDatosPersonales datosPersonales;
    float comision;
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
    struct infoDatosPersonales datosVacios = {0, 0, 0, 0,"", "", "", "", "", "", "", "", ""};
    void *estructuraVacia;
    size_t sizeEstructura;

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
			nombreArchivo = "./Data_files/Mercados.dat";
            struct infoMercado mercadoVacio = {0, datosVacios, 0};
            estructuraVacia = &mercadoVacio;
            sizeEstructura = sizeof(mercadoVacio);
            break;
        }
        case 4:
		{
			n_registros = 1000;
			nombreArchivo = "./Data_files/Empleados.dat";
            struct infoEmpleado empleadoVacio = {0, 0, 0, 0, datosVacios, 0};
            estructuraVacia = &empleadoVacio;
            sizeEstructura = sizeof(empleadoVacio);
            break;
        }
        case 5:
		{
			n_registros = 100;
			nombreArchivo = "./Data_files/Proveedores.dat";
            struct infoProveedor proveedorVacio = {0, datosVacios, 0};
            estructuraVacia = &proveedorVacio;
            sizeEstructura = sizeof(proveedorVacio);
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

bool existeClave(int numeroArchivo, int *clave_buscar)
{
    FILE *fPtr;
    char *nombreArchivo;
    void *estructuraPtr;
    size_t sizeEstructura;

    switch(numeroArchivo)
	{
        case 1:
		{
            struct infoArticulo articulo;
            estructuraPtr = &articulo;
			nombreArchivo = "./Data_files/Articulos.dat";
            sizeEstructura = sizeof(struct infoArticulo);
            break;
        }
        case 2:
		{
            struct infoInsumo insumo;
            estructuraPtr = &insumo;
			nombreArchivo = "./Data_files/Insumos.dat";
            sizeEstructura = sizeof(struct infoInsumo);
            break;
        }
        case 3:
		{
            struct infoMercado mercado;
            estructuraPtr = &mercado;
			nombreArchivo = "./Data_files/Mercados.dat";
            sizeEstructura = sizeof(struct infoMercado);
            break;
        }
        case 4:
		{
            struct infoEmpleado empleado;
            estructuraPtr = &empleado;
			nombreArchivo = "./Data_files/Empleados.dat";
            sizeEstructura = sizeof(struct infoEmpleado);
            break;
        }
        case 5:
		{
            struct infoProveedor proveedor;
            estructuraPtr = &proveedor;
			nombreArchivo = "./Data_files/Proveedores.dat";
            sizeEstructura = sizeof(struct infoProveedor);
            break;
        }
    }

    if((fPtr = fopen(nombreArchivo,"r")) == NULL)
        return false;
    
    fseek(fPtr, (*clave_buscar - 1) * sizeEstructura, SEEK_SET);

    if(fread(estructuraPtr, sizeEstructura, 1, fPtr))
    {
        switch (numeroArchivo)
        {
            case 1:
                return ((struct infoArticulo *)estructuraPtr)->clave != 0;
            case 2:
                return ((struct infoInsumo *)estructuraPtr)->clave != 0;
            case 3:
                return ((struct infoMercado *)estructuraPtr)->clave != 0;
            case 4:
                return ((struct infoEmpleado *)estructuraPtr)->clave != 0;
            case 5:
                return ((struct infoProveedor *)estructuraPtr)->clave != 0;
        }
    }
    
    fclose(fPtr);
    return false;
}

/*
bool IndicarHayRegistros(int numeroArchivo)
{
    FILE *archivoExistencias;
    bool valorInicial = false, valorEnArchivo;

    if((archivoExistencias = fopen("./Data_files/existenRegistros.dat", "rb")) == NULL)
    {
        if((archivoExistencias = fopen("./Data_files/existenRegistros.dat", "w")) == NULL)
            return false;
        else
        {
            for(int i = 0; i < 7; i++)
                fwrite(&valorInicial, sizeof(valorInicial), 1, archivoExistencias);
            
            fclose(archivoExistencias);
        }
    }
    else
        fclose(archivoExistencias);

    if((archivoExistencias = fopen("./Data_files/existenRegistros.dat", "rb+")) == NULL)
        return false;
    else
    {
        fseek(archivoExistencias, (numeroArchivo - 1) * sizeof(bool), SEEK_SET);
        fread(&valorEnArchivo, sizeof(valorEnArchivo), 1, archivoExistencias);

        if (!valorEnArchivo)
        {
            valorEnArchivo = true;
            fseek(archivoExistencias, (numeroArchivo - 1) * sizeof(bool), SEEK_SET);
            fwrite(&valorEnArchivo, sizeof(valorEnArchivo), 1, archivoExistencias);
        }
        
        fclose(archivoExistencias);
        return true;
    }
}
*/

bool VerificarHayRegistros(int numeroArchivo)
{
    FILE *archivoAVerificar;
    bool valorEnArchivo = false;
    char *nombreArchivo;

    switch(numeroArchivo)
    {
        case 1:
            nombreArchivo = "./Data_files/Articulos.dat";
            break;
        case 2:
            nombreArchivo = "./Data_files/Insumos.dat";
            break;
        case 3:
            nombreArchivo = "./Data_files/Mercados.dat";
            break;
        case 4:
            nombreArchivo = "./Data_files/Empleados.dat";
            break;
        case 5:
            nombreArchivo = "./Data_files/Proveedores.dat";
            break;
    }
    
    if ((archivoAVerificar = fopen(nombreArchivo, "rb")) == NULL) 
        return false;
    else 
        return true;
}

/*bool Modificar_VerArchivoExistencias(int numeroArchivo, bool modificar)
{
    FILE *archivoExistencias;
    bool valorInicial = false, valorEnArchivo, existenRegistros;

    if (modificar)
    {
        if((archivoExistencias = fopen("./Data_files/existenRegistros.dat", "rb")) == NULL)
        {
            if((archivoExistencias = fopen("./Data_files/existenRegistros.dat", "w")) == NULL)
                return false;
            else
            {
                for(int i = 0; i < 7; i++)
                    fwrite(&valorInicial, sizeof(valorInicial), 1, archivoExistencias);
                
                fclose(archivoExistencias);
            }
        }
        else
        {
            fclose(archivoExistencias);
        }

        if((archivoExistencias = fopen("./Data_files/existenRegistros.dat", "rb+")) == NULL)
            return false;
        else
        {
            fseek(archivoExistencias, numeroArchivo, SEEK_SET);
            fread(&valorEnArchivo, sizeof(valorEnArchivo), 1, archivoExistencias);

            if (!valorEnArchivo)
                valorEnArchivo = true;

            fseek(archivoExistencias, numeroArchivo, SEEK_SET);
            fwrite(&valorEnArchivo, sizeof(valorEnArchivo), 1, archivoExistencias);

            fclose(archivoExistencias);
            return true;
        }
    }
    else
    {
        if((archivoExistencias = fopen("./Data_files/existenRegistros.dat", "rb")) == NULL)
            return false;
        else
        {
            fseek(archivoExistencias, numeroArchivo, SEEK_SET);
            fread(&valorEnArchivo, sizeof(valorEnArchivo), 1, archivoExistencias);
            fclose(archivoExistencias);
        }
        return valorEnArchivo;
    }
}

*/


float obtenerCosto(int *Insumos, int *sizeInsumos)
{
    FILE *archivoInsumos;
    struct infoInsumo insumoActual;
    int i = 0, j;
    float costoTotal = 0, promedioCostoInsumo;

    if ((archivoInsumos = fopen("./Data_files/Insumos.dat", "rb")) == NULL)
        return 0;
 
    while (i < *sizeInsumos)
    {
        j = 0;
        promedioCostoInsumo = 0;
        fseek(archivoInsumos, (*(Insumos + i) - 1) * sizeof(insumoActual), SEEK_SET);
        fread(&insumoActual, sizeof(insumoActual), 1, archivoInsumos);

        while (*(insumoActual.precioSurtido + j) != 0 && j < 10)
        {
            promedioCostoInsumo += *(insumoActual.precioSurtido + j);
            j++;
        }

        promedioCostoInsumo /= j;
        
        costoTotal += promedioCostoInsumo;

        i++;
    }

    fclose(archivoInsumos);
    
    return costoTotal;
}
