#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

char	*cmd1			= "echo";
char	*arg1			= "Don't do that";
char	*path1			= "/bin/echo";

// char	*cmd1			= "sed";
// char	*arg1			= "s/And/But/";
// char	*path1			= "/usr/bin/sed";

char	*cmd2			= "awk";
char	*arg2			= "{count++} END {print count}";
char	*path2			= "/usr/bin/awk";


int	main(int argc, char **argv, char **env)
{
	int		i= 0;
	int		fd;

	char	*argv_init1[3]	= {cmd1, arg1, NULL};
	char	*argv_init2[4]	= {cmd2, arg2,  NULL};

	// while (*env)
	// {
	// 	printf("path%d: %s\n", i++, *env);
	// 	env++;
	// }

	fd = open("infile", O_RDWR);
	if (fd < 0)
	{
		printf("fd error");
		exit(1);
	}
	dup2(fd, 0);
	if (execve(path1, argv_init1, env) == -1)
		printf("Error: %s\n", strerror(errno));

	// if (execve(path2, argv_init2, env) == -1)
	// 	printf("Error: %s\n", strerror(errno));
	// if (execve(path2, argv_init2, env) == -1)
	// 	printf("Error: %s\n", strerror(errno));
}

// int	main(void)
// {
// 	int	fd;
// 	int	nb;

// 	fd = open("test", O_RDWR);
// 	if (fd < 0)
// 		printf("error");
// 	write(fd, &nb, sizeof(int));
// 	write(fd, "\nHello world", 10);
// }

/*
	Example for connect output between 2 process
*/
// int main()
// {
// 	pid_t pid;
// 	int nb = 10;
// 	int pipe_fd[2];

// 	if (pipe(pipe_fd) == -1) {
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	printf("->Before fork nb = %d\n", nb);

// 	pid = fork();

// 	if (pid < 0) {
// 		printf("fork failed");
// 		exit(EXIT_FAILURE);
// 	} else if (pid > 0) {
// 		// Code executed by the parent process
// 		close(pipe_fd[0]); // Close the reading end in the parent
// 		nb = nb - 1;
// 		write(pipe_fd[1], &nb, sizeof(nb)); // Write to the pipe
// 		close(pipe_fd[1]); // Close the writing end in the parent

// 		printf("Hello from parent\nGot child-id: %d\n", pid);
// 		printf("After fork nb = %d (parent)\n", nb);
// 	} else if (pid == 0) {

// 		int	g;

// 		g = 0;
// 		// Code executed by the child process
// 		close(pipe_fd[1]); // Close the writing end in the child
// 		read(pipe_fd[0], &g, sizeof(nb)); // Read from the pipe
// 		close(pipe_fd[0]); // Close the reading end in the child
// 		g = g - 1;
// 		printf("Hello from child!\n");
// 		printf("After fork nb = %d (child)\n", g);
// 	}

// 	return 0;
// }


// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

/*
	Example for output between 2 process (not connected
*/
// int main()
// {
// 	pid_t	pid;
// 	int		nb;

// 	nb = 10;

// 	printf("->Before fork nb = %d\n", nb);

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		printf("fork failed");
// 		exit(1);
// 	}
// 	else if (pid > 0)
// 	{
// 		printf("Hello from parent\nGot child-id: %d\n", pid);
// 		nb = nb - 1;
// 		printf("After fork nb = %d (parent)\n", nb);
// 	}
// 	else if (pid == 0)
// 	{
// 		printf("Hello from child !\n");
// 		nb = nb - 1;
// 		printf("After fork nb = %d (child)\n", nb);
// 	}
// }
