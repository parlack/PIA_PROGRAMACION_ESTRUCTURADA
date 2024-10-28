#include <stdio.h>
#include <ctype.h>
#include "Header_files/Lecturas.h"

main()
{
	int opcionMenuPrincipal;
	FILE *filePtr;
	char agregarMas;
	bool isValid, existeArchivo, hayInsumos, hayMercados, hayProveedores;

	do
	{
		printf("\tMEN%c PRINCIPAL\n\n", 233);
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
		
		isValid = scanf("%d", &opcionMenuPrincipal) == 1 && isInIntRange(&opcionMenuPrincipal, 1, 10);
		
		if(!isValid)
			printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
		
	} while(!isValid);
	
	while (opcionMenuPrincipal != 10)
	{
		switch (opcionMenuPrincipal)
		{
			case 1:	//Articulos
				
				//VALIDAR QUE EXISTAN INSUMOS Y MERCADOS
				existeArchivo = inicializarArchivo(1);
				hayInsumos = VerificarHayRegistros(2);
				hayMercados = VerificarHayRegistros(3);

				if(existeArchivo && hayInsumos && hayMercados)
				{
					if ((filePtr = fopen("./Data_files/Articulos.dat", "rb+")) == NULL)
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
					else
					{
						do
						{
							lecturaArticulo(filePtr);
							
                            do
							{
								printf("Ingresar articulos? [s/n] ~ ");
								fflush(stdin);
								scanf("%c", &agregarMas);

								agregarMas = tolower(agregarMas);

								isValid = agregarMas == 's' || agregarMas == 'n';
								
								if (!isValid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (!isValid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("No fue posible abrir el archivo por las siguiente(s) razones:\n");
					if(!existeArchivo)
						printf("\t- ERROR EN EL ARCHIVO DE DATOS: \"Articulos.dat\".\n");
					
					if(!hayInsumos)
						printf("\t- No existen INSUMOS guardados.\n");
					
					if(!hayMercados)
						printf("\t- No existen MERCADOS guardados.\n");
				}

				break;
				
			case 2: //INSUMOOOS

				existeArchivo = inicializarArchivo(2);
			    hayProveedores = VerificarHayRegistros(5);
				
				if(existeArchivo && hayProveedores)
				{
					if ((filePtr = fopen("./Data_files/Insumos.dat", "rb+")) == NULL)
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
					else
					{
						do
						{
							lecturaInsumo(filePtr);
							
                            do
							{
								printf("Ingresar m%cs insumos? [s/n] ~ ", 160);
								fflush(stdin);
								scanf("%c", &agregarMas);

								agregarMas = tolower(agregarMas);

								isValid = agregarMas == 's' || agregarMas == 'n';
								
								if (!isValid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (!isValid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("No fue posible abrir el archivo por las siguiente(s) razones:\n");
					if(!existeArchivo)
						printf("\t- ERROR EN EL ARCHIVO DE DATOS: \"Insumos.dat\".\n");
					
					if(!hayProveedores)
						printf("\t- No existen PROVEEDORES guardados.\n");
				}
				//VALIDAR QUE EXISTAN PROVEEDORES
				
				break;
			case 3: // MERCADOS
			
				if(inicializarArchivo(3))
				{
					if ((filePtr = fopen("./Data_files/Mercados.dat", "rb+")) == NULL)
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
					else
					{
						do
						{
							lecturaMercado(filePtr);
							
                            do
							{
								printf("Ingresar m%cs mercados? [s/n] ~ ", 160);
								fflush(stdin);
								scanf("%c", &agregarMas);

								agregarMas = tolower(agregarMas);

								isValid = agregarMas == 's' || agregarMas == 'n';
								
								if (!isValid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (!isValid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("ERROR. No fue posible crear el archivo \"Mercados.dat\".\n");
				}
				
				break;
			case 4: // EMPLEADOS

				if(inicializarArchivo(4))
				{
					if ((filePtr = fopen("./Data_files/Empleados.dat", "rb+")) == NULL)
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
					else
					{
						do
						{
							lecturaEmpleado(filePtr);
							
                            do
							{
								printf("Ingresar m%cs empleados? [s/n] ~ ", 160);
								fflush(stdin);
								scanf("%c", &agregarMas);

								agregarMas = tolower(agregarMas);

								isValid = agregarMas == 's' || agregarMas == 'n';
								
								if (!isValid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (!isValid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("ERROR. No fue posible crear el archivo \"Empleados.dat\".\n");
				}

				break;
			case 5: // PROVEEDORES

				if(inicializarArchivo(5))
				{
					if ((filePtr = fopen("./Data_files/Proveedores.dat", "rb+")) == NULL)
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
					else
					{
						do
						{
							lecturaProveedor(filePtr);
							
                            do
							{
								printf("Ingresar m%cs proveedores? [s/n] ~ ", 160);
								fflush(stdin);
								scanf("%c", &agregarMas);

								agregarMas = tolower(agregarMas);

								isValid = agregarMas == 's' || agregarMas == 'n';
								
								if (!isValid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (!isValid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
					printf("ERROR. No fue posible crear el archivo \"Proveedores.dat\".\n");

				break;
			case 6:	// Ventas
				
				//VALIDAR QUE EXISTAN MERCADOS, ARTICULOS Y EMPLEADOS
				
				break;
			case 7:	//Compras
				
				//VALIDAR QUE EXISTAN PROVEEDORES E INSUMOS
				
				break;
			case 8:	//Control de Inventario
				
				//VALIDAR QUE EXISTAN COMPRAS
				break;
			case 9: //Reportes
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

			isValid = scanf("%d", &opcionMenuPrincipal) == 1 && isInIntRange(&opcionMenuPrincipal, 1, 10);
		
			if(!isValid)
				printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
			
		} while(!isValid);
	}
}
