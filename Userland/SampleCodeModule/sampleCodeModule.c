/* sampleCodeModule.c */
#include <libC.h>
#include <shell.h>

extern void writePixel(int x, int y,  int red, int green, int blue);

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

int main() {
	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	/* if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF; */
	shell();
}
