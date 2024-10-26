#include <stdbool.h>
#include <string.h>
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

bool moreThanZero(float *value, bool canBeEqual)
{
	if(canBeEqual)
		return *value >= 0;
	else
		return *value > 0;
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
	bool isValid = false;
	int i = 0;
	
	while (*(email + i) != '\0' && !isValid)
	{
		if (*(email + i) == '@')
		{
			isValid = true;
		}
		i++;
	}
	
	return isValid;
}

bool isRFC(struct infoDatosPersonales *Datos)
{
	bool isValid = true;
	
	return isValid;
}


