#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "Estructuras_granja.h"

bool isInIntRange(int *, int, int);
bool isInFloatRange(float *, float, float);
bool isInCharRange(char *, char, char);
bool isCharAlphabetic(char *, bool);
bool isAlphabetic(char *, bool);
int stringLength(char *);
bool minStringLength(char *, int);
void retirarSaltoLinea(char *);
bool intMoreThanZero(int *, bool);
bool floatMoreThanZero(float *, bool);
bool validarFecha(int *, int *, int *);
void limpiarApellido(char [], char []);
void seleccionarNombre(char [], char []);
bool validarRFC(struct infoDatosPersonales *);
bool esCorreoElectronico(char *);


bool isInIntRange(int *value, int min, int max)
{
	return *value >= min && *value <= max;
}

bool isInFloatRange(float *value, float min, float max)
{
	return *value >= min && *value <= max;
}

bool isInCharRange(char *value, char min, char max)
{
	return *value >= min && *value <= max;
}

bool isCharAlphabetic(char *character, bool isAlphaNumeric)
{
    bool isValid = true;

    if(isAlphaNumeric)
    {
        if (!((*character >= 'a' && *character <= 'z') || 
              (*character >= 'A' && *character <= 'Z') || 
              (*character >= '0' && *character <= '9')))
        {
            isValid = false;
        }
    }
    else
    {
        if (!((*character >= 'a' && *character <= 'z') || 
              (*character >= 'A' && *character <= 'Z')))
        {
            isValid = false;
        }
    }
    
    return isValid;
}

bool isAlphabetic(char *charLine, bool isAlphaNumeric)
{
	bool isValid = true;
	int i = 0;
	
    while (*(charLine + i) != '\0' && isValid)
    {
        if(!isCharAlphabetic(charLine + i, isAlphaNumeric) && *(charLine + i) != ' ')
        {
            isValid = false;
        }
            
        i++;
    }
	
	return isValid;
}

int stringLength(char *cadena)
{	
	int i = 0;
	
	while(*(cadena + i) != '\0')
		i++;
	
	return i;
}

bool minStringLength(char *cadena, int minLength)
{	
	return stringLength(cadena) >= minLength;
}

void retirarSaltoLinea(char *cadena)
{
    size_t longitud = stringLength(cadena);

    if (longitud > 0 && cadena[longitud - 1] == '\n') 
        cadena[longitud - 1] = '\0';
}

bool intMoreThanZero(int *value, bool canBeEqual)
{
	if(canBeEqual)
		return *value >= 0;
	else
		return *value > 0;
}

bool floatMoreThanZero(float *value, bool canBeEqual)
{
	if(canBeEqual)
		return *value >= 0;
	else
		return *value > 0;
}

bool validarFecha(int *day, int *month, int *year)
{
    int daysInMonth;
    time_t t = time(NULL);
    struct tm *fechaActual = localtime(&t);

    int anioActual = fechaActual->tm_year + 1900;
    int mesActual = fechaActual->tm_mon + 1;
    int diaActual = fechaActual->tm_mday;

    if (*year > anioActual) 
        return false;
    else if (*year == anioActual)
    {
        if (*month > mesActual)
            return false;
        else if (*month == mesActual) 
        {
            if (*day > diaActual)
                return false;
        }
    }

    switch (*month) 
    {
        case 2:
        	
            daysInMonth = (*year % 4 == 0 && *year % 100 != 0 || *year % 400 == 0) ? 29 : 28;
            break;
            
        case 4: case 6: case 9: case 11:
        	
            daysInMonth = 30;
            break;
            
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        
        default:
            return false;
            break;
    }

    return *day >= 1 && *day <= daysInMonth;
}

void limpiarApellido(char apellido[], char apellidoLimpio[]) 
{
    char *prefijos[] = {"DE", "LA", "LAS", "LOS", "Y", "DEL"};
    int num_prefijos = sizeof(prefijos) / sizeof(prefijos[0]), i, prefijoLen, j;
    bool cambio;
    char temp[30];
    strcpy(temp, apellido);

    for (i = 0; i < stringLength(temp); i++)
        temp[i] = toupper(temp[i]);
    

    strcpy(apellidoLimpio, apellido);

    
    do
	{
        cambio = false;
        for (i = 0; i < num_prefijos && !cambio; i++) 
		{
            prefijoLen = stringLength(prefijos[i]);
            if (strncmp(temp, prefijos[i], prefijoLen) == 0) 
			{
                strcpy(apellidoLimpio, apellidoLimpio + prefijoLen);
                
                if (apellidoLimpio[0] == ' ') 
                    memmove(apellidoLimpio, apellidoLimpio + 1, stringLength(apellidoLimpio));
                
                
                strcpy(temp, apellidoLimpio);
                for (j = 0; j < stringLength(temp); j++) 
                    temp[j] = toupper(temp[j]);
                
                cambio = true; 
            }
        }
    } while (cambio);
}

void seleccionarNombre(char nombre[], char nombreSeleccionado[]) 
{
    char *excepciones[] = {"MARIA", "JOSE", "MA.", "JUANA", "JUAN", "DE", "LA", "LAS", "LOS", "Y", "DEL"};
    int num_excepciones = sizeof(excepciones) / sizeof(excepciones[0]), i, 
    nombre_seleccionado;
    char temp[30]; 
    bool es_excepcion;
    strcpy(temp, nombre);

    for (i = 0; i < stringLength(temp); i++) 
        temp[i] = toupper(temp[i]);

    char *token = strtok(temp, " ");
    nombre_seleccionado = false;

    while (token != NULL && !nombre_seleccionado) 
	{
        es_excepcion = false;
        for (i = 0; i < num_excepciones; i++) 
            if (strcmp(token, excepciones[i]) == 0) 
                es_excepcion = true;
        

        if (!es_excepcion) 
		{
            strcpy(nombreSeleccionado, token);
            nombre_seleccionado = true;
        }

        token = strtok(NULL, " ");
    }

    if (!nombre_seleccionado)
        strcpy(nombreSeleccionado, strtok(nombre, " "));
}

bool validarRFC(struct infoDatosPersonales *datos) 
{
    char rfc[11], apellidoPLimpio[31], apellidoMLimpio[31], 
    nombreSeleccionado[31];
    int len, i;
    bool vocal_encontrada, es_valido;

    i = 9;
    while(i < 13)
    {
        if(!(((*(datos->RFC + i) >= 'A' && *(datos->RFC + i) <= 'Z')   || 
			  (*(datos->RFC + i) >= '0' && *(datos->RFC + i) <= '9'))))
            return false;
        i++;
    }
    
    
    limpiarApellido(datos->apellidoPaterno, apellidoPLimpio);
    limpiarApellido(datos->apellidoMaterno, apellidoMLimpio);

    seleccionarNombre(datos->nombres, nombreSeleccionado);

    rfc[0] = toupper(apellidoPLimpio[0]);
    len = stringLength(apellidoPLimpio);
    vocal_encontrada = false;
    
    if (len > 1) 
	{
        i = 1;
        while(!vocal_encontrada && i < len)
        {
            if(strchr("AEIOUaeiou", apellidoPLimpio[i]) != NULL)
            {
                rfc[1] = toupper(apellidoPLimpio[i]);
                vocal_encontrada = true;
            }

            i++;
        }
    }
    
    if (!vocal_encontrada)
        rfc[1] = 'X';

    rfc[2] = toupper(apellidoMLimpio[0]);

    rfc[3] = toupper(nombreSeleccionado[0]);

    sprintf(rfc + 4, "%02d%02d%02d", datos->yearBirth % 100, datos->monthBirth, datos->dayBirth);

    rfc[10] = '\0';

    es_valido = (strncmp(rfc, datos->RFC, 10) == 0);
        
    return es_valido;
}

bool esCorreoElectronico(char *correo) 
{
    int i = 0;
    bool arrobaEncontrada = false;
    bool puntoEncontradoDespuesDeArroba = false;

    while (correo[i] != '\0')
    {
        
        if (correo[i] == ' ' || !(isCharAlphabetic(correo + i, true) || correo[i] == '@' || correo[i] == '.' || correo[i] == '-' || correo[i] == '_'))
            return false;

        if (correo[i] == '@')
        {
            if (arrobaEncontrada)
                return false;
            
            arrobaEncontrada = true;

            if (i == 0 || correo[i + 1] == '\0' || !isCharAlphabetic(correo + i + 1, false))
                return false;
        }

        if (arrobaEncontrada && correo[i] == '.')
        {
            
            if (correo[i + 1] == '\0' || !isCharAlphabetic(correo + i + 1, false) || !isCharAlphabetic(correo + i - 1, false))
                return false;
            
            puntoEncontradoDespuesDeArroba = true;
        }
        i++;
    }

    return arrobaEncontrada && puntoEncontradoDespuesDeArroba;
}
