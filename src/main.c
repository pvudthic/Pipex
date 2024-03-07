/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <pvudthic@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:36:33 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/07 18:50:00 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../pipex.h>

int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];
	int		exit_code;
	t_pipe	*data;
	pid_t	pid;

	check_input(argc, env);
	data = initialize(argv, env);
	exit_code = pipex(pipe_fd, data, pid);
	clear_mem(data);
	return (exit_code);
}
