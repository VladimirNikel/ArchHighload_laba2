#define _GNU_SOURCE
#include <unistd.h>								//sethostname()
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>								//CLONE_NEWPID | CLONE_NEWNET | CLONE_NEWNS | SIGCHLD
//#include <sys/mount.h>
#include <time.h>								//rand()
#include <sys/wait.h>							//sleep()
#include <sys/utsname.h>						//struct utsname

static char child_stack[1048576];
char str[201]="";

void print_nodename(){
	struct utsname utsname;
	uname(&utsname);
	printf("%s\n", utsname.nodename);
}

int child_fn(){
	printf("\nПервоначальное имя узла:");
	print_nodename();
	//printf("Имя будет изменено в новом пространстве имён!\n");
	//генерация рандомного имени - числа
	char newNodename[10];
	sprintf(newNodename, "%d", rand());
	sethostname(newNodename, 11);				//NedoDocker 11

	printf("Новое имя узла: ");
	print_nodename();

	//полезная нагрузка
	printf("Родительский PID: %ld\n", (long)getppid());
	printf("Мой PID: %ld\n\n", (long)getpid());


	//выполнение введеной программы
	printf("\nВывод программы\n=================================================\n");
	if(system(str) != 0)
		printf("\n=================================================\n\tПрограмма \"упала\". А я вырубаюсь.");
	else
		printf("\n=================================================\nПрограмма корректно завершилась - не паримся и не тратим ресурсы компьютера. Я спать.");
	printf("\n\n\tСпасибо, что пользуетесь этим недоDocker'ом.\nNikel (c)\n");
	return 0;
}

int main(int argc, char **argv){
	srand(time(NULL));
	printf("Введите относительный путь запускаемой команды (вместе с параметрами): ");
	gets(str);
	pid_t child_pid = clone(child_fn, child_stack+1048576, CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWNET | SIGCHLD, NULL);
	sleep(1);
	waitpid(child_pid, NULL, 0);
	return 0;
}

