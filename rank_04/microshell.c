#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void exit_fatal(void)
{
	write(2, "error: fatal\n", 14);
	exit(1);
}

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int ft_cd(char **line)
{
	int result;

	if (line[1] && line[2] == NULL)
	{
		result = chdir(line[1]);
		if (result == -1)
		{
			write(2, "error: cd: cannot change directory to ", 38);
			write(2, line[1], ft_strlen(line[1]));
			write(2, "\n", 1);
		}
	}
	else
		write(2, "error: cd: bad arguments\n", 25);
	return (0);
}

int ft_linelen(char **s)
{
	int len = 0;

	while (s[len] && strcmp(s[len], ";") && strcmp(s[len], "|"))
		len++;
	return (len);
}

int main(int argc, char **argv, char **env)
{
	int i = 1;
	int j = 0;
	char **line = NULL;
	int opened_pipe = 0;
	int len = 0;
	pid_t pid;
	int savefd0 = dup(0);
	int savefd1 = dup(1);
	int pipefd[2];

	while (i < argc)
	{
		if (!(strcmp(argv[i], ";")) || !(strcmp(argv[i], "|")))
			i++;
		else
		{
			len = ft_linelen(&argv[i]);
			if (!(line = (char **)malloc(sizeof(char *) * (len + 1))))
				exit_fatal();
			line[len] = NULL;
			j = i;
			while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			{
				line[i - j] = argv[i];
				i++;
			}
			if (opened_pipe)
			{
				dup2(pipefd[0], 0);
				close(pipefd[0]);
			}
			if (argv[i] && !(strcmp(argv[i], "|")))
			{
				if (pipe(pipefd) == -1)
					exit_fatal();
				dup2(pipefd[1], 1);
				close(pipefd[1]);
			}
			if (!(strcmp(line[0], "cd")))
				ft_cd(line);
			else
			{
				pid = fork();
				if (pid == 0)
				{
					if ((execve(line[0], line, env)) == -1)
					{
						write(2, "error: cannot execute ", 22);
						write(2, line[0], ft_strlen(line[0]));
						write(2, "\n", 1);
						free(line);
						return (0);
					}
				}
				if (pid < 0)
					exit_fatal();
				waitpid(pid, &j, 0);
			}
			if (opened_pipe)
			{
				dup2(savefd0, 0);
				opened_pipe = 0;
			}
			if (argv[i] && !(strcmp(argv[i], "|")))
			{
				dup2(savefd1, 1);
				opened_pipe = 1;
			}
			free(line);
		}
	}
	return (0);
}
