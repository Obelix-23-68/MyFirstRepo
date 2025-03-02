// TODO: build: even though this course is primarily about basics of systems
// programming through basics of C, you should write in C but compile it as C++.
// It's possible since C++ is pretty compatible with C. And it gives you an
// advantage of writing stricter code, which C++ enforces.
//
// You can do this by using .cpp extension or passing "-x c++" to your compiler.


#include <stdio.h>
#include <math.h>

void eq(int, int, int);
// TODO:   ^    ^    ^ style: specify full names of function parameters even in
//                     forward-declared functions

int main(){
	int a, b, c, esc = 1;
        // TODO:     ^~~ it's better to write variable names with complete words
        //               you choose a name like "should_continue"
	while (esc){
		printf("a,b,c долны быть числами\n");
		printf("введите значение a:\n");
                // TODO: style: move "a" declaration =here=, immediately before
                //       the scanf (it's possible in C++, C99 and later)
		scanf("%d", &a); // TODO: bug: scanf can fail, you should check
		printf("введите значение b:\n");
		scanf("%d", &b);
		printf("введите значение c:\n");
		scanf("%d", &c);
		eq(a,b,c); // TODO: style: write a space after the comma ", "
                // TODO: style: you can make your strings multiline strings more
                //       readable by using language feature that strings that go
                //       next to each other get automatically concatenated, e.g:
                //
                //       printf("0 - exit\n"
                //              "1 - continue\n");
                //
		printf("0 - выход\nдругое число, - продолжить\n");
                // TODO: usability: it's better to choose a specific number
                //       (let's say 1 instead of saying "any other number" as it
                //        reduces the number of possible states your program can
                //        be in, which is great for debugging and deals with
                //        corner cases like number greater than INT_MAX)
		scanf("%d", &esc);
	}
return 0; // TODO: style: this return is misaligned
}

// TODO: naming: you should choose a more descriptive name for your function,
// as a rule of thumb, functions do things so their names should include a verb.
// In this particular case it's not clear what "eq" is - is it "eq"uality check
// or "equation" something or whatever - prefer full names for this reason. It
// is also not clear what it does with your equation and what kind of equations
// it expects. Rename it so that answer to all this questions is obvious.
void eq(int a, int b, int c){
	int D, x1, x2;
	if (a != 0){
		D = (b*b)-(4*a*c);
		x1 = ((-b)+(sqrt(D)))/(2*a); // TODO: style: use more spaces for
		x2 = ((-b)-(sqrt(D)))/(2*a); //       with your operators
		if(D<0)
			printf("нет действительных корней\n");
		if(D==0)
			printf("2 равных корня = %d.\n", x1);
		if(D>0) // TODO: consistency: add spaces, like "D > 0"
			printf("2 различных корня, x1 = %d, x2 = %d.\n", x1, x2);
	}
	else if (a == 0 && b != 0){ // TODO: separation of concerns: extract
		x1 = -c/-b;         //       linear case to a separate function
                // TODO: separation of concerns: your equation solver should
                //       be usable programmatically (i.e. without printing text
                //       to screen, which requires an interactive user), you
                //       should separate your "UI" part from "solver" part
		printf("1 корень, x1 = %d\n", x1);
	}
	else if (a == 0 && b == 0 && c != 0)
		printf("нет корней\n");
	else if (a == 0 && b == 0 && b == 0)
		printf("корень - любое число\n");
}
