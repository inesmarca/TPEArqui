#include <calculator.h>

#define NULL 0

void runCalc(const char * str, int dim) {
    // char vec[dim];
    // infijaToPosfija(str, vec, dim);
}

char * eval( char * first,int first_dim,char * second,int second_dim,char operation){
    
    long firstnum=stringtoLong(first);
    long secondnum=stringtoLong(second);
    long result=0;
    int result_dim=-1;//nunca puede ser un valor negativo, si sigue negativo al final hay un error
    
    
    while (second_dim>first_dim) //igualo las dimensiones para poder operar bien
    {
        firstnum*=10;
        first_dim++;
    }
     while (second_dim<first_dim) //igualo las dimensiones para poder operar bien
    {
        secondnum*=10;
        second_dim++;
    }
    switch (operation)
    {
    case '+':
        result+=firstnum;
        result+=secondnum;
        result_dim=first_dim;

        break;
     case '-':
        result=firstnum;
        result-=secondnum;
        result_dim=first_dim;
        break;
     case '*':
        result=firstnum;
        result*=secondnum;
        result_dim=first_dim+second_dim;
        break;
     case '/':
        result=firstnum;
        result/=secondnum;
        result_dim=first_dim-second_dim;
        break;
    default:
    //unsupported operation
        break;
    }
    return longtoString(result,result_dim,first); //uso el first porque si se pasa de largo pisa el second. no se pueden instanciar arrays adentro del scope de la funcion porque van a fallar
}


char * longtoString(long number,int dim,char * output){
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
        if(dim==0){
          aux[index++]='.';
        }
      
        aux[index++]=number%10+'0';
        number/=10;
        dim--;
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
            int start=input_pos-1; //es la primer posicion del numero,(el comienzo de mi string)
            while (input[input_pos]!=' ')
            {
                input_pos++; //busco el final del numero
            }
            input[input_pos++]=0;//pongo el 0 para terminate el string.
            stack[stack_pos++]=input+sizeof(char)*start;//meto el string formado al stack.
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


// la dimencion no fue usada en ningun lugar, podriamos hacer algo con eso o lo sacamos.
void infijaToPosfija(char * input, char * output, int dim){
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
    output[pos_output-1]=0;
}