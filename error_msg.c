/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:36:36 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/20 16:15:04 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clear_path(t_pipe *data)
{
	int	i;

	i = 0;
	if (data->path_1)
		free(data->path_1);
	if (data->path_2)
		free(data->path_2);
	if (data->env_path)
	{
		while (data->env_path[i])
		{
			free(data->env_path[i]);
			i++;
		}
		free(data->env_path);
	}
}

static void	clear_cmd(char **cmd)
{
	int		i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			cmd[i] = NULL;
			i++;
		}
		free(cmd);
	}
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
	if (data)
	{
		close_fds(data);
		clear_cmd(data->cmd_1);
		clear_cmd(data->cmd_2);
		clear_path(data);
		free(data);
		data = NULL;
		return ;
	}
}

void	put_error_msg(int err_num, t_pipe *data)
{
	ft_putstr_fd("./pipex : ", STDERR_FD);
	ft_putstr_fd(strerror(err_num), STDERR_FD);
	if (data)
		clear_mem(data);
	exit(err_num);
}
