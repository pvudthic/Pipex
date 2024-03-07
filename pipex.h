/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <pvudthic@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:38:07 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/07 18:50:12 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define END_WRITE 1
# define END_READ 0

typedef struct l_list
{
	int		fd_infile;
	int		fd_outfile;
	char	**env;
	char	**env_path;
	char	*path_1;
	char	*path_2;
	char	**cmd_1;
	char	**cmd_2;
}	t_pipe;

t_pipe	*initialize(char **argv, char **env);
int		pipex(int *pipe_fd, t_pipe *data, pid_t pid);
void	check_input(int argc, char **env);
void	put_error_msg(int err_num, t_pipe *data);
void	clear_mem(t_pipe *data);
void	get_envpath(t_pipe *data);
void	open_error(char *file, int err_num);
void	memory_error(t_pipe *data);

#endif
