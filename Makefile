CC = clang
CFLAGS = -Wall -Wextra

all: menu list_tasks remove_task

menu: menu.c
	@echo "[*] Building menu.c"
	$(CC) menu.c $(CFLAGS) -o menu

list_tasks: list_tasks.c
	@echo "[*] Building list_tasks.c"
	$(CC) list_tasks.c $(CFLAGS) -o list_tasks

remove_task: remove_task.c
	@echo "[*] Building remove_task.c"
	$(CC) remove_task.c $(CFLAGS) -o remove_task


clean:
	@echo "[*] Removing binaries"
	rm -f menu list_tasks remove_task
