#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Invalid syntax!\n");
		printf("%s <task>\n", argv[0]);
		return 1;
	}

	if (remove(argv[1]) == 0)
	{
		printf("Task removed successfully!\n\n");
		return 0;
	}

	else
	{
		printf("Unable to remove task!\n\n");
		return 1;
	}
}
