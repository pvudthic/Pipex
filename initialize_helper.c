/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 05:46:31 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/20 16:07:01 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_error(char *file, int err_num)
{
	ft_putstr_fd("./pipex: ", STDERR_FD);
	ft_putstr_fd(strerror(err_num), STDERR_FD);
	ft_putstr_fd(": ", STDERR_FD);
	ft_putstr_fd(file, STDERR_FD);
}

void	memory_error(t_pipe *data)
{
	perror("Memory Error: ");
	put_error_msg(errno, data);
}

static void	join_blackslash(char **env_path, t_pipe *data)
{
	int		i;
	char	*old_path;

	i = 0;
	old_path = NULL;
	while (env_path[i])
	{
		old_path = env_path[i];
		env_path[i] = ft_strjoin(env_path[i], "/");
		if (!env_path[i])
			memory_error(data);
		free(old_path);
		i++;
	}
}

static char	**split_path(char *path, t_pipe *data)
{
	char	**env_path;

	env_path = ft_split(path, ':');
	if (!env_path)
		memory_error(data);
	free(path);
	join_blackslash(env_path, data);
	return (env_path);
}

void	get_envpath(t_pipe *data)
{
	char	**envp;
	char	*path;
	int		i;

	i = 0;
	envp = data->env;
	while (envp[i] != NULL)
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			if (!path || !data->cmd_1 || !data->cmd_2)
				memory_error(data);
			data->env_path = split_path(path, data);
			return ;
		}
		i++;
	}
	perror("./pipex : Could not find environment PATH");
	clear_mem(data);
	exit(1);
}

/*
	FOR DEBUGGER
*/
// void	put_2dptr(char **ptr)
// {
// 	int	i = 0;
// 	while (ptr[i])
// 	{
// 		printf("%s\n", ptr[i]);
// 		i++;
// 	}
// }
