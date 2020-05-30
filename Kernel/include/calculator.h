
void runCalc(const char * str, int dim);

char * eval( char * first,int first_dim,char * second,int second_dim,char operation);

long stringtoLong(char * number);

char * evaluatePosfija(char * input);

int findDim(const char * num);

int precedence(char token1, char token2);

int isToken(char token);

void infijaToPosfija(char * input, char * output, int dim);

char * longtoString(long number,int dim,char * output);
