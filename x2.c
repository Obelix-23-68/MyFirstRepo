#include <stdio.h>
#include <math.h>

int main(){
	int a, b, c, D, x1, x2;
	printf("a,b,c долны быть действительными числами, где а не равно 0.\n");
	printf("введите значение a:\n");
	scanf("%d", &a);
	printf("введите значение b:\n");
	scanf("%d", &b);
	printf("введите значение c:\n");
	scanf("%d", &c);
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
