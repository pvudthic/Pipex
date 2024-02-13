#include "../pipex.h"

char	**cmd_argument(char *argv)
{
	char	**arg;
	//char	*cmd;
	//char	*argument;

	arg = split_arg(argv);
	if (!arg)
		exit_handler();
	while (*arg)
	{
		printf("%s\n", *arg);
		arg++;
	}
	return (arg);
}

char	*cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**origin_path;

	path = NULL;
	if (!cmd)
		exit_handler();
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
			break;
		env++;
	}
	origin_path = ft_split(*env, ':');
	if (!origin_path)
		exit_handler();
	while (*origin_path)
	{
		path = ft_strjoin(*origin_path, cmd);
		if (!path)
			exit_handler();
		if (access(path, F_OK | X_OK) == 0)
			break;
		free(path);
		origin_path++;
	}
	return (path);
}



t_pipe	*initialize(char **argv, char **env)
{
	t_pipe	*new;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (!new)
		exit_handler();
	new->infile = argv[1];
	new->cmd_1 = cmd_argument(argv[2]);
	new->cmd_2 = cmd_argument(argv[3]);
	new->outfile = argv[4];
	new->path_1 = cmd_path(ft_strjoin("/", new->cmd_1[0]), env);
	new->path_2 = cmd_path(ft_strjoin("/", new->cmd_2[0]), env);
	//debugger_data(new);
	// exit(0);
	return (new);
}

void	parent(t_pipe *data, int *pipe, char **env, int status)
{
	int	fd;

	wait(&status);
	close(pipe[1]);
	fd = open(data->outfile, O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		exit_handler();
	dup2(pipe[0], STDIN_FD);
	dup2(fd, STDOUT_FD);
	execve(data->path_2, data->cmd_2, env);
	return ;
}

/*
	Input of command will be change from
	Standard input to infile
	Output of command will be change from
	Standard output to pipe_fd
*/
void	child(t_pipe *data, int *pipe, char **env)
{
	int	fd;

	close(pipe[0]);
	fd = open(data->infile, O_RDONLY);
	if (fd < 0)
		exit_handler();
	dup2(fd, STDIN_FD);
	dup2(pipe[1], STDOUT_FD);
	execve(data->path_1, data->cmd_1, env);
	return ;
}

/*
	pipe_fd[1] = write, pipe_fd[0] = read
*/
int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];
	int		status;
	t_pipe	*data;
	pid_t	pid;

	(void) argc;
	status = 0;
	printf("recieved argv[2] : %s\n", argv[2]);
	printf("recieved argv[3] : %s\n", argv[3]);
	// if (argc != 5)
	// {
	// 	perror("infile cmd1 cmd2 outfile.");
	// 	exit(1);
	// }
	if (pipe(pipe_fd) == -1)
		exit_handler();
	data = initialize(argv, env);
	pid = fork();
	if (pid < 0)
		exit_handler();
	else if (pid == 0)
		child(data, pipe_fd, env);
	parent(data, pipe_fd, env, status);
}

/* Command for test
./pipex infile.txt cat wc outfile.txt
./pipex infile.txt cat wc inexistent.txt
./pipex infile.txt 'sed    "s/And/But/"' 'grep But' outfile.txt
./pipex infile.txt 'sed "s/And/But/"' 'awk '"'"'{count++} END
{print count}'"'"'' outfile.txt
*/
