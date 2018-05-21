#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "typing_exercise.h"

int main(void) {
	int number;
	bool end;
	
	end = false;	
	while(!end) {
		system("clear");
		printf(">> 영문 타자 연습 프로그램 <<\n");
		printf("1. 자리 연습\t");
		printf("2. 낱말 연습\n");
		printf("3. 짧은 글 연습\t");
		printf("4. 긴 글 연습\n");
		printf("5. 프로그램 종료\n\n");
		printf("번호를 선택하세요: ");
		scanf("%d", &number);

		switch(number) {
		case 1:
			exercise_alphabet();
			break;
		case 2:
			exercise_word();
			break;
		case 3:
			exercise_short_article();
			break;
		case 4:
			exercise_long_article();
			break;
		case 5:
			system("clear");
			end = true;
			break;
		default:
			fprintf(stderr, "\n잘못된 번호를 입력하였습니다. 다시 입력하세요.\n");
			break;
		}
	}
	return 0;
}