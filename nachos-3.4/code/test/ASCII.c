/*------------------DO AN 1 - File Name: BubbleSort.c-----------------
-	1512423 - Nguyen Duc Phuoc	 			     -
-	1512421 - Dinh Huu Phuoc	 			     -
-	1512433 - Nguyen Nhat Quang	 			     -
---------------------------------------------------------------------*/
#include "syscall.h"
#include "copyright.h"
int main()
{	
	int j;
	PrintString("In bang ma ASCII\n");
	for (j = 0;j < 127;j++){
		PrintInt(j);
		PrintString(": \t");
		PrintChar(j);
		PrintChar('\n');
	}

	return 0;
}
