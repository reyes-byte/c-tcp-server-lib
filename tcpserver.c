/*tcpserver.c*/
#include <tcpserver.h>

public server *globalsrv;

#define handler() &handler__

private void handler_(connection *conn) {
    return;
}

private init start() {
    return; 
}

public server *tcpserver(int16 port, callback cb) {
    signed int ret;
    int32 s, ;
    struct sockaddr_in sock;
    server *srv;
    int 16 size;
    
    if (globalsrv)
        reterr($1 "tcp server already initialised");

    ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret < 0) 
        reterr($1 "Failed to initialize socket");
    else 
        s = $4 ret;


    sock.sin_family = AF_INET;
    sock.sin_port = htops($i port);
    sock_sin_addr.s_addr = INADDR_ANY;

    ret = bind($i s, (struct sockaddr*)&sock, sizeof(struct sockaddr));
    if (ret ) {
        close ($i s);
        reterr($1 "Unable to bind to port");
    }

    ret = listen($i s, 10);
    if (ret) {
        close($i s)
        reterr($1 "Unable to lisen to port")
    }

    size = sizeof(struct s_server);
    srv = (server*)malloc($i size);
    assert(srv);
    memset($c srv, 0 , $i size);

    srv->fd = s;
    srv->port = port;
    srv->ok = &okfunction;
    srv->err = &errfunction;
    srv->cb = cb;
    srv->listen = &listen;
    srv->status = Okstatus;
    globalsrv = srv;
}

private bool okfunction() {
    if (!globsrv)
        return false;
    return (globalsrv->status == Okstatus) ?
            true :
        false;
}

private char * errfunction() {
    if (!globserv) {
        return "tcp server not initialized";
    else if (globalsrv->status != errstatus)
        return "no error";
    else
        return $c globalsrv;
    }
}

private int listenfuncion() {

    int32 s;
    signed int ret;
    struct sockaddr_in sock;
    socklen_t len;
    socklen_t *lenptr;
    int16 size;
    connection *conn;

    if (!globalsrv) 
        return -1;
    else if (globalsrv->status == errstatus) 
        return -1;

    if (!fork())
        exit(0);
     
    len = sizeof(struct sockaddr_in);
    lenptr = &len;

    while (true) {
        ret = accept($i globalsrv -> fd, (struct sockaddr *)&sock, lenptr);
        if (ret < 0) {
            sleep(2);
            continue;
        }    
        else 
            s = $4 ret;

        size = sizeof(struct s_connection);
        conn = (connection *)malloc($i size);
        if (!conn) {
            close($i s);
            sleep(2);
            continue;
    
        }
        memset($c conn, 0,$i size)
        conn -> fd = s;
        conn->host = $i inet_ntoa(sock.sin_addr);
        conn->port = $2 htons(sock.sin_port);
        if (!fork()) {
            if (conn)
                free(conn);
            continue;
        }

        conn -> cb(conn);
        exit(0);
    }

    exit(0);
    return 0;

}

int main() {
    server *serv;

    serv = tcpserver(8585, handler());
    if (serv && !serv->ok()) {
        printf("Error %s\n", serv.err());
        return -1;
    }
     
    printf("Listening to port %d\n", 8585);
    return serv->listen(); 
}