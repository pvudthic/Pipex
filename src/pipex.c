/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <pvudthic@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:36:28 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/07 18:58:50 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../pipex.h>

int	parent(t_pipe *data, int *pipe_fd, int status)
{
	wait(&status);
	if (data->fd_outfile == -1 || !data->path_2)
		exit(1);
	close(pipe_fd[END_WRITE]);
	close(data->fd_infile);
	if (dup2(pipe_fd[END_READ], STDIN_FD) == -1)
		put_error_msg(errno, data);
	if (dup2(data->fd_outfile, STDOUT_FD) == -1)
		put_error_msg(errno, data);
	if (execve(data->path_2, data->cmd_2, data->env) == -1)
		put_error_msg(errno, data);
	close(data->fd_outfile);
	return (0);
}

int	child(t_pipe *data, int *pipe_fd)
{
	if (data->fd_infile == -1 || !data->path_1)
		exit(0);
	close(pipe_fd[END_READ]);
	close(data->fd_outfile);
	if (dup2(pipe_fd[END_WRITE], STDOUT_FD) == -1)
		put_error_msg(errno, data);
	if (dup2(data->fd_infile, STDIN_FD) == -1)
		put_error_msg(errno, data);
	if (execve(data->path_1, data->cmd_1, data->env) == -1)
		put_error_msg(errno, data);
	close(data->fd_infile);
	return (0);
}

int	pipex(int *pipe_fd, t_pipe *data, pid_t pid)
{
	int	status;
	int	exit_code;

	status = 0;
	if (pipe(pipe_fd) == -1)
		put_error_msg(errno, data);
	pid = fork();
	if (pid < 0)
		put_error_msg(errno, data);
	else if (pid == 0)
		exit_code = child(data, pipe_fd);
	exit_code = parent(data, pipe_fd, status);
	return (exit_code);
}
