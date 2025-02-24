#include <stdio.h>
#include <math.h>

void eq(int, int, int);

int main(){
	int a, b, c, esc = 1;
	while (esc){
		printf("a,b,c долны быть числами\n");
		printf("введите значение a:\n");
		scanf("%d", &a);
		printf("введите значение b:\n");
		scanf("%d", &b);
		printf("введите значение c:\n");
		scanf("%d", &c);
		eq(a,b,c);
		printf("0 - выход\nдругое число, - продолжить\n");
		scanf("%d", &esc);
	}
return 0;
}

void eq(int a, int b, int c){
	int D, x1, x2;
	if (a != 0){
		D = (b*b)-(4*a*c);
		x1 = ((-b)+(sqrt(D)))/(2*a);
		x2 = ((-b)-(sqrt(D)))/(2*a);
		if(D<0)
			printf("нет действительных корней\n");
		if(D==0)
			printf("2 равных корня = %d.\n", x1);
		if(D>0)
			printf("2 различных корня, x1 = %d, x2 = %d.\n", x1, x2);
	}
	else if (a == 0 && b != 0){
		x1 = -c/-b;
		printf("1 корень, x1 = %d\n", x1);
	}
	else if (a == 0 && b == 0 && c != 0)
		printf("нет корней\n");
	else if (a == 0 && b == 0 && b == 0)
		printf("корень - любое число\n");
}
