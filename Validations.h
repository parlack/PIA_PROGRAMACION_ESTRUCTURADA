#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "Estructuras_granja.h"


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

bool isAlphabetic(char *charLine, bool isAlphaNumeric)
{
	bool isValid = true;
	int i = 0;
	
    while (*(charLine + i) != '\0' && isValid)
    {
        if(!isCharAlphabetic(charLine + i, isAlphaNumeric) || *(charLine + i) != ' ')
        {
            isValid = false;
        }
            
        i++;
    }
	
	return isValid;
}

bool isCharAlphabetic(char *char, bool isAlphaNumeric)
{
    bool isValid = true;

    if(isAlphaNumeric)
    {
        if (!((*char >= 'a' && *char <= 'z') || 
              (*char >= 'A' && *char <= 'Z') || 
              (*char >= '0' && *char <= '9')))
        {
            isValid = false;
        }
    }
    else
    {
        if (!((*char >= 'a' && *char <= 'z') || 
              (*char >= 'A' && *char <= 'Z')))
        {
            isValid = false;
        }
    }
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

// Función para eliminar prefijos comunes en apellidos compuestos
void limpiarApellido(char apellido[], char apellidoLimpio[]) 
{
    char *prefijos[] = {"DE", "LA", "LAS", "LOS", "Y", "DEL"};
    int num_prefijos = sizeof(prefijos) / sizeof(prefijos[0]), i, prefijoLen, j;
    bool cambio;
    char temp[30];
    strcpy(temp, apellido);

    // Convertir a mayúsculas para una comparación uniforme
    for (i = 0; i < stringLength(temp); i++)
        temp[i] = toupper(temp[i]);
    

    // Inicialmente copiar el apellido a apellidoLimpio
    strcpy(apellidoLimpio, apellido);

    // Iterar sobre los prefijos mientras se encuentren en el inicio
    
    do
	{
        cambio = false;
        for (i = 0; i < num_prefijos && !cambio; i++) 
		{
            prefijoLen = stringLength(prefijos[i]);
            if (strncmp(temp, prefijos[i], prefijoLen) == 0) 
			{
                // Desplazar el apellido a la izquierda
                strcpy(apellidoLimpio, apellidoLimpio + prefijoLen);
                
                // Eliminar espacio en blanco inicial si queda alguno
                if (apellidoLimpio[0] == ' ') 
                    memmove(apellidoLimpio, apellidoLimpio + 1, stringLength(apellidoLimpio));
                
                
                // Volver a copiar apellidoLimpio en temp para comparar en mayúsculas
                strcpy(temp, apellidoLimpio);
                for (j = 0; j < stringLength(temp); j++) 
                    temp[j] = toupper(temp[j]);
                
                cambio = true;  // Indicar que hubo un cambio y repetir
            }
        }
    } while (cambio);
}

// Función para seleccionar el nombre correcto ignorando "José" o "María" si es necesario
void seleccionarNombre(char nombre[], char nombreSeleccionado[]) 
{
    char *excepciones[] = {"MARIA", "JOSE", "MA.", "JUANA", "JUAN", "DE", "LA", "LAS", "LOS", "Y", "DEL"};
    int num_excepciones = sizeof(excepciones) / sizeof(excepciones[0]), i, 
    nombre_seleccionado;
    char temp[30]; 
    bool es_excepcion;
    strcpy(temp, nombre);

    // Convertir a mayúsculas para una comparación uniforme
    for (i = 0; i < stringLength(temp); i++) 
        temp[i] = toupper(temp[i]);

    // Dividir nombres si es un nombre compuesto
    char *token = strtok(temp, " "); //Para dividir los nombre
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

    // Si todos los nombres son excepciones, tomar el primer nombre completo
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
    
    

    // Limpiar los apellidos para eliminar prefijos innecesarios
    limpiarApellido(datos->apellidoPaterno, apellidoPLimpio);
    limpiarApellido(datos->apellidoMaterno, apellidoMLimpio);

    // Seleccionar el nombre correcto
    seleccionarNombre(datos->nombres, nombreSeleccionado);

    // 1. Tomar la primera letra y vocal interna del apellido paterno
    rfc[0] = toupper(apellidoPLimpio[0]);
    len = stringLength(apellidoPLimpio);
    vocal_encontrada = false;
    
    // Asegurarse de que el apellido paterno tiene más de una letra
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
    
    // Si no se encuentra vocal interna o el apellido es muy corto, usar 'X'
    if (!vocal_encontrada)
        rfc[1] = 'X';

    // 2. Tomar la primera letra del apellido materno
    rfc[2] = toupper(apellidoMLimpio[0]);

    // 3. Tomar la primera letra del nombre seleccionado
    rfc[3] = toupper(nombreSeleccionado[0]);

    // 4. Tomar el año, mes y día de nacimiento y añadirlos al RFC
    sprintf(rfc + 4, "%02d%02d%02d", datos->yearBirth % 100, datos->monthBirth, datos->dayBirth);

    // Asegurarse de que el RFC generado tenga una longitud de 10 para comparar
    rfc[10] = '\0';

    // Comparar los primeros 10 caracteres del RFC generado con el RFC original proporcionado
    es_valido = (strncmp(rfc, datos->RFC, 10) == 0);
    printf("\n%s %s\n", datos->RFC, rfc);
        
    return es_valido;
}

bool esCorreoElectronico(char *correo) 
{
    int i = 0;
    bool arrobaEncontrada = false;
    bool puntoEncontradoDespuesDeArroba = false;

    while (correo[i] != '\0')
    {
        
        if (correo[i] == ' ' || !(isCharAlphabetic(correo[i], true) || correo[i] == '@' || correo[i] == '.' || correo[i] == '-' || correo[i] == '_'))
            return false;

        if (correo[i] == '@')
        {
            if (arrobaEncontrada)
                return false;
            
            arrobaEncontrada = true;

            if (i == 0 || correo[i + 1] == '\0' || !isCharAlphabetic(correo[i + 1], false))
                return false;
        }

        if (arrobaEncontrada && correo[i] == '.')
        {
            
            if (correo[i + 1] == '\0' || !isCharAlphabetic(correo[i + 1], false) || !isCharAlphabetic(correo[i - 1], false))
                return false;
            
            puntoEncontradoDespuesDeArroba = true;
        }
        i++;
    }

    return arrobaEncontrada && puntoEncontradoDespuesDeArroba;
}