// Va en UserLand

#include <libC.h>
#include <func.h>

int fix_retarded_format_hours(int time) {
    int aux = time/16;
    aux *= 10;
    aux = aux + (time % 16) - 3;
    if (aux < 0) {
        aux += 24;
    }
    return aux % 24;
}

int fix_retarded_format(int time) {
    int aux = time / 16;
    aux *= 10;
    aux = aux + (time % 16);
    return aux;
} 

void printTime() {
    printf("%d:%d:%d/n", fix_retarded_format_hours(getRTC(4)), fix_retarded_format(getRTC(2)), fix_retarded_format(getRTC(0)));
}