#include "syscall.h"
#include "copyright.h"
/*Tao mot file co ten la "Do an 2" (nhap tu console)
Sau do nhap mssv va ten cua cac thanh vien co dang mssv-hoten vao file vua tao.
Xuong dong Enter.
Sau do doc file do.
*/

int main(int argc, char* argv[])
{	
		/*OpenFileID open; 
		int isCreate = CreateFile("hello1");
		open = OpenFileFunc("hello1", 0);
		if (open==-1) PrintString("Can not open file\n");
		WriteFile("123", 3, open);
		CloseFile(open);*/
	
	OpenFileID infor;
	OpenFileID openFileInfor;
	int totalLength;
	char c = '\n';
	int numBytes;
	int n = 3;	// so sv trong nhom
	int length;
	char fileName[255], content[255], contentFile[255];
	OpenFileID inConsole = OpenFileFunc("stdin", 2);
	OpenFileID outConsole = OpenFileFunc("stdout", 3);
		if (inConsole == -1)
	{
		PrintString("Can not open console\n");
		return 0;
	}
	PrintString("Input fileName: ");
	ReadFile(fileName, 255, inConsole); 
	//PrintString(fileName);
	CreateFile(fileName);
	infor = OpenFileFunc(fileName, 0);
	if (infor == -1)
	{
		PrintString("Can not open file \n");
		return 0;
	}
	PrintString("\nNhap vao noi dung cua file:\n");
	while(n >= 1){
		length = ReadFile(content, 255, inConsole);
		//PrintString(content);
		WriteFile(content, length, infor);
		WriteFile(&c, 1, infor);
		n--;
		if (n == 0) break;
	}
	CloseFile(infor);
	infor = OpenFileFunc(fileName, 0);
	totalLength = ReadFile(contentFile, 255, infor);
	PrintString("Kich thuoc: ");
	PrintInt(totalLength);
	PrintString("\n");
	//PrintString(contentFile);
	WriteFile(contentFile, totalLength, outConsole);
	CloseFile(inConsole);
	CloseFile(outConsole);
	CloseFile(infor);
	return 0;
}
