#include "../pipex.h"

void	exit_handler(void)
{
	exit(1);
}

void	debugger_data(t_pipe *new)
{
	int	i;

	i = 1;
	printf("cmd_1: %s\n", new->cmd_1[0]);
	if (new->cmd_1[1])
	{
		printf("Got argument: ");
		while (new->cmd_1[i])
		{
			printf("%s/", new->cmd_1[i]);
			i++;
		}
		printf("\n");
	}

	printf("\ncmd_2: %s\n", new->cmd_2[0]);
	i = 1;
	if (new->cmd_2[1])
	{
		printf("Got argument: ");
		while (new->cmd_2[i])
		{
			printf("%s ", new->cmd_2[i]);
			i++;
		}
		printf("\n");
	}
	printf("\npath_1: %s\n", new->path_1);
	printf("\npath_2: %s\n", new->path_2);
}
