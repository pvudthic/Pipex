/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <pvudthic@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:36:36 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/07 05:12:05 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../pipex.h>

static void	clear_path(t_pipe *data)
{
	if (data->path_1)
		free(data->path_1);
	if (data->path_2)
		free(data->path_2);
}

static void	clear_cmd(char **cmd)
{
	char	**cmd_arg;

	cmd_arg = cmd;
	if (*cmd_arg)
	{
		while (*cmd_arg)
		{
			free(*cmd_arg);
			cmd_arg++;
		}
	}
	if (cmd)
		free(cmd);
	return ;
}

static void	close_fds(t_pipe *data)
{
	if (data->fd_infile != -1)
		close(data->fd_infile);
	if (data->fd_outfile != -1)
		close(data->fd_outfile);
	return ;
}

void	clear_mem(t_pipe *data)
{
	close_fds(data);
	clear_cmd(data->cmd_1);
	clear_cmd(data->cmd_2);
	clear_path(data);
	return ;
}

void	put_error_msg(int err_num, t_pipe *data)
{
	ft_putstr_fd("./pipex : ", STDERR_FD);
	ft_putstr_fd(strerror(err_num), STDERR_FD);
	if (data)
	{
		clear_mem(data);
		free(data);
	}
	exit(err_num);
}
