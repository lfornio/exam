
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int width, height;
char back;

int main(int argc, char **argv)
{
	FILE *res;

	if(argc == 2)
	{
		res = fopen(argv[1], "r");
		if (!res)
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return(1);
		}
		int size;
		size = fscanf(res, "%d %d %c\n", &width, &height, &back);
		printf("wid = %d\n", width);
		printf("hei = %d\n", height);
		printf("back = %c\n", back);
		printf("size = %d\n", size);
		if(size != 3)
			return (1);


		// printf("res = %p\n", res);





	fclose(res);

	}
	else
		write(1, "Error: argument\n", 16);
	return(0);
}
