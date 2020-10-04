#define _GNU_SOURCE
#define CLONE_NEWNS
#define CLONE_NEWPID
#define CLONE_NEWNET
#define SIGCHLD
#include <unistd.h>								//sethostname()
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>								//CLONE_NEWPID | CLONE_NEWNET | CLONE_NEWNS | SIGCHLD
#include <time.h>								//rand()
#include <sys/wait.h>							//sleep()
#include <sys/utsname.h>						//struct utsname
#include <string.h>

char str[1001]="";								//объявление переменной, в которой будет храниться команда и ее аргументы
int flags = CLONE_NEWUTS | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWNET | SIGCHLD;

void print_nodename(){
	struct utsname utsname;
	uname(&utsname);
	printf("%s\n", utsname.nodename);
}

int child_fn(){
	printf("\nПервоначальное имя узла: ");
	print_nodename();
	//генерация рандомного имени - числа
	char newNodename[20];
	sprintf(newNodename, "%9d", rand());
	strcat(newNodename, "-NedoDocker");
	sethostname(newNodename, 20);
	printf("Новое имя узла: ");
	print_nodename();

	printf("Родительский PID: %ld\n", (long)getppid());
	printf("Мой PID: %ld\n\n", (long)getpid());

	//выполнение введеной программы
	printf("\nВывод программы\n==================================================\n");
	if(system(str) != 0)											//выполнение введеной команды, и если возвращаемое значение не 0 - орём, паникуем, плачем
		printf("\n==================================================\n\tПрограмма \"упала\". Ну и я вырубаюсь.");
	else															//иначе - всё ок, идем довольными спать
		printf("\n==================================================\nПрограмма корректно завершилась. Я сделал всё что мог и пошёл довольным спать.");
	printf("\n\n%s\n%50s\n","     Спасибо, что пользуетесь этим недоDocker'ом.", "Nikel (c), 2020");
	return 0;
}

pid_t create_clone(void **stack, int kb){
	int stack_size = kb * 1024;										//сколько килобайт выделим процессу (для его стека)		по dafault: 1G
	*stack = malloc(stack_size);
	void *stack_top = (char *) *stack + stack_size;					//выделение указанного адресного пространства
	return clone(child_fn, stack_top, flags, NULL);					//создание клона процесса с изоляцией в соотвествии с флагами
}

int main(int argc, char **argv){
	srand(time(NULL));
	printf("**************************************************\nАвтор: Ниемисто Владимир [Nikel], М3О-117М-20\nНазвание программы: \"Жалкое подобие Docker'а\"\nОписание: Эта вундер-вафля умеет запускать процессы с изоляцией:\n\t1. Пространства имён\n\t2. PID'ов процессов\n\t3. Пространства имён NET\n\t4. Файловой системе\nИ позволяет ограничивать процесс по доступной ему памяти.\n**************************************************\n\n");
	printf("1. Введите относительный путь запускаемой команды (вместе с параметрами): ");
	fgets(str, 1000, stdin);		//путь запускаемой команды
	
	int kb = 0;
	while(kb <= 0){
		printf("2. Введите размер передаваемого стека (в килобайтах): ");
		scanf("%d", &kb);
	}

	printf("\n\nПо умолчанию используется изоляция по:\n\t1. Пространству имён\n\t2. PID'ам процессов\n\t3. Пространству имён NET\n\t4. Файловой системе\n");
	int result;
	printf("\nЖелаете внести изменения (отключив какую-нибудь изоляцию)? (1 - да/2 - нет): ");
	scanf("%d", &result);
	if(result == 1){
		printf("Хорошо, какую изоляцию отключить?\n\t1. Пространства имён\n\t2. PID'ам процессов\n\t3. Пространства имён NET\n\t4. Файловой системе\n\nВведите номер отключаемой изоляции: ");
		int isolation_off = 0;
		scanf("%d", &isolation_off);
		switch(isolation_off){
			case 1:
				flags = CLONE_NEWPID | CLONE_NEWNET | SIGCHLD;
				printf("\tВы отключили изоляцию пространства имён.\n");
				break;
			case 2:
				flags = CLONE_NEWUTS | CLONE_NEWNS | CLONE_NEWNET | SIGCHLD;
				printf("\tВы отключили изоляцию процессов.\n");
				break;
			case 3:
				flags = CLONE_NEWUTS | CLONE_NEWNS | CLONE_NEWPID | SIGCHLD;
				printf("\tВы отключили изоляцию сетей (имён NET).\n");
				break;
			case 4:
				flags = CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNET | SIGCHLD;
				printf("\tВы отключили изоляцию файловой системы.\n");
				break;
			default:
				printf("\tВы ввели неверные данные - я оставляю всё как было.");
				flags = CLONE_NEWUTS | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWNET | SIGCHLD;
				break;
		}
	}
	
	void *stack;
	pid_t child_pid = create_clone(&stack, kb);
	//sleep(1);
	waitpid(child_pid, NULL, 0);
	free(stack);
	return 0;
}




