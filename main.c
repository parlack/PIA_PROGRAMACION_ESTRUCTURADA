#include <stdio.h>
#include <ctype.h>
#include "Header_files/Reportes.h"

main()
{
	int opcionMenuPrincipal;
	FILE *filePtr;
	char agregarMas, opcionMenuReporte;
	bool isInvalid, existeArchivo, hayInsumos, hayMercados, hayProveedores, hayArticulos, hayEmpleados;

	do
	{
		printf("\n\n\tMENU PRINCIPAL\n\n");
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
		
		isInvalid = scanf("%d", &opcionMenuPrincipal) != 1 || !isInIntRange(&opcionMenuPrincipal, 1, 10);
		
		if(isInvalid)
		{
			fflush(stdin);
			printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
		}
		
	} while(isInvalid);
	
	while (opcionMenuPrincipal != 10)
	{
		switch(opcionMenuPrincipal)
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

								isInvalid = agregarMas != 's' && agregarMas != 'n';
								
								if (isInvalid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("\nNo fue posible abrir el archivo por las siguiente(s) razones:\n");
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

								isInvalid = agregarMas != 's' && agregarMas != 'n';
								
								if (isInvalid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("\nNo fue posible abrir el archivo por las siguiente(s) razones:\n");
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

								isInvalid = agregarMas != 's' && agregarMas != 'n';
								
								if (isInvalid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("\nERROR. No fue posible crear el archivo \"Mercados.dat\".\n");
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

								isInvalid = agregarMas != 's' && agregarMas != 'n';
								
								if (isInvalid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (isInvalid);
						
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

								isInvalid = agregarMas != 's' && agregarMas != 'n';
								
								if (isInvalid)
									printf("Respuesta invalida [s/n].\n");
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
					printf("\nERROR. No fue posible crear el archivo \"Proveedores.dat\".\n");

				break;
			case 6:	// Ventas 				//TERMINAR FACTURA
				
				//VALIDAR QUE EXISTAN MERCADOS, ARTICULOS Y EMPLEADOS
				hayArticulos = VerificarHayRegistros(1);
				hayMercados = VerificarHayRegistros(3);
				hayEmpleados = VerificarHayRegistros(4);

				if(hayArticulos && hayMercados && hayEmpleados)
				{
					do
					{
						if ((filePtr = fopen("./Data_files/Ventas.txt", "a+")) == NULL)
							printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
						else
						{
							lecturaVentas(filePtr);
							fclose(filePtr);
						}
						
						do
						{
							printf("Realizar otra venta? [s/n] ~ ");
							fflush(stdin);

							if(scanf("%c", &agregarMas) != 1 || (agregarMas != 's' && agregarMas != 'n'))
							{
								printf("Respuesta invalida [s/n].\n");
								isInvalid = true;
							}
							else
								isInvalid = false;
							
							
						} while (isInvalid);
					
					} while (agregarMas == 's');
				}
				else
				{
					printf("\nNo fue posible abrir el archivo debido a:\n");
					if(!hayArticulos)
						printf("\t- No existen ARTICULOS guardados.\n");
					
					if(!hayMercados)
						printf("\t- No existen MERCADOS guardados.\n");

					if(!hayEmpleados)
						printf("\t- No existen EMPLEADOS guardados.\n");
				}

				break;
			case 7:	//Compras
				
				//VALIDAR QUE EXISTAN PROVEEDORES E INSUMOS
				hayInsumos = VerificarHayRegistros(2);
				hayProveedores = VerificarHayRegistros(5);

				if(hayInsumos && hayProveedores)
				{
					do
					{
						if ((filePtr = fopen("./Data_files/Compras.txt", "a+")) == NULL)
							printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
						else
						{
							lecturaCompras(filePtr);
							fclose(filePtr);
						}
							
						do
						{
							printf("Realizar otra compra? [s/n] ~ ");
							fflush(stdin);

							if(scanf("%c", &agregarMas) != 1 || (agregarMas != 's' && agregarMas != 'n'))
							{
								printf("Respuesta invalida [s/n].\n");
								isInvalid = true;
							}
							else
								isInvalid = false;
							
						} while (isInvalid);
					
					} while (agregarMas == 's');
				}
				else
				{
					printf("\nNo fue posible abrir el archivo debido a:\n");
					if(!hayInsumos)
						printf("\t- No existen INSUMOS guardados.\n");
					
					if(!hayProveedores)
						printf("\t- No existen PROVEEDORES guardados.\n");
				}
				
				break;
			case 8:	//Control de Inventario
				
				do
				{
					if ((filePtr = fopen("./Data_files/Compras.txt", "r")) == NULL)
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
					else
					{
						controlInventario(filePtr);
						fclose(filePtr);
					}
						
					do
					{
						printf("Agregar otra recepcion? [s/n] ~ ");
						fflush(stdin);

						if(scanf("%c", &agregarMas) != 1 || (agregarMas != 's' && agregarMas != 'n'))
						{
							printf("Respuesta invalida [s/n].\n");
							isInvalid = true;
						}
						else
							isInvalid = false;
						
					} while (isInvalid);
				
				} while (agregarMas == 's');
				
				break;
			case 9: //Reportes

				do
				{
					printf("\n\n\tMENU DE REPORTES\n\n");
					printf("a - Listado de art%cculos\n", 161);
					printf("b - Total de venta por fecha\n");
					printf("c - Total de venta por art%cculo\n", 161);
					printf("d - Listado de art%cculos a solicitar\n", 161);
					printf("e - Saldos por pagar\n");
					printf("f - C%clculo de comisiones\n", 131);
					printf("g - Compras pendientes de recepci%cn\n", 162);
					printf("h - Salir\n");
					printf("[ Ingresa una opci%cn ] ~ ", 162);
					fflush(stdin);
					isInvalid = scanf("%c", &opcionMenuReporte) != 1 || !isInCharRange(&opcionMenuReporte, 'a', 'h');
								
					if(isInvalid)
					{
						fflush(stdin);
						printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
					}
				
				} while(isInvalid);

				while(opcionMenuReporte != 'h')
				{
					
					switch(opcionMenuReporte)
					{
						case 'a':
							if ((filePtr = fopen("./Data_files/Articulos.dat", "rb+")) == NULL)
								printf("Error al abrir el archivo. No existen registros de Articulos.\n");
							else
							{
								reporteArticulos(filePtr);
								fclose(filePtr);
							}
							break;

						case 'b':
							if ((filePtr = fopen("./Data_files/Ventas.txt", "r")) == NULL)
								printf("Error al abrir el archivo. No existen registros de Ventas.\n");
							else
							{
								ventasFecha(filePtr);
								fclose(filePtr);
							}
							break;

						case 'c':
							if(!VerificarHayRegistros(1))
								printf("Error: No hay articulos registrados.\n");
							else if ((filePtr = fopen("./Data_files/Ventas.txt", "r")) == NULL)
								printf("Error al abrir el archivo. No existen registros de Ventas.\n");
							else
							{
								ventasArticulo(filePtr);
								fclose(filePtr);
							}
							break;

						case 'd':
							if ((filePtr = fopen("./Data_files/Insumos.dat", "rb")) == NULL)
								printf("Error al abrir el archivo. No existen registros de Insumos.\n");
							else
							{
								insumosPorSolicitar(filePtr);
								fclose(filePtr);
							}
							break;

						case 'e':

							break;

						case 'f':
							if ((filePtr = fopen("./Data_files/Empleados.dat", "rb")) == NULL)
								printf("Error al abrir el archivo. No existen registros de Empleados.\n");
							else
							{
								calculoDeComision(filePtr);
								fclose(filePtr);
							}
							break;

						case 'g':
						    if ((filePtr = fopen("./Data_files/Compras.txt", "r")) == NULL)
								printf("Error al abrir el archivo. No existen registros de Compras.\n");
							else
							{
								comprasConRecepcionPendiente(filePtr);
								fclose(filePtr);
							}
							break;
					

					}
					
					do
					{
						printf("\n\n\tMENU DE REPORTES\n\n");
						printf("a - Listado de art%cculos\n", 161);
						printf("b - Total de venta por fecha\n");
						printf("c - Total de venta por art%cculo\n", 161);
						printf("d - Listado de art%cculos a solicitar\n", 161);
						printf("e - Saldos por pagar\n");
						printf("f - C%clculo de comisiones\n", 131);
						printf("g - Compras pendientes de recepci%cn\n", 162);
						printf("h - Salir\n");
						printf("[ Ingresa una opci%cn ] ~ ", 162);
						fflush(stdin);
						isInvalid = scanf("%c", &opcionMenuReporte) != 1 || !isInCharRange(&opcionMenuReporte, 'a', 'h');
									
						if(isInvalid)
						{
							fflush(stdin);
							printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
						}
					
					} while(isInvalid);
				}
				
				break;
		}
		
		do
		{
			printf("\n\n\tMENU PRINCIPAL\n\n");
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

			isInvalid = scanf("%d", &opcionMenuPrincipal) != 1 || !isInIntRange(&opcionMenuPrincipal, 1, 10);
		
			if(isInvalid)
			{
				fflush(stdin);
				printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
			}
			
		} while(isInvalid);
	}
}
