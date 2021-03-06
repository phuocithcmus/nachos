/*------------------DO AN 1 - File Name: Exception.cc-----------------
-	1512423 - Nguyen Duc Phuoc	 			     -
-	1512421 - Dinh Huu Phuoc	 			     -
-	1512433 - Nguyen Nhat Quang	 			     -
---------------------------------------------------------------------*/
/*
- Chinh sua, them va copy mot so dong lenh trong cac files, folders:
	+ mipssim.cc: copy lenh tang bien dem cho thanh ghi
	+ system.h va system.cc: them va khoi tao, xoa vung nho cua con tro gSynchConsole
	+ threads: them thu vien SynchConsole
	+ Makefile.common: them duong dan cho 2 tep SynchConsole
	+ cac file start.c, start.s: them lenh MIPS khi viet system call
	+ syscall.h: dinh nghia ham va define cho tung system call
	+ makefile: tao lenh MIPS va khai bao chay chuong trinh
*/

// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
	int type = machine->ReadRegister(2);
	switch (which){
		case NoException: // Everything ok!
			printf("Everything ok!");
			break;
		case SyscallException: // A program executed a system call.
			switch (type){
				case SC_Halt:
					DEBUG('a', "Shutdown, initiated by user program.\n");
   					interrupt->Halt();
					break;	
				case SC_ReadInt:
				{
					bool a = true;
					//printf("Read Int System Call.");
					int number = 0; 				// this is result
					char *buff = new char[15]; 			// number from console
					int digit = gSynchConsole->Read(buff, 15); 	// bytes of buff
					int i = (buff[0] == '-') ? i = 1 : i = 0; 		// i begin at 1 or 0
					int j = (buff[0] == '-') ? j = 1 : j = 0; 
					for (;j < digit;j++){				// while from console is not a integer
						if (buff[j] < '0' || buff[j] > '9'){
							printf("ReadInt Error. Number form Console is not a integer");
							machine->WriteRegister(2, 0);
							delete buff;
							a = false;
							break;
						}
					}
					if (a == true){
						for (;i < digit;i++){
							number = number*10 + (buff[i] - 48); 
						}
						number = (buff[0] == '-') ? -1*number : number;
						machine->WriteRegister(2, number);
						delete buff;
					}
					break;
				}
				
				case SC_PrintInt:
				{	
					//printf("Print Int into Console.");
					char result[15];
					int n = machine->ReadRegister(4);
					int num = n < 0 ? -1 : 1; 			// check for num. if n < 0 num = -1 and ...
					if (n < 0){
						n = -n;
					}
					int length = 0;					// index of result
					while(n != 0){
						result[length] = n%10 + 48;
						n = n / 10;
						length++;
					}
					int j = 0;
					for (;j < length/2;j++){
						char temp = result[j];
						result[j] = result[length - j - 1];
						result[length - j - 1] = temp;
					}
					if (num == -1){
						char a = '-';
						gSynchConsole->Write(&a,1);
						gSynchConsole->Write(result,length);
					}
					else {
						gSynchConsole->Write(result,length);
					}
				break;
				}

				case SC_ReadChar:
				{
					char c;
					int digit = gSynchConsole->Read(&c, 1); // nhap tu man hinh console
					machine->WriteRegister(2, c);		// ghi vao thanh ghi so 2
				}
				break;
				case SC_PrintChar:
				{
					char ch;
					ch = (char) machine->ReadRegister(4);	//doc tu thanh ghi so 4
					gSynchConsole->Write(&ch, 1);		//xuat ra man hinh console
					break;

				}
				case SC_ReadString:
				{	
					/*char* note = "Chieu dai am. nhap lai";
					int lengthNote = 23;
					char *buffer = new char[100];
					int buff = machine->ReadRegister(4);
					int b = machine->ReadRegister(5);
					if (b < 0){
						printf("Chieu dai am. nhap lai");
						machine->System2User(buff, lengthNote, note);	
					}
					else {
					int l = gSynchConsole->Read(buffer, b);		//nhap tu man hinh console
					machine->System2User(buff, l, buffer);		//chuyen du lieu tu system sang user vi chuoi duoc nhap luu o user		
					}
					delete buffer;*/
					char *buf = new char[255];
					if (buf == 0) break;
					int bufAddrUser = machine->ReadRegister(4);
					int length = machine->ReadRegister(5);
					int sz = gSynchConsole->Read(buf, length);
					machine->System2User(bufAddrUser, sz, buf);
					delete buf;
				}
				break;
				case SC_PrintString:
				{
					int buff = machine->ReadRegister(4);
					char* buffer = new char[100];
					buffer = machine->User2System(buff, 100); 	// chuyen tu user qua kernel
					int i = 0; 					// khong biet chuoi co bao nhieu ki tu ???
					while(buffer[i] != '\0') 			// chay vong while in tung ki tu
					{
						gSynchConsole->Write(&buffer[i],1);
						i++;
					}
					delete buffer;
				}
				break;
				case SC_CreateFile:
				{
					int bufferAdd = machine->ReadRegister(4);	// doc tham so tu user
					char *buffer = new char[100];
					buffer = machine->User2System(bufferAdd, 100);
					// tao file
					if (fileSystem->Create(buffer, 0) == false){
						printf("Khong the tao file!");
						machine->WriteRegister(2, -1); // tao that bai tra ve -1
					}
					else{
						/*printf("Tao file thanh cong !!!");*/
						machine->WriteRegister(2, 0);	// tao file thanh cong tra ve 0
					}
					delete[] buffer;
				}
				break;
				case SC_OpenFileID:
				{
					int bufferAdd = machine->ReadRegister(4);	// doc tham so tu user
					int type = machine->ReadRegister(5);		// loai file can mo 0: doc va ghi, 1: chi doc
					char *buffer = new char[100];
					if (fileSystem->index > 10){
						printf("Khong the mo file!");
						machine->WriteRegister(2, -1); // mo that bai tra ve -1
						delete buffer;
						break;
					}
					buffer = machine->User2System(bufferAdd, 100);
					if (strcmp(buffer, "stdin") == 0){
						printf("Che do stdin\n");
						machine->WriteRegister(2, 0);	// mo file thanh cong tra ve 0
						break;
					}
					if (strcmp(buffer, "stdout") == 0){
						printf("Che do stdout\n");
						machine->WriteRegister(2, 1);	// mo file thanh cong tra ve 1
						break;
					}
					if ((fileSystem->openf[fileSystem->index] = fileSystem->Open(buffer, type)) != NULL){
						//printf("mo file thanh congaa");
						machine->WriteRegister(2, fileSystem->index-1);
					} else {
						printf("Khong the mo file");
						machine->WriteRegister(2, -1);
					}
					delete[] buffer;
				}
				break;
				case SC_CloseFile:
				{
					int m_index = machine->ReadRegister(4);
					if (fileSystem->openf[m_index] == NULL) 
						break;
					delete fileSystem->openf[m_index];
					fileSystem->openf[m_index] = NULL;
					break;
				}
				case SC_ReadFile:
				{
					int bufAddr = machine->ReadRegister(4);
					int NumBuf = machine->ReadRegister(5);
					int m_index = machine->ReadRegister(6);	
					int OldPos;
					int NewPos;
					char *buf = new char[NumBuf];
					int i = 0;
					// Check m_index
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					OldPos = fileSystem->openf[m_index]->GetCurrentPos();
					buf = machine->User2System(bufAddr, NumBuf);
					if (fileSystem->openf[m_index]->type == 2)
					{
						/*  printf("NumBuf = %d\n", NumBuf);*/
						int sz = gSynchConsole->Read(buf, NumBuf);
						/*  machine->System2User(bufAddr, sz, buf);*/
					
						machine->System2User(bufAddr, sz, buf);
						machine->WriteRegister(2, sz);
						break;
					}
					
					if ((fileSystem->openf[m_index]->Read(buf, NumBuf) ) > 0)
					{
						// Copy data from kernel to user space
					  NewPos = fileSystem->openf[m_index]->GetCurrentPos();
						machine->System2User(bufAddr, NewPos - OldPos +1, buf);
						machine->WriteRegister(2, NewPos - OldPos + 1);
					}
					else
					{
						printf("LOI");
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// read data from console 
					
					/*  
					if (fileOpen.type == 2)
					{
						int sz = gSynchConsole->Read(buf, NumBuf);
						machine->System2User(bufAddr, sz, buf);
						machine->WriteRegister(2, sz);
					}*/
					delete[] buf;
					break;
				}
				case SC_WriteFile:
				{
					int bufAddr = machine->ReadRegister(4);
					int NumBuf = machine->ReadRegister(5);
					int m_index =  machine->ReadRegister(6);
					int OldPos;
					int NewPos;
					char *buf = new char[NumBuf];
					// Check m_index
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					OldPos = fileSystem->openf[m_index]->GetCurrentPos();
					
					// type must equals '0'
					buf = machine->User2System(bufAddr, NumBuf);
					if (fileSystem->openf[m_index]->type  == 0 || fileSystem->openf[m_index]->type == 3)
					{	
						//printf("%d", fileSystem->openf[m_index]->type);
						if ((fileSystem->openf[m_index]->Write(buf, NumBuf)) > 0) 
						{
							// Copy data from kernel to user space
							//printf("%s",buf);
							NewPos = fileSystem->openf[m_index]->GetCurrentPos();
							machine->WriteRegister(2, NewPos - OldPos + 1);
						}
					}
					else if (fileSystem->openf[m_index]->type == 1)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// Write data to console
					if (fileSystem->openf[m_index]->type == 3)
					{
						int i = 0;
						printf("stdout mode: \n");
						while (buf[i] != 0 /*&& buf[i] != '\n'*/)
						{
							gSynchConsole->Write(buf+i, 1);
							i++;
						}
						buf[i] = '\n';
						gSynchConsole->Write(buf+i,1);
						machine->WriteRegister(2, i-1);
					}
					delete[] buf;
					break;
				}
				case SC_SeekFile:
				{
					int pos = machine->ReadRegister(4);
					int m_index = machine->ReadRegister(5);
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						printf("seek fail \n");
						machine->WriteRegister(2, -1);
						break;
					}
						pos = (pos == -1) ? fileSystem->openf[m_index]->Length() : pos;
					if (pos > fileSystem->openf[m_index]->Length() || pos < 0) {
						machine->WriteRegister(2, -1);
					} else 
					{
						fileSystem->openf[m_index]->Seek(pos);
						machine->WriteRegister(2, pos);
					}
					break;
				}
				case SC_Exec:
				{// Executable file (user space)
					int execFile = machine->ReadRegister(4);

					// change to kernel space
					char* execFile_kernel = machine->User2System(execFile, 100);
					
					int id = pTab->ExecUpdate(execFile_kernel);
					
					machine->WriteRegister(2, id);
					
					delete execFile_kernel;
					break;	
				}
				case SC_Join:
				{
					// read join process id
					int id = machine->ReadRegister(4);
					
					int ec = pTab->JoinUpdate(id);
					
					machine->WriteRegister(2, ec);
					
					break;
				}	
				case SC_Exit:
				{
					// read exitStatus
					int exitStatus = machine->ReadRegister(4);
					int ec = pTab->ExitUpdate(exitStatus) ;
					
					currentThread->FreeSpace();
					currentThread->Finish();
					
					machine->WriteRegister(2, ec);

					for (int i = 0; i < 10; i++) if (pTab->IsExist(i)) printf("\n%s\n", pTab->GetFileName(i));
					
					break;
				}
				case SC_CreateSemaphore:
				{
					// read semaphore name (kernel space)
					int name = machine->ReadRegister(4);
					
					// kernel space to user space
					char* name_kernel = machine->User2System(name, 100);
					
					// read semval from argument
					int semval = machine->ReadRegister(5);
					
					int t = semTab->Create(name_kernel, semval) ;
					
					machine->WriteRegister(2, t);
					
					delete name_kernel;
					break;
				}
				case SC_Up:
				{
					int name = machine->ReadRegister(4);

					// kernel space to user space
					char* name_kernel = machine->User2System(name, 100);
					
					int pos = semTab->getSemPos(name_kernel);
					
					if (pos == -1) {
						printf("Semaphore %s not exist\n", name_kernel);
						machine->WriteRegister(2, -1);
						delete name_kernel;
						break;
					} else {
						int t =semTab->Signal(name_kernel);
						machine->WriteRegister(2, t);
						delete name_kernel;
						break;
					}
				}
				case SC_Down:
				{
					// read  name (kernel space)
					int name = machine->ReadRegister(4);
					
					// kernel space to user space
					char* name_kernel = machine->User2System(name, 100);
					
					int pos = semTab->getSemPos(name_kernel);
					
					if (pos == -1) {
						printf("Semaphore %s not exist\n", name_kernel);
						machine->WriteRegister(2, -1);
						delete name_kernel;
						break;
					} else {
						int t = semTab->Wait(name_kernel);
						machine->WriteRegister(2, t);
						delete name_kernel;
						break;
					}
				}
			}
			// Tăng biến pc lên 1 đơn vị
			machine->registers[PrevPCReg] = machine->registers[PCReg];	// thanh ghi truoc gan bang thanh ghi hien tai
			machine->registers[PCReg] = machine->registers[NextPCReg];	// thanh ghi hein tai bang thanh ghi tiep theo
			machine->registers[NextPCReg] += 4; 				// thanh ghi tiep theo bang chinh no + cho 4 de qua dia chi ke tiep
			break;
		case PageFaultException: // No valid translation found
			printf("No valid translation found");
			ASSERT(FALSE);
			break;
		case ReadOnlyException: // Write attempted to page marked "read-only"
			printf("Write attempted to page marked \"read-only\"");
			ASSERT(FALSE);
			break;
		case BusErrorException: // Translation resulted in an invalid physical address
			printf("Translation resulted in an invalid physical address");
			ASSERT(FALSE);
			break;
		case AddressErrorException: // Unaligned reference or one that was beyond the end of the address space
			printf("Unaligned reference or one that was beyond the end of the address space");
			ASSERT(FALSE);
			break;
		case OverflowException: // Integer overflow in add or sub.
			printf("Integer overflow in add or sub.");
			ASSERT(FALSE);
			break;
		case IllegalInstrException: // Unimplemented or reserved instr.
			printf("Unimplemented or reserved instr.");
			ASSERT(FALSE);
			break;
	}

//    if ((which == SyscallException) && (type == SC_Halt)) {
//	DEBUG('a', "Shutdown, initiated by user program.\n");
//   	interrupt->Halt();
//    } else {
//	printf("Unexpected user mode exception %d %d\n", which, type);
//	ASSERT(FALSE);
//    }
}
