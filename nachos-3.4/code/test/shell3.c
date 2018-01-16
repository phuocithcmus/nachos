#include "syscall.h"

int main(){
	SpaceId newProc;
	SpaceId newProc1;
	/*OpenFileID fileId;
	char name[255];
	while(1){
	PrintString("Nhap file name: ");
	ReadString(name, 255);
	if (name[0] == 'e') break;
	if ( (fileId = OpenFileFunc(name, 0)) == -1)
	{
		PrintString("Khong the mo file. Nhap lai");
		continue;
	}*/
	
	newProc = Exec("./test/pong");
	newProc1 = Exec("./test/ping");
	Join(newProc);
	Join(newProc1);	
	//}
	return 0;
}
