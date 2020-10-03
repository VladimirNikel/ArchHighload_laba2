#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <string.h>
#include <string.h>
//#include <stddef.h>		//wchar_t

/*

cat /home/nikel/Шаблоны/bootstrap_log.txt

*/

int exec_process_with_isolation(){
	//необходимо сменить корень
	if(chroot(p, uap, retval) == 0 )	//если удалось сменить корень файловой системы - продолжаем работу
		/*
		truct proc *p;
		struct chroot_args *uap;
		int *retval;
		*/
	{

	}
	else{
		printf("\n\t\tАлярм!\tАлярм!\tАлярм!\n\t\tМне не удалось произвести смену корня файловой системы... Думай. Хы :)\n")
		return -1;						// код ошибки, что не удалось сменить корень файловой системы...
	}





}



int main(int argc, char **argv)
{
	printf("Введите относительный путь запускаемой команды (вместе с параметрами): ");
	char str[201]="";
	gets(str);

	//выполнение введеной программы
	printf("\nВывод программы\n=================================================\n");
	if(system(str) != 0)
		printf("\n=================================================\n\tПрограмма \"упала\". А я вырубаюсь.");
	else
		printf("\n=================================================\nПрограмма корректно завершилась - не паримся и не тратим ресурсы компьютера. Я спать.");

	printf("\n\n\tСпасибо, что пользуетесь этим недоDocker'ом.\nNikel (c)\n");
	return 0;
}

