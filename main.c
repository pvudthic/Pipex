/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:36:33 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/20 16:07:08 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];
	int		exit_code;
	t_pipe	*data;

	check_input(argc, env);
	data = initialize(argv, env);
	exit_code = pipex(pipe_fd, data);
	clear_mem(data);
	return (exit_code);
}
