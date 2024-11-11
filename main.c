#include <stdio.h>
#include <ctype.h>
#include "Reportes.h"



main()
{
	int opcionMenuPrincipal;
	FILE *filePtr;
	char agregarMas, opcionMenuReporte, opcionGenerarFactura;
	bool isInvalid, existeArchivo, hayInsumos, hayMercados, hayProveedores, hayArticulos, hayEmpleados;

	do
	{
		setColor(11);
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
		setColor(7);
		
		isInvalid = scanf("%d", &opcionMenuPrincipal) != 1 || !isInIntRange(&opcionMenuPrincipal, 1, 10);
		
		if(isInvalid)
		{
			fflush(stdin);
			setColor(4);
			printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
			setColor(7);
		}
		
	} while(isInvalid);
	
	while (opcionMenuPrincipal != 10)
	{
		existeArchivo = false;
		switch(opcionMenuPrincipal)
		{
			case 1:	//Articulos
				
				//VALIDAR QUE EXISTAN INSUMOS Y MERCADOS
				hayInsumos = VerificarHayRegistros(2);
				hayMercados = VerificarHayRegistros(3);
				
				if(hayInsumos && hayMercados)
					existeArchivo = inicializarArchivo(1);
				
				

				if(existeArchivo)
				{
					if ((filePtr = fopen("Articulos.dat", "rb+")) == NULL)
					{
						setColor(4);
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    	setColor(7);
						
					}
					else
					{
						do
						{
							lecturaArticulo(filePtr);
							
                            do
							{
								printf("Ingresar otro articulo? [s/n] ~ ");
								fflush(stdin);

								if(scanf("%c", &agregarMas) != 1)
									isInvalid = true;
								else
								{
									agregarMas = tolower(agregarMas);
									isInvalid = agregarMas != 's' && agregarMas != 'n';
								}
								
								if (isInvalid)
								{
									setColor(4);
									printf("Respuesta invalida [s/n].\n");
                    				setColor(7);
								}
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					setColor(4);
					printf("\nNo fue posible abrir el archivo por las siguiente(s) razones:\n");
					if(!existeArchivo)
						printf("\t- ERROR EN EL ARCHIVO DE DATOS: \"Articulos.dat\".\n");
					
					if(!hayInsumos)
						printf("\t- No existen INSUMOS guardados.\n");
					
					if(!hayMercados)
						printf("\t- No existen MERCADOS guardados.\n");
                    setColor(7);
				}

				break;
				
			case 2: //INSUMOOOS

			    hayProveedores = VerificarHayRegistros(5);
			    
			    if(hayProveedores)
			    	existeArchivo = inicializarArchivo(2);

			    
				if(existeArchivo)
				{
					if ((filePtr = fopen("Insumos.dat", "rb+")) == NULL)
					{
                    	setColor(4);
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    	setColor(7);
					}
					else
					{
						do
						{
							lecturaInsumo(filePtr);
							
                            do
							{
								printf("Ingresar m%cs insumos? [s/n] ~ ", 160);
								fflush(stdin);

								if(scanf("%c", &agregarMas) != 1)
									isInvalid = true;
								else
								{
									agregarMas = tolower(agregarMas);
									isInvalid = agregarMas != 's' && agregarMas != 'n';
								}
								
								if (isInvalid)
								{
									setColor(4);
									printf("Respuesta invalida [s/n].\n");
                    				setColor(7);
									
								}
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					printf("\nNo fue posible abrir el archivo por las siguiente(s) razones:\n");
					if(!existeArchivo)
					{
                    	setColor(4);
						printf("\t- ERROR EN EL ARCHIVO DE DATOS: \"Insumos.dat\".\n");
                    	setColor(7);
					}
					
					if(!hayProveedores)
					{
                   		setColor(4);
						printf("\t- No existen PROVEEDORES guardados.\n");
                    	setColor(7);
					}
				}
				//VALIDAR QUE EXISTAN PROVEEDORES
				
				break;
			case 3: // MERCADOS
			
				if(inicializarArchivo(3))
				{
					if ((filePtr = fopen("Mercados.dat", "rb+")) == NULL)
					{
						setColor(4);
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    	setColor(7);

					}
					else
					{
						do
						{
							lecturaMercado(filePtr);
							
                            do
							{
								printf("Ingresar m%cs mercados? [s/n] ~ ", 160);
								fflush(stdin);
								
								if(scanf("%c", &agregarMas) != 1)
									isInvalid = true;
								else
								{
									agregarMas = tolower(agregarMas);
									isInvalid = agregarMas != 's' && agregarMas != 'n';
								}
								
								if (isInvalid)
								{
                    				setColor(4);
									printf("Respuesta invalida [s/n].\n");
                    				setColor(7);
								}
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					setColor(4);
					printf("\nERROR. No fue posible crear el archivo \"Mercados.dat\".\n");
                    setColor(7);
				}
				
				break;
			case 4: // EMPLEADOS

				if(inicializarArchivo(4))
				{
					if ((filePtr = fopen("Empleados.dat", "rb+")) == NULL)
					{
                    	setColor(4);
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    	setColor(7);
					}
					else
					{
						do
						{
							lecturaEmpleado(filePtr);
							
                            do
							{
								printf("Ingresar m%cs empleados? [s/n] ~ ", 160);
								fflush(stdin);
								
								if(scanf("%c", &agregarMas) != 1)
									isInvalid = true;
								else
								{
									agregarMas = tolower(agregarMas);
									isInvalid = agregarMas != 's' && agregarMas != 'n';
								}
								
								if (isInvalid)
								{
									setColor(4);
									printf("Respuesta invalida [s/n].\n");
                    				setColor(7);

								}
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					setColor(4);
					printf("ERROR. No fue posible crear el archivo \"Empleados.dat\".\n");
                    setColor(7);
				}

				break;
			case 5: // PROVEEDORES

				if(inicializarArchivo(5))
				{
					if ((filePtr = fopen("Proveedores.dat", "rb+")) == NULL)
					{
                    	setColor(4);
						printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    	setColor(7);

					}
					else
					{
						do
						{
							lecturaProveedor(filePtr);
							
                            do
							{
								printf("Ingresar m%cs proveedores? [s/n] ~ ", 160);
								fflush(stdin);
								
								if(scanf("%c", &agregarMas) != 1)
									isInvalid = true;
								else
								{
									agregarMas = tolower(agregarMas);
									isInvalid = agregarMas != 's' && agregarMas != 'n';
								}
								
								if (isInvalid)
								{
									setColor(4);
									printf("Respuesta invalida [s/n].\n");
                    				setColor(7);

								}
								
							} while (isInvalid);
						
						} while (agregarMas == 's');
						
						fclose(filePtr);
					}
				}
				else
				{
					setColor(4);
					printf("\nERROR. No fue posible crear el archivo \"Proveedores.dat\".\n");
                    setColor(7);

				}

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
						if ((filePtr = fopen("Ventas.txt", "a+")) == NULL)
						{
                    		setColor(4);
							printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                   	 		setColor(7);
						}
						else
						{
							lecturaVentas(filePtr);

							do
							{
								printf("\nDesea generar factura? [s/n] ~ ");
								fflush(stdin);

								if(scanf("%c", &opcionGenerarFactura) != 1 || (opcionGenerarFactura != 's' && opcionGenerarFactura != 'n'))
								{
									setColor(4);
									printf("\nERROR: Opci%cn inv%clida.\n", 162, 160);
                    				setColor(7);
									isInvalid = true;
								}
								else
									isInvalid = false;

							} while (isInvalid);

							if(opcionGenerarFactura == 's')
							{
								generarFactura(filePtr);	
							}

							fclose(filePtr);

						}
						
						do
						{
							printf("Realizar otra venta? [s/n] ~ ");
							fflush(stdin);

							if(scanf("%c", &agregarMas) != 1)
								isInvalid = true;
							else
							{
								agregarMas = tolower(agregarMas);
								isInvalid = agregarMas != 's' && agregarMas != 'n';
							}
							
							if (isInvalid)
							{
								setColor(4);
								printf("Respuesta invalida [s/n].\n");
                    			setColor(7);
							}
							
						} while (isInvalid);
					
					} while (agregarMas == 's');
				}
				else
				{
					setColor(4);
					printf("\nNo fue posible abrir el archivo debido a:\n");
					if(!hayArticulos)
						printf("\t- No existen ARTICULOS guardados.\n");
					
					if(!hayMercados)
						printf("\t- No existen MERCADOS guardados.\n");

					if(!hayEmpleados)
						printf("\t- No existen EMPLEADOS guardados.\n");
                	setColor(7);
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
						if ((filePtr = fopen("Compras.txt", "a+")) == NULL)
						{
                   		 	setColor(4);
							printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
                    		setColor(7);
						}
						else
						{
							lecturaCompras(filePtr);
							fclose(filePtr);
						}
							
						do
						{
							printf("Realizar otra compra? [s/n] ~ ");
							fflush(stdin);

							if(scanf("%c", &agregarMas) != 1)
								isInvalid = true;
							else
							{
								agregarMas = tolower(agregarMas);
								isInvalid = agregarMas != 's' && agregarMas != 'n';
							}
							
							if (isInvalid)
							{
								setColor(4);
								printf("Respuesta invalida [s/n].\n");
                    			setColor(7);

							}
							
						} while (isInvalid);
					
					} while (agregarMas == 's');
				}
				else
				{
					setColor(4);
					printf("\nNo fue posible abrir el archivo debido a:\n");
					if(!hayInsumos)
						printf("\t- No existen INSUMOS guardados.\n");
					
					if(!hayProveedores)
						printf("\t- No existen PROVEEDORES guardados.\n");
            		setColor(7);
				}
				
				break;
			case 8:	//Control de Inventario
				if ((filePtr = fopen("Compras.txt", "r+")) == NULL)
				{
					setColor(4);
					printf("Error al abrir el archivo. Por favor intentalo de nuevo o contacte a soporte.\n");
            		setColor(7);
				}
				else
				{
					do
					{
						controlInventario(filePtr);
							
						do
						{
							printf("Agregar otra recepcion? [s/n] ~ ");
							fflush(stdin);

							if(scanf("%c", &agregarMas) != 1)
								isInvalid = true;
							else
							{
								agregarMas = tolower(agregarMas);
								isInvalid = agregarMas != 's' && agregarMas != 'n';
							}
							
							if (isInvalid)
							{
								setColor(4);
								printf("Respuesta invalida [s/n].\n");
            					setColor(7);
							}
							
						} while (isInvalid);
					
					} while (agregarMas == 's');

					fclose(filePtr);
				}
				
				
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
						setColor(4);
						printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
            			setColor(7);
					}
				
				} while(isInvalid);

				while(opcionMenuReporte != 'h')
				{
					switch(opcionMenuReporte)
					{
						case 'a':
							if ((filePtr = fopen("Articulos.dat", "rb+")) == NULL)
							{
								setColor(4);
								printf("Error al abrir el archivo. No existen registros de Articulos.\n");
            					setColor(7);
							}
							else
							{
								reporteArticulos(filePtr);
								fclose(filePtr);
							}
							break;

						case 'b':
							if ((filePtr = fopen("Ventas.txt", "r")) == NULL)
							{
								setColor(4);
								printf("Error al abrir el archivo. No existen registros de Ventas.\n");
            					setColor(7);
							}
							else
							{
								ventasFecha(filePtr);
								fclose(filePtr);
							}
							break;

						case 'c':
							if(!VerificarHayRegistros(1))
							{
								setColor(4);
								printf("Error: No hay articulos registrados.\n");
            					setColor(7);
							}
							else if ((filePtr = fopen("Ventas.txt", "r")) == NULL)
							{
								setColor(4);
								printf("Error al abrir el archivo. No existen registros de Ventas.\n");
            					setColor(7);
							}
							else
							{
								ventasArticulo(filePtr);
								fclose(filePtr);
							}
							break;

						case 'd':
							if ((filePtr = fopen("Insumos.dat", "rb")) == NULL)
							{
								setColor(4);
								printf("Error al abrir el archivo. No existen registros de Insumos.\n");
            					setColor(7);
							}
							else
							{
								insumosPorSolicitar(filePtr);
								fclose(filePtr);
							}
							break;

						case 'e':
							if ((filePtr = fopen("Proveedores.dat", "rb")) == NULL)
							{
								setColor(4);
								printf("Error al abrir el archivo. No existen registros de Empleados.\n");
            					setColor(7);
							}
							else
							{
								SaldosPendientes(filePtr);
								fclose(filePtr);
							}
							break;
							

						case 'f':
							if ((filePtr = fopen("Empleados.dat", "rb")) == NULL)
							{
								setColor(4);
								printf("Error al abrir el archivo. No existen registros de Empleados.\n");
            					setColor(7);
							}
							else
							{
								calculoDeComision(filePtr);
								fclose(filePtr);
							}
							break;

						case 'g':
						    if ((filePtr = fopen("Compras.txt", "r")) == NULL)
							{
								setColor(4);
								printf("Error al abrir el archivo. No existen registros de Compras.\n");
            					setColor(7);
							}
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
							setColor(4);
							printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
            				setColor(7);
						}
					
					} while(isInvalid);
				}
				
				break;
		}
		
		do
		{
			setColor(11);
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
			setColor(7);

			isInvalid = scanf("%d", &opcionMenuPrincipal) != 1 || !isInIntRange(&opcionMenuPrincipal, 1, 10);
		
			if(isInvalid)
			{
				fflush(stdin);
				setColor(4);
				printf("\nERROR: Opci%cn inv%clida.\n\n", 162, 160);
                setColor(7);
			}
			
		} while(isInvalid);
	}
}
