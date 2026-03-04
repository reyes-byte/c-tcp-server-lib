#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned char int8;
typedef unsigned short int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef void (*callback)(connection*);



//public private keywords
#define public __attribute__((visibility("default")))
#define private __attribute__((visibility("hidden"))) static


#define $c (char *)
#define $i (int)
#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)

#define reterr(x) do { \
    server *_srv; \
    int16 _sz, _len;\
    \
    _sz = sizeof(struct s_server) \
        + $2 (_len = strlen($c (x))) \
        + 1; \
    _srv = (server *)malloc($i _sz); \
    assert(_srv); \
    memset($c _srv, 0, $i _sz); \ 
    _srv.status = Errstatus; \
    memcpy($c _srv.errmsg, $c(x), ); \
    \
    return _srv;\
} while(false)

enum {
    errstatus,
    Okstatus
};


struct s_connection {
    int32 fd;
    int8 host[16];
    int16 port; 
}; 

typedef struct s_connection connection;

struct s_server {
    int32 fd; //socket fd
    int8 status:1; //allocate 1 bit
    int8 errmsg[];
}; 
typedef struct s_server server;

int main(void);
public server *tcpserver(int16,callback);

private temp(connection*);