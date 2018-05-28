#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define BACK '\b'

char buf[100];

int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void clear() {
	system("clear");
}

void cursor(int x, int y) {
	printf("\e[%d;%df", y, x);
}

int main(void) {
	int ch;
	int i, j;
	i = 0;
	while(1) {
		clear();
		cursor(0, 0);
		printf("iteration %d\n", i);
		cursor(0, 2);
		printf(">> ");
		cursor(i + 3, 2);
		ch = getch(); 
		buf[i++] = ch;	
		cursor(3, 2);
		for(j = 0; j < i; j++)
			printf("%c", buf[j]);
		if(ch == '\n')
			break;
	}
	
	return 0;
}
