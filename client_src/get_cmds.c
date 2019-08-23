#include "../includes/client.h"

void		process_args(char *str, int fd)
{
	char	**array;

	array = ft_strsplit(str, ' ');
	if (ft_strcmp(array[0], "quit") == 0)
		handle_exit(fd);
	if (ft_strcmp(array[0], "pwd") == 0)
		handle_pwd(fd);
	if (ft_strcmp(array[0], "ls") == 0)
		handle_ls(fd);
}

char*		read_support(char c, int buff, int n, int i)
{
	char *cmd;

	cmd = (char *)malloc(sizeof(char) * BUFFSIZE);
	while (n < buff)
	{
		if (read(STDIN_FILENO, &c, 1) > 0) 
		{
			if (c != '\n' && c != EOF)
				cmd[i] = c;
			else
				break;
		}
		else
			break;
		if (n + 1 == buff && c != '\n' && c != EOF)
		{
			buff += BUFFSIZE;
			cmd = realloc(cmd, buff);
		}
		i++;
		n++;
	}
	cmd[i] = '\0';
	return cmd;
}

int		read_input(int fd)
{
	char c;
	int buff;
	int i;
	int n;
	char *cmd;
 
	i = 0;
	n = 0;
	c = ' ';
	buff = BUFFSIZE;
	ft_putstr("\033[1;36mft_p> \033[0m");
	cmd = read_support(c, buff, i, n);
	process_args(cmd, fd);
	return (0);
}