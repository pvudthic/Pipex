/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <pvudthic@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:36:22 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/07 18:53:51 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../pipex.h>

static void	starter_value(t_pipe *data)
{
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->cmd_1 = NULL;
	data->cmd_1 = NULL;
	data->path_1 = NULL;
	data->path_2 = NULL;
	data->env_path = NULL;
	data->env = NULL;
}

static char	*get_cmdpath(t_pipe *data, char *cmd)
{
	int		i;
	char	*path;
	char	**env_paths;

	i = 0;
	env_paths = data->env_path;
	while (env_paths[i])
	{
		path = ft_strjoin(env_paths[i], cmd);
		if (!path)
			memory_error(data);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_putstr_fd("./pipex: command not found : ", STDERR_FD);
	ft_putstr_fd(cmd, STDERR_FD);
	ft_putstr_fd("\n", STDERR_FD);
	return (0);
}

static void	get_command(t_pipe *data, char *argv2, char *argv3)
{
	data->cmd_1 = ft_split(argv2, ' ');
	data->cmd_2 = ft_split(argv3, ' ');
	if (!data->cmd_1 || !data->cmd_2)
		memory_error(data);
	get_envpath(data);
}

static void	open_files(t_pipe *data, char *infile, char *outfile)
{
	data->fd_infile = open(infile, O_RDONLY, 644);
	if (data->fd_infile == -1)
		open_error(infile, errno);
	data->fd_outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
		open_error(outfile, errno);
}

t_pipe	*initialize(char **argv, char **env)
{
	t_pipe	*data;

	data = (t_pipe *)malloc(sizeof(t_pipe));
	if (!data)
		memory_error(data);
	starter_value(data);
	data->env = env;
	open_files(data, argv[1], argv[4]);
	get_command(data, argv[2], argv[3]);
	data->path_1 = get_cmdpath(data, data->cmd_1[0]);
	data->path_2 = get_cmdpath(data, data->cmd_2[0]);
	return (data);
}
