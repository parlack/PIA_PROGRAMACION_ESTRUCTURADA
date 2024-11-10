#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

void setColor(int color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);


    /*
    1 BLUE 
    2 GREEN  
    4 RED  
    7 WHITE  
    */
}

struct infoDatosPersonales
{
	int yearBirth, monthBirth, dayBirth, numeroDomicilio;
    char nombres[31],
         apellidoPaterno[31],
         apellidoMaterno[31],
         RFC[14], correo[51],
         calle[41], colonia[41],
         municipio[41], estado[41];
};
    
struct infoArticulo
{
	int clave, clavesMercados[10], clavesInsumos[10], inventario, temporadaSiembra, temporadaCosecha;
	char descripcion[51];
	float costoProduccion, precioVenta;
};

struct infoInsumo
{
	int clave, clavesProveedores[10], puntoReorden, inventario;
	char descripcion[51];
	float precioSurtido[10];
};

struct infoProveedor
{
    int clave;
    struct infoDatosPersonales datosPersonales;
    float descuento, saldo;
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
	int claveMercado, claveArticulo, claveEmpleado, cantidad, year, month, day;
	float precioTotal, descuento, comision;
    char descripcion[51];
};

struct infoCompra
{
	int claveProveedor, claveInsumo, cantidad, entregado;
	float totalDeCompra, descuento;
    char descripcion[51];
};

bool inicializarArchivo(int numeroArchivo)
{
    FILE *fPtr;
    int i, n_registros;
    const char *nombreArchivo;
    struct infoDatosPersonales datosVacios = {0, 0, 0, 0,"", "", "", "", "", "", "", "", ""};
    void *estructuraVacia;
    size_t sizeEstructura;

    switch(numeroArchivo)
	{
        case 1:
		{
			n_registros = 1000;
			nombreArchivo = "Articulos.dat";
            struct infoArticulo articuloVacio = {0, {0}, {0}, 0, 0, 0, "", 0, 0};
            estructuraVacia = &articuloVacio;
            sizeEstructura = sizeof(articuloVacio);
            break;
        }
        case 2:
		{
			n_registros = 100;
			nombreArchivo = "Insumos.dat";
            struct infoInsumo insumoVacio = {0, {0}, 0, 0, "", {0}};
            estructuraVacia = &insumoVacio;
            sizeEstructura = sizeof(insumoVacio);
            break;
        }
        case 3:
		{
			n_registros = 100;
			nombreArchivo = "Mercados.dat";
            struct infoMercado mercadoVacio = {0, datosVacios, 0};
            estructuraVacia = &mercadoVacio;
            sizeEstructura = sizeof(mercadoVacio);
            break;
        }
        case 4:
		{
			n_registros = 1000;
			nombreArchivo = "Empleados.dat";
            struct infoEmpleado empleadoVacio = {0, 0, 0, 0, datosVacios, 0};
            estructuraVacia = &empleadoVacio;
            sizeEstructura = sizeof(empleadoVacio);
            break;
        }
        case 5:
		{
			n_registros = 100;
			nombreArchivo = "Proveedores.dat";
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
    const char *nombreArchivo;
    void *estructuraPtr;
    size_t sizeEstructura;

    switch(numeroArchivo)
	{
        case 1:
		{
            struct infoArticulo articulo;
            estructuraPtr = &articulo;
			nombreArchivo = "Articulos.dat";
            sizeEstructura = sizeof(struct infoArticulo);
            break;
        }
        case 2:
		{
            struct infoInsumo insumo;
            estructuraPtr = &insumo;
			nombreArchivo = "Insumos.dat";
            sizeEstructura = sizeof(struct infoInsumo);
            break;
        }
        case 3:
		{
            struct infoMercado mercado;
            estructuraPtr = &mercado;
			nombreArchivo = "Mercados.dat";
            sizeEstructura = sizeof(struct infoMercado);
            break;
        }
        case 4:
		{
            struct infoEmpleado empleado;
            estructuraPtr = &empleado;
			nombreArchivo = "Empleados.dat";
            sizeEstructura = sizeof(struct infoEmpleado);
            break;
        }
        case 5:
		{
            struct infoProveedor proveedor;
            estructuraPtr = &proveedor;
			nombreArchivo = "Proveedores.dat";
            sizeEstructura = sizeof(struct infoProveedor);
            break;
        }
    }

    if((fPtr = fopen(nombreArchivo,"rb")) == NULL)
        return false;
    
    fseek(fPtr, (*clave_buscar - 1) * sizeEstructura, SEEK_SET);

    if(fread(estructuraPtr, sizeEstructura, 1, fPtr))
    {
    	fclose(fPtr);
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
    setColor(4);
    printf("Error al verificar registros.\n");
    setColor(7);
    
    fclose(fPtr);
    return false;
}

bool VerificarHayRegistros(int numeroArchivo)
{
    FILE *archivoAVerificar;
    bool valorEnArchivo = false;
    const char *nombreArchivo;

    switch(numeroArchivo)
    {
        case 1:
            nombreArchivo = "Articulos.dat";
            break;
        case 2:
            nombreArchivo = "Insumos.dat";
            break;
        case 3:
            nombreArchivo = "Mercados.dat";
            break;
        case 4:
            nombreArchivo = "Empleados.dat";
            break;
        case 5:
            nombreArchivo = "Proveedores.dat";
            break;
    }
    
    if ((archivoAVerificar = fopen(nombreArchivo, "rb")) == NULL)
        return false;
    else
    {
        fclose(archivoAVerificar);
        return true;
    }
}

float obtenerCosto(int *Insumos, int *numeroInsumos)
{
    FILE *archivoInsumos;
    struct infoInsumo insumoActual;
    int i = 0, j;
    float costoTotal = 0, promedioCostoInsumo;

    if ((archivoInsumos = fopen("Insumos.dat", "rb")) == NULL)
        return 0;
    
    while (i < *numeroInsumos)
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

int inventarioRestante(int *claveArticulo)
{
    FILE *archivoArticulos;
    struct infoArticulo articuloActual;
    
    if((archivoArticulos = fopen("Articulos.dat", "rb")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo de articulos. Por favor intentalo de nuevo o contacte a soporte.\n");
        setColor(7);
        return 0;
    }
    else
    {
        fseek(archivoArticulos, (*claveArticulo - 1) * sizeof(articuloActual), SEEK_SET);
        fread(&articuloActual, sizeof(articuloActual), 1, archivoArticulos);

        fclose(archivoArticulos);

        return articuloActual.inventario;
    }
}

bool verificarProveedorInsumo(int *claveProveedor, int *claveInsumo)
{
    FILE *archivoInsumos;
    int i;
    struct infoInsumo insumoActual;

    if((archivoInsumos = fopen("Insumos.dat", "rb")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo de insumos. Por favor intentalo de nuevo o contacte a soporte.\n");
        setColor(7);
        return false;
    }
    else
    {
        fseek(archivoInsumos, (*claveInsumo - 1) * sizeof(struct infoInsumo), SEEK_SET);
        fread(&insumoActual, sizeof(struct infoInsumo), 1, archivoInsumos);

        i = 0;

        while(i < 10 && insumoActual.clavesProveedores[i] != 0)
        {
            if(insumoActual.clavesProveedores[i] == *claveProveedor)
            {
                fclose(archivoInsumos);
                return true;
            }

            i++;
        }

        fclose(archivoInsumos);
        return false;
    }
}

void obtenerDatosInsumo(int *claveProveedor, int *claveInsumo, float *precioUnitario, char *descripcion)
{
    FILE *archivoInsumos;
    int i;
    struct infoInsumo insumoActual;

    if((archivoInsumos = fopen("Insumos.dat", "rb")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo de insumos. Por favor intentalo de nuevo o contacte a soporte.\n");
        setColor(7);
    }
    else
    {
        fseek(archivoInsumos, (*claveInsumo - 1) * sizeof(struct infoInsumo), SEEK_SET);
        fread(&insumoActual, sizeof(struct infoInsumo), 1, archivoInsumos);

        i = 0;

        while(i < 10 && insumoActual.clavesProveedores[i] != 0)
        {
            if(insumoActual.clavesProveedores[i] == *claveProveedor)
            {
                *precioUnitario = insumoActual.precioSurtido[i];
                strcpy(descripcion, insumoActual.descripcion);
                fclose(archivoInsumos);
                return;
            }

            i++;
        }

        fclose(archivoInsumos);
        return;
    }
}

void modificarSaldo(int *claveProveedor, float *monto, const char modo)
{
    struct infoProveedor proveedorActual;
    FILE *filePtr;

    if((filePtr = fopen("Proveedores.dat", "rb+")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo de proveedores. El saldo no se pudo reflejar.\n");
        setColor(7);
    }
    else
    {
        fseek(filePtr, (*claveProveedor - 1) * sizeof(proveedorActual), SEEK_SET);
        fread(&proveedorActual, sizeof(proveedorActual), 1, filePtr);

        if (modo == '+')
            proveedorActual.saldo += *monto;
        else if (modo == '-')
            proveedorActual.saldo -= *monto;

        
        fseek(filePtr, (*claveProveedor - 1) * sizeof(proveedorActual), SEEK_SET);
        fwrite(&proveedorActual, sizeof(proveedorActual), 1, filePtr);

        fclose(filePtr);
    }
}

float obtenerDescuento(int *clave, int numeroArchivo)
{
    FILE *filePtr;
    const char *filename;
    size_t structSize;
    float descuento = 0;

    if (numeroArchivo == 1)
    {
        filename = "Proveedores.dat";
        structSize = sizeof(struct infoProveedor);
    }
    else if (numeroArchivo == 2)
    {
        filename = "Mercados.dat";
        structSize = sizeof(struct infoMercado);
    }
    else
    {
        setColor(4);
        printf("Número de archivo no válido.\n");
        setColor(7);
        return 0;
    }


    if ((filePtr = fopen(filename, "rb+")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo. No se pudo obtener la información del descuento.\n");
        setColor(7);
        return 0;
    }

    fseek(filePtr, (*clave - 1) * structSize, SEEK_SET);

    if (numeroArchivo == 1)
    {
        struct infoProveedor proveedorActual;
        fread(&proveedorActual, structSize, 1, filePtr);
        descuento = proveedorActual.descuento;
    }
    else
    {
        struct infoMercado mercadoActual;
        fread(&mercadoActual, structSize, 1, filePtr);
        descuento = mercadoActual.descuento;
    }

    fclose(filePtr);
    return descuento;
}

float obtenerComision(int *claveEmpleado)
{
    struct infoEmpleado empleadoActual;
    FILE *filePtr;

    if((filePtr = fopen("Empleados.dat", "rb+")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo de empleados. No se pudo obtener la informacion.\n");
        setColor(7);
        return 0;
    }
    else
    {
        fseek(filePtr, (*claveEmpleado - 1) * sizeof(empleadoActual), SEEK_SET);
        fread(&empleadoActual, sizeof(empleadoActual), 1, filePtr);
        fclose(filePtr);

        return empleadoActual.comision;
    }
}

void obtenerDatosArticulo(int *claveArticulo, float *precio, char *descripcion)
{
    FILE *archivoArticulos;
    struct infoArticulo articuloActual;
    
    if((archivoArticulos = fopen("Articulos.dat", "rb")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo de articulos. Por favor intentalo de nuevo o contacte a soporte.\n");
        setColor(7);
        
    }
    else
    {
        fseek(archivoArticulos, (*claveArticulo - 1) * sizeof(articuloActual), SEEK_SET);
        fread(&articuloActual, sizeof(articuloActual), 1, archivoArticulos);

        *precio = articuloActual.precioVenta;
        strcpy(descripcion, articuloActual.descripcion);

        fclose(archivoArticulos);
    }
}

void restarInventarioArticulos(int *claveArticulo, int *cantidad)
{
    FILE *archivoArticulos;
    struct infoArticulo articuloActual;
    
    if((archivoArticulos = fopen("Articulos.dat", "rb+")) == NULL)
    {
        setColor(4);
        printf("Error al abrir el archivo de articulos. No fue posible actualizar el inventario.\n");
        setColor(7);
    }
    else
    {
        fseek(archivoArticulos, (*claveArticulo - 1) * sizeof(articuloActual), SEEK_SET);
        fread(&articuloActual, sizeof(articuloActual), 1, archivoArticulos);

        articuloActual.inventario -= *cantidad;

        fseek(archivoArticulos, (*claveArticulo - 1) * sizeof(articuloActual), SEEK_SET);
        fwrite(&articuloActual, sizeof(articuloActual), 1, archivoArticulos);

        fclose(archivoArticulos);
    }
}

