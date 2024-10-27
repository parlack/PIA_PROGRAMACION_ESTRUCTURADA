#include <stdbool.h>
#include <ctype.h>
#include "./cbits/regex.h"
#include "Estructuras_granja.h"

bool isInRange(float value, float min, float max)
{
	return value >= min && value <= max;
}

bool isInCharRange(char *value, char min, char max)
{
	return *value >= min && *value <= max;
}

bool isAlphabetic(char *charLine, bool isAlphaNumeric)
{
	bool isValid = true;
	int i = 0;
	
	if (isAlphaNumeric)
	{	
		while (*(charLine + i) != '\0' && isValid)
		{
			if (!((*(charLine + i) >= 'a' && *(charLine + i) <= 'z') || 
				(*(charLine + i) >= 'A' && *(charLine + i) <= 'Z')   || 
				(*(charLine + i) >= '0' && *(charLine + i) <= '9')   || 
				*(charLine + i) == ' '))
			{
				isValid = false;
			}
				
			i++;
		}
	}
	else
	{
		while (*(charLine + i) != '\0' && isValid)
		{
			if (!((*(charLine + i) >= 'a' && *(charLine + i) <= 'z') || 
				(*(charLine + i) >= 'A' && *(charLine + i) <= 'Z')   || 
				*(charLine + i) == ' '))
			{
				isValid = false;
			}
			
			i++;
		}
	}
	
	return isValid;
} 

bool minStringLength(char *cadena, int minLength)
{	
	int i = 0;
	
	while(*(cadena + i) != '\0')
	{
		i++;
	}
	
	return i >= minLength;
}

//FALTA FUNCION: Existe registro en archivo

bool moreThanZero(float value, bool canBeEqual)
{
	if(canBeEqual)
		return value >= 0;
	else
		return value > 0;
}

//FALTA FUNCION: Validar RFC

bool isValidDate(int *day, int *month, int *year)
{
    int daysInMonth;

    switch (*month) {
    	
        case 2:
        	
            daysInMonth = (*year % 4 == 0 && (*year % 100 != 0 || *year % 400 == 0)) ? 29 : 28;
            break;
            
        case 4: case 6: case 9: case 11:
        	
            daysInMonth = 30;
            break;
            
        default:
            daysInMonth = 31;
    }

    return *day >= 1 && *day <= daysInMonth;
}


bool isEmail(char *email)
{
    regex_t regex;
    bool isValid;

    // Definir el patrón para un correo electrónico
    char *patron = "^[a-zA-Z-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]+$";


    if (regcomp(&regex, patron, REG_EXTENDED) != 0) {
        printf("Error al verificar el correo.\n");
        return false;
    }

    isValid = regexec(&regex, email, 0, NULL, 0);

    regfree(&regex);
	
	return isValid;
}


int lengthChar(char *Cadena)
{
	int i = 0;

	while(Cadena[i] != '\0')
		i++;

	return i;
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
bool validarRFC(struct infoDatosPersonales *datos, char *rfc)
{
    char rfcGenerado[14];
    sprintf(rfcGenerado, "%c%c%c%02d%02d%02d",
            toupper(datos->apellidoPaterno[0]),
            toupper(datos->apellidoMaterno[0]),
            toupper(datos->nombres[0]),
            datos->year % 100,
            datos->month,
            datos->day);

    char regexPattern[50];
    sprintf(regexPattern, "^%s[0-9A-Z]{3}$", rfcGenerado);

    regex_t regex;
    if (regcomp(&regex, regexPattern, REG_EXTENDED) != 0) {
        return false;
    }

    bool isValid = (regexec(&regex, rfc, 0, NULL, 0) == 0);
    regfree(&regex);

    return isValid;
}
*/
