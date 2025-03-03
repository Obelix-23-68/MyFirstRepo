#include <stdio.h>
#include <math.h>
#define MIN -200
#define MAX 200

int equation_solver (int a, int b, int c, int *root_value, int *root_value2);
int linear_equation_solver (int b, int c, int *root_value);
int read_number (int max, int min);

int main(){
	int again = 1;
	while (again){
		printf("a,b,c долны быть числами от %d до %d\n", MIN, MAX);
		printf("введите значение a:\n");
		int a;
		a = read_number(MAX, MIN);
		printf("введите значение b:\n");
		int b;
		b = read_number(MAX, MIN);
		printf("введите значение c:\n");
		int c;
		c = read_number(MAX, MIN);
		int root_value, answer;
		if (a == 0){
			answer = linear_equation_solver (b, c, &root_value);
			if (answer == 1)
				printf("1 корень со значением %d\n", root_value);
			else if (answer == 2)
				printf("нет корней\n");
			else if (answer == 3)
				printf("корень - любое число\n");
		}
		int root_value2;
		if (a != 0){
			answer = equation_solver (a, b, c, &root_value, &root_value2);
			if (answer == 1)
				printf("нет действительных корней\n");
			else if (answer == 2)
				printf("2 корня равных %d\n", root_value);
			else if (answer == 3)
				printf("2 различных корня, первый = %d, второй = %d.\n", root_value, root_value2);
		}
		while(1){
			printf("0 - выход\n"
						 "1 - попробовать снова\n");
			int error;
			error = scanf("%d", &again);
			if (error == 0 || error == EOF){
				while ((again = getchar()) != '\n');
				printf("ошибка ввода, попробуйте снова\n");
			}
			else if (again != 0 && again != 1)
				printf("ошибка ввода, попробуйте еще раз\n");
			else
				break;
		}
	}
return 0;
}

int linear_equation_solver (int b, int c, int *root_value){
	if (b != 0){
		*root_value = -c/-b;
		return 1;
	}
	else if (c != 0)
		return 2;
	else
		return 3;
}

int equation_solver (int a, int b, int c, int *root_value, int *root_value2){
	int D;
	D = (b*b)-(4*a*c);
	*root_value = ((-b) + (sqrt(D))) / (2 * a);
	*root_value2 = ((-b) - (sqrt(D))) / (2 * a);
	if(D < 0)
		return 1;
	if(D == 0)
		return 2;
	if(D > 0)
		return 3;
}

int read_number(int max, int min){
	int number, error = 0;
	while (error != 1){
		error = scanf("%d", &number);
		if (error == 0 || error == EOF){
			printf ("ошибка ввода, попробуйте снова\n");
			while ((number = getchar()) != '\n');
			continue;
		}
		if (number < min || number > max){
			printf ("не верное значение, попробуйте снова\n");
			continue;
		}
	}
return number;
}
