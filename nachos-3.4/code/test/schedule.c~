#include "syscall.h"

int
main(){
	int pingid, pongid;
	pingid = Exec("./test/ping");
	pongid = Exec("./test/pong");
	Join(pingid);
	Join(pongid);
	return 0;
}
