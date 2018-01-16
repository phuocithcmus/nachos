#include "syscall.h"
#include "copyright.h"

int main(int argc, char* argv[])
{
	char mess[255];
	unsigned int i ;
	OpenFileID inConsole = OpenFileFunc("stdin", 2);
	OpenFileID outConsole = OpenFileFunc("stdout", 3);

	PrintString("\nDa mo file xong !!!\n");
	if (inConsole == -1 || outConsole == -1)
	{
		PrintString("Can not open console\n");
		return 0;
	}
	PrintString("Stdin mode: \n");
	ReadFile(mess, 255, inConsole); 
	//PrintString(mess);
	
	WriteFile(mess, 255, outConsole);
	CloseFile(inConsole);
	CloseFile(outConsole);
	return 0;
}
