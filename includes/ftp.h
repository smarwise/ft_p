#include "../libft/libft.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#define BACKLOG 10
#define MAXDATASIZE 100
#define BUFFSIZE 5

