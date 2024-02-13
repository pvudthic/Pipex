#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

typedef	struct	l_list
{
	char	*infile;
	char	*outfile;
	char	*path_1;
	char	*path_2;
	char	**cmd_1;
	char	**cmd_2;
	char	*err_msg;
	int		err_num;
}	t_pipe;

char	**split_arg(const char *s);
void	debugger_data(t_pipe *new);
void	exit_handler(void);

#endif
