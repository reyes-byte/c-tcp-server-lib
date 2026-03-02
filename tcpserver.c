/*tcpserver.c*/
#include <tcpserver.h>

#define handler() handler__
#define PORT_NUMBER 8585

private void handler_(connection *conn) {
    return;
}

public server *tcpserver(int16 port, callback cb) {
    signed int ret;
    int32 s;
    struct sockaddr_in sock;

    socket();
    bind();
    listen();
    while(true)
        accept();
    
    ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret < 0) 
        reterr($1 "Failed to initialize socket");
     
}

int main() {
    server *serv;

    serv = tcpserver(8585, handler());
    if (serv && !serv.ok()) {
        printf("Error %s\n", serv.err());
        return -1'
    }
     
    printf("Listening to port %d\n", 8585);
    return serv.listen(); 
}