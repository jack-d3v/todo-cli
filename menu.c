#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>

void print_banner(void);
void print_options(void);
void clear_buffer(void);
void launch_program(const char *program_name, char *args[]);
bool is_string_empty(char *task_name, size_t task_name_len);
bool is_valid_task_name(char *task_name, size_t task_name_len);

int main(void)
{ 
	DIR* tasks_dir = opendir("tasks");
	if (tasks_dir == NULL)
	{
		printf("tasks directory does not exist!\n");
		printf("Creating tasks directory...\n\n");

		if (mkdir("tasks", 0600) != -1)
		{
			printf("tasks directory created successfully!\n");
		}

		else
		{
			printf("Unable to create tasks directory!\n");
			perror("mkdir");
		}
	}

	else
	{
		closedir(tasks_dir);
		printf("tasks directory already exists!\n\n");
	}

	bool user_wants_to_exit = false;
	int choice;
	int scanf_return;
	char task_name[256];
	char *args[4];

	while (!user_wants_to_exit)
	{
		print_banner();
		
		print_options();

		printf("Your choice: ");
		scanf_return = scanf("%d", &choice);

		while (scanf_return != 1)
		{
			clear_buffer();

			printf("Invalid input!\n\n");

			printf("Your choice: ");
			scanf_return = scanf("%d", &choice);
		}

		clear_buffer();

		switch (choice)
		{
			case 1:
				printf("Testing create task\n");
				break;

			case 2:
				printf("Listing tasks...\n\n");

				args[0] = "./list_tasks";
				args[1] = "tasks";
				args[2] = NULL;

				launch_program("./list_tasks", args);
				break;

			case 3:

				memset(task_name, '\0', 256);
				
				printf("Task name: ");
				fgets(task_name, 256, stdin);

				size_t task_name_len = strlen(task_name);
				if (task_name[task_name_len - 1] == '\n')
				{
					task_name[task_name_len - 1] = '\0';
					task_name_len -= 1;
				}

				
				while (!is_valid_task_name(task_name, task_name_len))
				{
					memset(task_name, '\0', 256);

					printf("Task name: ");
					fgets(task_name, 256, stdin);

					task_name_len = strlen(task_name);
					if (task_name[task_name_len - 1] == '\n')
					{
						task_name[task_name_len - 1] = '\0';
						task_name_len -= 1;
					}
					
				}


				char task_path[512];
				snprintf(task_path, 512, "tasks/%s", task_name);

				args[0] = "./remove_task";
				args[1] = task_path;
				args[2] = NULL;

				launch_program("./remove_task", args);
				break;


			case 99:
				user_wants_to_exit = true;
				break;

			default:
				printf("Invalid choice!\n");

		}

		printf("\n\n\n\n\n\n"); // just to make output cleaner

	}


	return 0;
}

void print_banner(void)
{
	printf("# --- --- --- #\n");
	printf("               \n");
	printf("   To Do List  \n");
	printf("               \n");
	printf("# --- --- --- #\n\n");

	return;
}

void print_options(void)
{
	printf("options:\n\n");

	printf("1. Create task\n");
	printf("2. List tasks\n");
	printf("3. Remove task\n");
	printf("99.exit\n\n");

	return;
}

void clear_buffer(void)
{
	while (getchar() != '\n');
	return;
}

void launch_program(const char *program_name, char *args[])
{
        pid_t pid = fork();

        if (pid == -1)
        {
                perror("fork");
        }

        else if (pid == 0)
        {
                /* child process */
                execv(program_name, args);
                perror("execv");
        }

        else
        {
                wait(NULL);
        }
}

bool is_string_empty(char *task_name, size_t task_name_len)
{
	for (size_t i = 0; i < task_name_len; i++)
	{
		if (task_name[i] != ' ')
		{
			return false;
		}
	}
	return true;
}

bool is_valid_task_name(char *task_name, size_t task_name_len)
{
	if (is_string_empty(task_name, task_name_len))
	{
		printf("Task name can not be empty!\n\n");
		return false;
	}

	for (size_t i = 0; i < task_name_len; i++) 
	{
		if (task_name[i] == ' ')
		{
			continue;
		}

		if (!isalnum(task_name[i])) 
		{
			printf("Task name can not contain special characters!\n\n");
			return false;
		} 
	}
	
	return true;
}
