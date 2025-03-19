#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	/* Validating correct usage */
	if (argc != 2)
	{
		printf("Invalid syntax\n");
		printf("%s <dir>\n", argv[0]);
		return 1;
	}

	/* Opening Directory */
	DIR* tasks_dir = opendir(argv[1]);
	if (tasks_dir == NULL)
	{
		perror("opendir");
		return 1;
	}

	struct dirent *entry;
	size_t amount_of_tasks = 0;

	/* Going through each entry in the opened directory */
	while ((entry = readdir(tasks_dir)) != NULL)
	{
		/* Checking if the entry is a special folder */
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		{
			/* if it is then skip it */
			continue;
		}

		amount_of_tasks += 1;
		printf("[%zu] %s\n", amount_of_tasks, entry->d_name);
	}

	if (amount_of_tasks == 0)
	{
		printf("there are no tasks!\n\n");
	}


	closedir(tasks_dir);
	return 0;
}
