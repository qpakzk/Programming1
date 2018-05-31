#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <string.h>

#define NO 5
#define SEN 30
#define MAX_BUF 100000

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
	move_cursor(0, 0);
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
	getchar();
	return no;
}

 void exercise_pos(void){

   start_msg(1);
     int right = 0; //정확히 입력한 단어 개수
     int pro = 0, err = 0, acc = 0; //pro:정확도 err:오타수 acc:정확도
     int input, char_size;
     srand(time(NULL));


    for ( right; right < 20; ) {
         move_cursor(0,2);
         printf("진행도 : %3d%%\t오타수 : %3d\t정확도 : %d%%\n", pro, err, acc);
         move_cursor(0,5);

        char_size = rand()%2;         // 대문자인지 소문자인지 rand함수로 결정

        if (char_size == 0){         // 소문자일때
             char c = rand()%26+97;   // 소문자 랜덤
             printf("%c\n", c);
             input = getch();
             if ( input == c ){
                 ++right;
                 pro+=5;
				 acc = right*100/(right+err);    
			 }
			 else if ( input == ESC)
				 return;
             else {
                ++err;
			 	acc = right*100/(right+err);
			 }
         }

        else {                       // 대문자 일때
             char d = rand()%26+65;   // 대문자 랜덤
             printf("%c\n", d);
             input = getch();
             if ( input == d ){
                 ++right;
                pro+=5;
				acc = right*100/(right+err);
                 }
			 else if (input == ESC)
				 return;
             else {
				 ++err;
				 acc = right*100/(right+err) ;
			 }
		}
	}
	start_msg(1);
	move_cursor(0,2);
	printf("진행도 : %3d%%\t오타수 : %2d\t정확도 : %d%%\n", pro, err, acc);
	move_cursor(0 ,5);
	printf("종료하려면 enter를 누르세요.");
	while(getch() != '\n');
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
