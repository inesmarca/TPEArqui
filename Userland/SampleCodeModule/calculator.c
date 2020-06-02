#include <calculator.h>

char * eval( char * first,int first_dim,char * second,int second_dim,char operation);

long stringtoLong(char * number);

char * evaluatePosfija(char * input);

int findDim(const char * num);

int precedence(char token1, char token2);

int isToken(char token);

void infijaToPosfija(char * input, char * output);

char * longtoString(long number,int dim,char * output);

char * malloc2();

char * ajustardecimales(char * input);


#define NULL 0
#define MAX_NUM_IN_EXPRESION 20
#define MAX_NUMBER_LENGTH 20
#define MAX_INPUT_LENGTH 100
#define CANT_DECIMALES_INTER_OPERACIONES 6 
#define CANT_DECIMALES_OUTPUT 4 //siempre tiene que ser menos que cant_decimales_inter_operaciones



char * runCalc(char * str) {
    char aux[MAX_INPUT_LENGTH];
    infijaToPosfija(str, aux);
    char * result =evaluatePosfija(aux);
    return ajustardecimales(result);
}


char * ajustardecimales(char * input){
    int index=0;
    while (input[index]!='.')
    {
        index++;
    }
    index+=CANT_DECIMALES_OUTPUT+1;
    if (input[index] - '0' >= 5)
    {
      input[index] = 0;
      long aux = stringtoLong (input);
      aux++;
      input = longtoString (aux, CANT_DECIMALES_OUTPUT, input);
    }
  else
    {
      input[index] = 0;
    }

  //termina y deja CANT_DECIMALES _OUTPUT
  return input;
}


char * malloc2(){
    //esto es privado, no se deberia usar afuera del scope de la calculadora
    
    //  muy mala pseudo implementacion para poder conseguir memoria(necesito malloc. porque es tan dificil de implementar bien, me quiero matarrrrr)
    
    static char  freemem [MAX_NUM_IN_EXPRESION] [MAX_NUMBER_LENGTH];
    static int index=-1;
    index+=1;
    return freemem[index];
}





char * eval( char * first,int first_dim,char * second,int second_dim,char operation){
    
    long firstnum=stringtoLong(first);
    long secondnum=stringtoLong(second);
    long result=0;
    int result_dim=-1;//nunca puede ser un valor negativo, si sigue negativo al final hay un error
    
    
    while (first_dim<CANT_DECIMALES_INTER_OPERACIONES) //fijo  las dimensiones al minimo accurate decimales para poder operar bien
    {
        firstnum*=10;
        first_dim++;
    }
     while (second_dim<CANT_DECIMALES_INTER_OPERACIONES) //fijo  las dimensiones al minimo accurate decimales para poder operar bien
    {
        secondnum*=10;
        second_dim++;
    }
    switch (operation)
    {
    case '+':
        while (first_dim<second_dim) //igualo las dimensiones para poder operar bien
        {
        firstnum*=10;
        first_dim++;
        }
        while (second_dim<first_dim) //igualo las dimensiones para poder operar bien
        {
            secondnum*=10;
            second_dim++;
        }
            result+=firstnum;
            result+=secondnum;
            result_dim=first_dim;
            break;
     case '-':
        while (first_dim<second_dim) //igualo las dimensiones para poder operar bien
        {
        firstnum*=10;
        first_dim++;
        }
        while (second_dim<first_dim) //igualo las dimensiones para poder operar bien
        {
            secondnum*=10;
            second_dim++;
        }
        result=secondnum;
        result-=firstnum;
        result_dim=first_dim;
        break;

     case '*':
        result=firstnum;
        result*=secondnum;
        result_dim=first_dim+second_dim;
        while (result_dim>CANT_DECIMALES_INTER_OPERACIONES) //corrijo para que me queden solo Cant_decimal_inter_operaciones
        {
            result/=10;
            result_dim--;
        }
        break;
     case '/':
     while (second_dim<2*CANT_DECIMALES_INTER_OPERACIONES) //fijo  las dimensiones al minimo accurate decimales para poder operar bien
    {
        secondnum*=10;
        second_dim++;
    }
        result=secondnum;
        result/=firstnum;
        result_dim=second_dim-first_dim;

        break;
    }
   

 while (result_dim>CANT_DECIMALES_INTER_OPERACIONES) //corrijo para que me queden solo Cant_decimal_inter_operaciones
        {
            result/=10;
            result_dim--;
        }

    return longtoString(result,result_dim,malloc2()); //uso el first porque si se pasa de largo pisa el second. no se pueden instanciar arrays adentro del scope de la funcion porque van a fallar
}


char * longtoString(long number,int dim,char * output)
{ 
    char aux [20];
    int index=0;
    int index2=0;
    int negative=0;
    if (number<0)
    {
        negative=1;
    }
    
    while (number!=0)
    {
        if(dim==0)
        {
          aux[index++]='.';
        }
        int auxiliar=number % 10;
        if(auxiliar<0){
            number*=-1; 
        }
        aux[index++] = auxiliar + '0';
        number /= 10;
        dim--;
        //resto negativo quickfix
        
    }
    
    if(dim==0){
          aux[index++]='.';
          aux[index++]='0';
    }

    if (negative)
    {
        aux[index++]='-';
    }
    
    while (index!=0)
    {
        output[index2++]=aux[--index];
    }
    output[index2]=0;
   
    return output;
    int auxiliar=number % 10;
    
}

long stringtoLong (char *number)
{
  char negative = 0;
  long int sum = 0;
  int index = 0;
  while (number[index] != 0)
    {
      if (number[index] == '-')
    {
      negative = 1;
    }
      if (number[index] >= '0' && number[index] <= '9')
    {
      sum *= 10;
      sum += (number[index] - '0');
    }
      index++;
    }
  if (negative)
    {
      sum *= -1;
    }
  return sum;

}


int findDim(const char * num){//retorna la cantidad de decimales que encuentra
    char decimal_found=0;
    int pos=0;
    int dim=0;
    while (num[pos]!=0)
    {
        
        if (decimal_found)
        {
            dim++;
        }
        if (num[pos]=='.')
        {
            decimal_found=1;
        }
        pos++;
    }
    return dim;

}


char * evaluatePosfija(char * input)
{
    int input_pos=0;//posicion en el array del input.
    int stack_pos=0;
    char * stack [20];//stack de strings o matriz de chars, depende de como lo pienses
    while (input[input_pos]!=0)
    {
        char current=input[input_pos++];
        if (isToken(current)&&input[input_pos]==' ')//se fija que sea token y chequea el caso de que sea un numero negativo
        {
            
            char * first=stack[--stack_pos];
            int first_dim=findDim(first);
            char * second=stack[--stack_pos];
            int second_dim=findDim(second);
            stack[stack_pos++]=eval(first,first_dim,second,second_dim,current);
           
        }
        else if ((current>='0'&&current<='9')||(current=='-'&&input[input_pos]>='0'&&input[input_pos]<='9')) //number
        {
            char * auxiliar=malloc2();
            int index=0; 
            while (input[input_pos-1]!=' ')
            {
                auxiliar[index++]=input[input_pos++-1]; //copio el numero
            }
            auxiliar[index]=0;//pongo el 0 para terminate el string.
            stack[stack_pos++]=auxiliar;//meto el string formado al stack.
        }
    }
    if (stack_pos-1==0)
    {

        return stack[0];//si se hizo bien, el stack solo tiene 1 elemento
    }
    //lanzar exception
   

}






int precedence(char token1, char token2) {
    switch (token1) {
    case '+':
        if (token2 == '+' || token2 == '-' || token2 == ')') 
            return 1;
        else
            return 0;
    case '-':
        if ( token2 == '+' || token2 == '-' || token2 == ')')
            return 1;
        else
            return 0;
    case '*':
        if (token2 == '+' || token2 == '-' || token2 == '*' || token2 == '/' || token2 == ')')
            return 1;
        else
            return 0;
    case '/':
        if ( token2 == '+' || token2 == '-' || token2 == '*' || token2 == '/' || token2 == ')')
            return 1;
        else
            return 0;
    case '^':
        if (token2 == '+' || token2 == '-' || token2 == '*' || token2 == '/' || token2 == ')') 
            return 1;
        else
            return 0;
    case '(':
        return 0;

    
    default:
        break;
    }
}

int isToken(char token) {
    return (token == '+' || token == '-' || token == '*' || token == '/' || token == '^');
}


//toma la expresion infija y la trafsorma en posfija
void infijaToPosfija(char * input, char * output){
    int pos_output=0;
    int pos_input=0;
    int stack_pos=0;
    char stack [100];
    while (input[pos_input]!= '=')
    {   

        char current=input[pos_input++];
        if (current=='(')
        {
             stack[stack_pos++]=current;
        }
        else if(current==')')
        {
            current=stack[--stack_pos];// tiro el ) y pusheo hasta encontrar el bracket correspondiente
            while (current!='(')
            {
                output[pos_output++]=current;
                output[pos_output++]=' ';
                current=stack[--stack_pos];
            }
            
        }
        
        
        else if (isToken(current)&&input[pos_input]==' ')//es un signo y no un numero negativo
        {
            while (stack_pos!=0&&precedence(stack[stack_pos-1],current))
            {
                char character=stack[--stack_pos];
                if (character!='('&&character!=')')
                {
                    output[pos_output++]=character;
                    output[pos_output++]=' ';
                }
                
                //printf("done2");
                
            }
            stack[stack_pos++]=current;
            
        }
        else if ((current>='0'&&current<='9')||(current=='-'&&input[pos_input]>='0'&&input[pos_input]<='9'))
            //si es un numero o si arranca con un - pero continua con un numero
            {
            while ((current>='0'&&current<='9')||current=='.'||current=='-')//mientras que sea numero o punto decimal o el menos de un negativo
            {
                output[pos_output++]=current;
                current=input[pos_input++]; //sigue imprimiendo hasta llegar al espacio
                 
                //printf("done3");
            }
            output[pos_output++]=' '; //insertar el espacio para poder marcar por terminado
            
            }    
    }
    while (stack_pos!=0) //popear el resto del stack
    {
       char current=stack[--stack_pos];
       if (current!='('&&current!=')')
       {
        output[pos_output++]=current;
        output[pos_output++]=' ';
       }
        
    }
    output[pos_output++]=' ';
    output[pos_output-1]=0;
}
