#include <calculator.h>
#include <libC.h>


void runCalc(char * str, int dim) {
    // char vec[dim];
    // infijaToPosfija(str, vec, dim);
}


// void infijaToPosfija(char * str, char * vec, int dim) {
//     int pos = 0;
//     char stack[dim];
//     int peek = 0;
//     int pos2 = 0;
//     while (str[pos2] != '=') {
//         while (str[pos2] == ' ') pos2++;
//         if (!isToken(str[pos2])) {
//             vec[pos] = str[pos2];
//             pos++;
//         } else {
//             while (peek != 0 && precedence(stack[peek - 1], str[pos2])) {
//                 vec[pos] = stack[peek - 1];
//                 pos++;
//                 peek--;
//             }
//             if (str[pos2] == ')') {
//                 if (peek != 0 && stack[peek - 1] == '(') {
//                     peek--;
//                 } else {
//                     print("Error missing (");
//                     return;
//                 }
//             } else {
//                 stack[peek] = str[pos2];
//                 peek++;
//             }
//         }
//         pos2++;
//     }

//     while (peek != 0) {
//         if (stack[peek - 1] == '(') {
//             print("Error missing )");
//         } else {
//             vec[pos] = stack[peek - 1];
//             pos++;
//             peek--;
//         }
//     }
// }


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
    return (token == '+' || token == '-' || token == '*' || token == '/' || token == '^'|| token == ')'|| token == '(');
}



void infijaToPosfija(char * input, char * output, int dim){
    int pos_output=0;
    int pos_input=0;
    int stack_pos=0;
    char stack [100];
    while (input[pos_input]!= '=')
    {   

        char current=input[pos_input++];
        
        if (isToken(current)&&input[pos_input]==' ')//es un signo y no un numero negativo
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
        else if ( current== ' ')
        {
            pos_input;
            //printf("done4");
        }
        //throw exception no es ni numero ni operando valido       
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
    printf("%s",output);
}