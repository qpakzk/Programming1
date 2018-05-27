#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define NO 5

void clear(void);
void move_cursor(int x, int y);
void start_msg(int no);
int getch(void);

int menu(void);
void exercise_pos(void);
void exercise_word(void);
void exercise_short(void);
void exercise_long(void);
void end(void);
void error(void);

int main(void) {
	int no;
	
	while(1) {
		no = menu();
	
		switch(no) {
		case 1:
			exercise_pos();
			break;
		case 2:
			exercise_word();
			break;
		case 3:
			exercise_short();
			break;
		case 4:
			exercise_long();
			break;
		case 5:
			end();
		default:
			error();
		}
	}
	
	return 0;
}

void clear(void) {
	system("clear");
}

void move_cursor(int x, int y) {
	printf("\e[%d;%df", y, x);
}

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

void start_msg(int no) {
	char *msg[NO] = {"\b\b\b", "자리 연습", "낱말 연습", "짧은 글 연습", "긴 글 연습"};
	clear();
	printf(">> 영문 타자 연습 프로그램 : %s <<\n", msg[no]);
}

int menu(void) {
	int no;
	start_msg(0);
	printf("1. 자리 연습\t");
	printf("2. 낱말 연습\n");
	printf("3. 짧은 글 연습\t");
	printf("4. 긴 글 연습\n");
	printf("5. 프로그램 종료\n\n");
	printf("번호를 선택하세요: ");
	scanf("%d", &no);
	return no;
}

void exercise_pos(void) {
	start_msg(1);
	sleep(1);
}

void exercise_word(void) {
	start_msg(2);
	sleep(1);
}

void exercise_short(void) {
	start_msg(3);
	sleep(1);
}

void exercise_long(void) {
	start_msg(4);
	sleep(1);
}

void end(void) {
	clear();
	exit(0);
}

void error(void) {
	fprintf(stderr, "잘못된 번호를 입력하였습니다.\n");
	sleep(1);
	clear();
	exit(1);
}