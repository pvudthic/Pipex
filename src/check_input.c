/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvudthic <pvudthic@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 04:36:30 by pvudthic          #+#    #+#             */
/*   Updated: 2024/03/07 04:55:19 by pvudthic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../pipex.h>

static void	check_null_env(char **env)
{
	char	**tmp_env;
	int		i;

	i = 0;
	tmp_env = env;
	while (tmp_env[i])
	{
		if (tmp_env[i] == NULL)
		{
			perror("Environment Error : ");
			exit(0);
		}
		i++;
	}
	return ;
}

void	check_input(int argc, char **env)
{
	if (argc != 5)
	{
		perror("Error usage : ");
		perror("./pipex infile cmd1 cmd2 outfile");
		exit(1);
	}
	if (!env)
	{
		perror("Environment Error : ");
		exit(1);
	}
	check_null_env(env);
	return ;
}
