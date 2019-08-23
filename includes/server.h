#include "ftp.h"
#include <dirent.h>
#include <fcntl.h>
// #include <errno.h>

int   init(char *str);
void  sigchild_handler();
int   handle_error(int err);
void	ls_dir(int fd);
void	show_pwd(int fd);
void	send_cmds(char *str, int fd);
void handle_fail_success(int n);