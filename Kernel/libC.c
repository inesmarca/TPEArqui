#include <libC.h>
#include <stdarg.h>

#define MAX_PRINTABLE_CHARACTERS 1024

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
				output[output_pos++]=(va_arg( valist, char ));
				break;
			
			case 'd':
                ;//algo que ver con c y switch que son raros
				char aux [20];
				int counter=intToString(va_arg( valist, int ),aux);//me transforma el int a un string
				if (counter>20)
				{
					/* should throw exception*/
					//no acepta int's con mas de 20 digitos.
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
	write(1, output, output_pos);

    
    
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
