#include "ftp.h"
#include <dirent.h>
#include <fcntl.h>
// #include <errno.h>

int   init(char *str);
void  sigchild_handler();
int   handle_error(int err);
void	ls_dir(int fd, char *client_number);
void	show_pwd(int fd, char *client_number);
void	send_cmds(char *str, int fd, char *client_number);
void handle_fail_success(int n);
void cd_dir(int fd, char *str, char *client_number);
void    put_file(int fd, char *str, char *client_number);
void    get_file(int fd, char *str, char *client_number);
void	send_result(int n, int fd);
char    *get_file_name(char *str);
void	print_cmd(char *str, char *client_number);
char    *get_ip(struct sockaddr_in *sa);
void	print_msg(char *msg, char *client_number);