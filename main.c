#include <stdio.h>
#include "Header_files/Validations.h"
#include "Header_files/Estructuras_granja.h"

main()
{
	int opcionMenuPrincipal;
	FILE *filePtr;
	
	do
	{
		printf("\n\n\tMEN%c PRINCIPAL\n\n", 233);
		printf("1 - Art%cculos\n", 161);
		printf("2 - Insumos\n");
		printf("3 - Mercados\n");
		printf("4 - Empleados\n");
		printf("5 - Proveedores\n");
		printf("6 - Ventas\n");
		printf("7 - Compras\n");
		printf("8 - Control de Inventario\n");
		printf("9 - Reportes\n");
		printf("10 - SALIR\n");
		printf("[ Ingresa una opci%cn ] ~ ", 162);
		scanf("%d", &opcionMenuPrincipal);
		
		
	} while( !isInRange((float)opcionMenuPrincipal, 1, 10) );
	
	while (opcionMenuPrincipal != 10)
	{
		switch (opcionMenuPrincipal)
		{
			case 1:
				
				//VALIDAR QUE EXISTAN INSUMOS Y MERCADOS
				
				if(inicializarArchivo(1))
				{
					if ((filePtr = fopen("./Data_files/Articulos.dat", "ab")) == NULL)
						printf("Error al abrir el archivo. Por favor intentalo de nuevo\n");
					else
						printf("Hola mundo");
				}
				else
					printf("Error al abrir el archivo");
				break;
				
			case 2:
				
				//VALIDAR QUE EXISTAN PROVEEDORES
				
				break;
			case 3:
				
				
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				
				//VALIDAR QUE EXISTAN MERCADOS, ARTICULOS Y EMPLEADOS
				
				break;
			case 7:
				
				//VALIDAR QUE EXISTAN PROVEEDORES E INSUMOS
				
				break;
			case 8:
				
				//VALIDAR QUE EXISTAN COMPRAS
				break;
			case 9:
				break;
		}
		
		do
		{
			printf("\n\n\tMEN%c PRINCIPAL\n\n", 233);
			printf("1 - Art%cculos\n", 161);
			printf("2 - Insumos\n");
			printf("3 - Mercados\n");
			printf("4 - Empleados\n");
			printf("5 - Proveedores\n");
			printf("6 - Ventas\n");
			printf("7 - Compras\n");
			printf("8 - Control de Inventario\n");
			printf("9 - Reportes\n");
			printf("10 - SALIR\n");
			printf("[ Ingresa una opci%cn ] ~ ", 162);
			scanf("%d", &opcionMenuPrincipal);
			
		} while( !isInRange(opcionMenuPrincipal, 1, 10) );
	}
}
