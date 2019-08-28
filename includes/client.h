#include "ftp.h"
#include <fcntl.h>

void		handle_exit(int fd);
void		handle_pwd(int fd);
int   handle_error(int errno);
int   read_input(int fd);
void		handle_ls(int fd);
void handle_fail_success(int n);
void	handle_cd(int fd, char *str);
void    handle_put(int fd, char *str);
void    handle_get(int fd, char *str);