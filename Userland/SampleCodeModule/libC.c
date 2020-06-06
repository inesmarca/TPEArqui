#include <libC.h>
#include <stdarg.h>
#include <math.h>
#include <sysLib.h>

#define MAX_DIGITOS_EN_UN_NUMERO 20
#define DECIMALPLACES 4
#define MAX_PRINTABLE_CHARACTERS 1024
#define MAX_READABLE_CHARACTERS 1024
#define DEFAULT_LETTER_COLOR 0xFFFFFF
#define DEFAULT_BACKGROUND_COLOR 0x000000

int letter_color = DEFAULT_LETTER_COLOR;
int background_color = DEFAULT_BACKGROUND_COLOR;

void changeLetterColor(int code) {
	letter_color = code;
} 

void changeBackgroundColor(int code) {
	background_color = code;
}

//https://www.techiedelight.com/implement-strcpy-function-c/ era muy sencilla asi que la tomamos de internet.
char * strcpy(char * destination, const char * source){
	char * ptr=destination;
	while (*source != 0)
	{
		*destination=*source;
		destination++;
		source++;
	}
	*destination=0;
	return ptr;
	
}

int strcmp(char * s1, char * s2) {
    int cmp = 1;
    int i;
    for ( i = 0; s1[i] != 0 && s2[i] != 0 && cmp; i++) {
        if (s1[i] != s2[i]) {
            cmp = 0;
        }
    }

    if ((s1[i] == 0 && s2[i] != 0) || (s1[i] != 0 && s2[i] == 0) ) {
        cmp = 0;
    }
    return cmp;
}

void putChar(char str) {
	writeScreen(&str, letter_color, background_color);
}

char getChar() {
	char res = 0;
    while (res == 0) {
	    readKeyBuff(&res);
    }
	putChar(res);
	return res;
}

void printf(const char * format,...){
	//tiene que tener el formato correcto para funcionar bien. si hay % faltantes o sobrantes no va afuncionar.
	//tiene soporte para %c %d %s
	//wont print more all if the resulting string is greater than 1024 characters
	char output [MAX_PRINTABLE_CHARACTERS];
  
	va_list valist;
    va_start( valist, format );
	int output_pos=0;
	for (int i = 0; format[i] != 0; i++)
	{
		if (format[i]=='%')
		{
			i++;
			switch (format[i])
			{
			case 'c':
				output[output_pos++]=(va_arg( valist, int ));
				break;
			
			// case 'f':
			// 	;
			// 	char auxdouble[MAX_DIGITOS_EN_UN_NUMERO];
			// 	int counterdouble=doubleToString(va_arg(valist,double),auxdouble);
			// 	output[output_pos++]=(va_arg( valist, char ));
			// 	if (counterdouble>MAX_DIGITOS_EN_UN_NUMERO)
			// 	{
			// 		/* should throw exception*/
			// 		//no acepta doubles con mas de MAX_DIGITOS_EN_UN_NUMERO digitos.
			// 	}
			// 	for (int j = 0; j < counterdouble; j++)
			// 	{
			// 		output[output_pos++]=auxdouble[j];//copio el double hecho string a mi output
			// 	}
			// 	break;

			case 'd':
                ;//algo que ver con c y switch que son raros
				char aux [MAX_DIGITOS_EN_UN_NUMERO];
				int counter=intToString(va_arg( valist, int ),aux);//me transforma el int a un string
				if (counter>MAX_DIGITOS_EN_UN_NUMERO)
				{
					/* should throw exception*/
					//no acepta int's con mas de MAX_DIGITOS_EN_UN_NUMERO digitos.
				}
				for (int j = 0; j < counter; j++)
				{
					output[output_pos++]=aux[j];//copio el in hecho string a mi output
				}
				break;
			case 's': //copio el string
            ;//algo que ver con c y switch que son raros
				char * string2=(char *)va_arg( valist, char* );
               
				int j=0;
            
                
                
				while (string2[j] != 0)//busco que termine el string a copiar
				{
                    
					output[output_pos++]=string2[j++];
                   
				}
                
				
				break;
			
			default:
			/* should throw exception*/
			//expression not suported
				break;
			}
		}
        else //just copy the string
		{
			output[output_pos++]=format[i];
		}
		
		
	}
	va_end(valist);
    output[output_pos]=0;
	writeScreen(output, letter_color, background_color);

    
    
}

int scanf(const char *format, ...){
    //tiene que tener el formato correcto para funcionar bien. si hay % faltantes o sobrantes no va afuncionar.
	//tiene soporte para %c %d %s
	//lee como maximo MAX_READABLE_CHARACTERS (1024 characters)
	char output [MAX_READABLE_CHARACTERS];
  
	va_list valist;
    va_start( valist, format );
    int output_pos=0;
    int number_of_vars=0;
	for (int i = 0; format[i] != 0; i++)
	{
		if (format[i]=='%')
		{
			i++;
            number_of_vars++;
			switch (format[i])
			{
			case 'c':
				break;
			
			case 'd':
                ;//algo que ver con c y switch que son raros
				break;
			case 's': 
            ;//algo que ver con c y switch que son raros
				break;
			
			default:
			/* should throw exception*/
			//expression not suported
				break;
			}
		}
	}
	va_end(valist);
    return number_of_vars;
}

int intToString(int value, char * buffer)
{
	char *p = buffer;
	char *p1, *p2;
	int digits = 0;

	//Calculate characters for each digit
	do
	{
		int remainder = value % 10;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= 10);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

// int doubleToString(double value, char * buffer){
	
// 	int trunkated=(int)(value*1000);
	
	// int buf_pos=0;
	// int j=positivedigits(value);
	// double aux=1;
	// for (int i = 0; i <= j; i++)
	// {
	// 	aux*=10;
	// }
	// //tiene restricciones con SSE y no le gusta las potencias, asi que lo hago internamente.
	
	// for(;j>-DECIMALPLACES;j--)
	// {
		
	// 	buffer[buf_pos++]=(int)(value/aux)+'0';
	// 	aux/=10;
	// }
	// return buf_pos;
	

//}
// int positivedigits(double value){
// 	//devuelve la cantidad de digitos positivos en un numero.
// 	//34.7 retorna 2,2 retorna 1 y 0.04 retorna 0.
// 	int i = 0;
// 	double aux=1;
// 	while ( aux >= value )
// 	{
// 		i++;
// 		aux*=10;
// 	}
// 	return i-1;
	
// }

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

int fix_format_hours(int time) {
    int aux = time/16;
    aux *= 10;
    aux = aux + (time % 16) - 3;
    if (aux < 0) {
        aux += 24;
    }
    return aux % 24;
}

int fix_format(int time) {
    int aux = time / 16;
    aux *= 10;
    aux = aux + (time % 16);
    return aux;
} 

void printTime() {
    printf("%d:%d:%d\n", fix_format_hours(getRTC(4)), fix_format(getRTC(2)), fix_format(getRTC(0)));
}

void printTemperature() {
	printf("%d\n", getTemperature());
}