#include <calculator.h>
#include <video_driver.h>

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

void runCalc(char * str, int dim) {
    // char vec[dim];
    // infijaToPosfija(str, vec, dim);
}

int isToken(char token) {
    return (token == '+' || token == '-' || token == '*' || token == '/' || token == '^');
}

void infijaToPosfija(char * str, char * vec, int dim) {
    int pos = 0;
    char stack[dim];
    int peek = 0;
    int pos2 = 0;
    while (str[pos2] != '=') {
        while (str[pos2] = ' ') pos2++;
        if (!isToken(str[pos2])) {
            vec[pos] = str[pos2];
            pos++;
        } else {
            while (peek != 0 && precedence(stack[peek - 1], str[pos2])) {
                vec[pos] = stack[peek - 1];
                pos++;
                peek--;
            }
            if (str[pos2] == ')') {
                if (peek != 0 && stack[peek - 1] == '(') {
                    peek--;
                } else {
                    print("Error missing (");
                    return;
                }
            } else {
                stack[peek] = str[pos2];
                peek++;
            }
        }
        pos2++;
    }

    while (peek != 0) {
        if (stack[peek - 1] == '(') {
            print("Error missing )");
        } else {
            vec[pos] = stack[peek - 1];
            pos++;
            peek--;
        }
    }
}