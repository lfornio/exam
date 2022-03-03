#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_len(char **tab)
{

	int len = 0;
	while (tab[len] && strcmp(tab[len], ";") && strcmp(tab[len], "|"))
		len++;
	return (len);
}

void fatal(void)
{
	write(2, "error: fatal\n", 14);
	exit(1);
}

int ft_cd(char **line)
{
	int res;

	if(line[1] && line[2] == NULL)
	{
		res = chdir(line[1]);
		if(res < 0)
		{
			write(2, "error: cd: cannot change directory to ", 38);
			write(2, line[1], ft_strlen(line[1]));
			write(2, "\n", 1);
		}
	}
	else
		{
			write(2, "error: cd: bad arguments", 25);
		}

	return (0);
}

int main(int argc, char **argv, char **env)
{
	int i = 1;
	int j;
	char **line = NULL;
	int len;
	int open_pipe = 0;
	pid_t pid;
	int savefd0 = dup(0);
	int savefd1 = dup(1);
	int fd[2];

	while (i < argc)
	{
		if (argv[i] && (!strcmp(argv[i], ";") || !strcmp(argv[i], "|")))
			i++;
		else
		{
			len = ft_len(&argv[i]);
			// printf("len = %d\n", len);
			line = (char **)malloc(sizeof(char *) * (len + 1));
			if (!line)
				fatal();
			line[len] = NULL;
			j = i;
			while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			{
				line[i - j] = argv[i];
				i++;
			}
			// for(int k = 0; line[k]; k++)
			// 	printf("%s\n", line[k]);
			if (open_pipe)
			{
				dup2(fd[0], 0);
				close(fd[0]);
			}
			if (argv[i] && !strcmp(argv[i], "|"))
			{
				if (pipe(fd) < 0)
					fatal();
				dup2(fd[1], 1);
				close(fd[1]);
			}
			if (!strcmp(line[0], "cd"))
				ft_cd(line);
			else
			{
				pid = fork();
				if (pid < 0)
					fatal();
				if (pid == 0)
				{
					if ((execve(line[0], line, env)) < 0)
					{
						write(2, "error: cannot execute ", 22);
						write(2, line[0], ft_strlen(line[0]));
						write(2, "\n", 1);
						free(line);
						return (0);
					}
				}
				waitpid(pid, &j, 0);
			}
			if(open_pipe)
			{
				dup2(savefd0, 0);
				open_pipe = 0;
			}
			if (argv[i] && !strcmp(argv[i], "|"))
			{
				dup2(savefd1, 1);
				open_pipe = 1;
			}

			free(line);
		}
	}
	return (0);
}
