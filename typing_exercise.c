#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define NO 5
#define WORD_SIZE 100
#define SHORT_SIZE 30
#define LONG_SIZE 4
#define MAX_SIZE 100000

#define ESC 0x1B
#define DEL 0x7F

#define WORD_ROUND 20
#define SHORT_ROUND 5

void clear(void);
void move_cursor(int x, int y);
void start_msg(int no);
int getch(void);

int menu(void);
int cal_accuracy(char *str1, char *str2, int last);
int cal_speed(char *input, char *sen, int idx, struct timeval *start, struct timeval *end);

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

	char *word[WORD_SIZE] = {
		"appointment", "communication", "doubt", "remind", "phenomenon", 
		"meanwhile", "import", "interacrion", "likewise", "logger",
		"munufacture", "maximize", "diminish", "renew", "physical", 
		"content", "extend", "ingredient", "gaze", "regular", 
		"minimize", "content", "transform", "intend", "expend",
		"official", "special", "combine", "reputation", "devote", 
		"gradual", "therefore", "class", "indeed", "require", 
		"comprehend", "debate", "announce", "structure", "indicate", 
		"resist", "exit", "resource", "function", "tough",
		"postpone", "outcome", "undergo", "preceive", "circular", 
		"hospital", "outstand", "expose", "enforce", "biography",
		"concern", "circumstance", "isolation", "analyze", "commute",
		"solve", "abstraction", "state", "common", "character", 
		"last", "perhaps", "matter", "privilege", "iron",
		"vanity", "fatigue", "calamity", "virtue", "impulse",
		"hyprocrisy", "system", "monotony", "conquest", "insight",
		"influence", "fortitude", "compromise", "prosperity", "comfort",
		"symphony", "candidate", "homage", "conceit", "frustration",
		"impression", "identity", "eloquence","adolescence", "heritage",
		 "add", "vivid", "simultaneous", "acquaintance", "ready"
	};
	int no;
	int match = 0;
	int progress = 0, typos = 0, accuracy = 0;
	int input;
	char input_buf[MAX_SIZE];
	int idx = 0, i, j;
	int selected_word[WORD_ROUND];
	bool duplicate;
	srand(time(NULL));

	for(i = 0; i < WORD_ROUND; i++) {
		duplicate = false;
		while(1) {
			no = random() % WORD_SIZE;
			for(j = 0; j < i; j++) {
				if(selected_word[j] == no) {
					duplicate = true;
					break;
				}
				else
					duplicate = false;
			}
			if(!duplicate)
				break;
		}
		selected_word[i] = no;

		memset(input_buf, 0x00, MAX_SIZE);
		
		start_msg(2);
		move_cursor(0,2);
		printf("진행도 : %3d%%\t오타수 : %3d\t 정확도 : %d%%\n", progress, typos, accuracy);
		move_cursor(0, 5);
		printf("%s", word[no]);

		move_cursor(0,7);
		while (1) {
			input = getchar();
			if(input == '\n') {
				input_buf[idx] = 0;
				if(!strcmp("###", input_buf))
					return;
				if(strcmp(word[no], input_buf))
					typos++;
				else
					match++;

				accuracy = match * 100 / (typos + match);
				progress += 5;
				idx = 0;
				break;
			}
			else
				input_buf[idx++] = (char) input;
		}
		printf("round = %d\n", i);
	}

	if(i == WORD_ROUND) {
		start_msg(2);
		move_cursor(0,2);
		printf("진행도 : %3d%%\t오타수 : %3d\t 정확도 : %3d%%\n", progress, typos, accuracy);
		move_cursor(0,7);
	}
	while(getch() != '\n');
}

int cal_accuracy(char *input, char *sen, int last) {
	int correct_count = 0;
	int len = strlen(sen);
	int result;
	int i;
	if(last == 0)
		return 100;

	for(i = 0; i < last;  i++) {
		if(input[i] == sen[i])
			correct_count++;
	}

	result = last <= len ? correct_count * 100 / last : correct_count * 100 / len;
	return result;
}

int cal_speed(char *input, char *sen, int idx, struct timeval *start, struct timeval *end) {
	long long seconds = end->tv_sec - start->tv_sec;
	int speed;
	int i;
	int count_correct = 0;
	int last;
	int sen_len = strlen(sen);
	if(seconds == 0)
		return 0;
	
	last = idx > sen_len ? sen_len : idx;
	for(i = 0; i < last; i++) {
		if(input[i] == sen[i])
			count_correct++;
	}
	speed = (count_correct * 60) / seconds;
	return speed;	
}

void exercise_short(void) {
	//reference : https://www.fluentu.com/blog/english/ko/%EC%A7%80%EA%B8%88-%EB%B0%94%EB%A1%9C-%EB%B0%B0%EC%9B%8C%EC%95%BC-%ED%95%A0-%EA%B0%80%EC%9E%A5-%EC%9C%A0%EC%9A%A9%ED%95%9C-%EC%98%81%EC%96%B4-%EC%86%8D%EB%8B%B4-50-%EA%B0%80%EC%A7%80/
	char *sentence[SHORT_SIZE] = {
		"The grass is always greener on the other side of the fence.",//0
		"Don't judge a book by its cover.",//1
		"Strike while the iron is hot.",//2
		"Too many cooks spoil the broth.",//3
		"You can't have your cake and eat it too.",//4
		"Many hands make light work.",//5
		"When in Rome, do as the Romans do.",//6
		"Don't cross the bridge until you come to it.",//7
		"Honesty is the best policy.",//8
		"Practice makes perfect.",//9
		"Where there's a will, there's a way.",//10
		"Look before you leap.",//11
		"Beggars can't be choosers.",//12
		"Don't make a mountain out of an anthill.",//13
		"An apple a day keeps the doctor away.",//14
		"The early bird catches the worm.",//15
		"Better late than never.",//16
		"The cat is out of the bag.",//17
		"Two wrongs don't make a right.",//18
		"Always put your best foot forward.",//19
		"Rome wasn't built in a day.",//20
		"It's better to be safe than sorry.",//21
		"Don't bite the hand that feeds you.",//22
		"The squeaky wheel gets the grease.",//23
		"Don't bite off more than you can chew.",//24
		"You made your bed, now you have to lie in it.",//25
		"Actions speak louder than words.",//26
		"It takes two to tango.",//27
		"Don't count your chickens before they hatch.",//28
		"It's no use crying over spilled milk."//29
	};
	int no;
	int progress = 0, current_speed = 0, max_speed = 0, accuracy = 100;
	int input;
	char input_buf[MAX_SIZE];
	int idx = 0, i, j;
	bool duplicate;
	int selected_short[SHORT_ROUND];
	int round = SHORT_ROUND;
	bool is_first = true;

	struct timeval start, end;
	srand(time(NULL));

	for(i = 0; i < SHORT_ROUND; i++) {
		duplicate = false;
		while(1) {
			no = random() % SHORT_SIZE;
			for(j = 0; j < i; j++) {
				if(selected_short[j] == no) {
					duplicate = true;
					break;
				}
				else
					duplicate = false;
			}
			if(!duplicate)
				break;
		}
		selected_short[i] = no;
		memset(input_buf, 0x00, MAX_SIZE);
		while(1) {
			start_msg(3);
			move_cursor(0, 2);
			printf("진행도 : %3d%%\t현재타수 : %3d\t최고타수 : %3d\t정확도 : %d%%\n", progress, current_speed, max_speed, accuracy);
			move_cursor(0, 5);
			printf("%s", sentence[no]);

			move_cursor(idx, 7);
			input = getch();
			if(input == ESC) 
				return;
			else if(input == DEL) {
				if(idx <= 0) {
					continue;
				}
				idx--;
				accuracy = cal_accuracy(input_buf, sentence[no], idx);
			}
			else if(input == '\n') {
				progress += 20;
				memset(input_buf, 0x00, MAX_SIZE);
				idx = 0;
				current_speed = 0;
				accuracy = 100;
				is_first = true;
				break;
			}
			else {
				if(is_first) {
 				 	gettimeofday(&start, NULL);
					is_first = false;
				}
				else
					gettimeofday(&end, NULL);
				input_buf[idx++] = input;
				accuracy = cal_accuracy(input_buf, sentence[no], idx);
				current_speed = cal_speed(input_buf, sentence[no], idx, &start, &end);
				max_speed = max_speed < current_speed ? current_speed : max_speed;
			}
			
			move_cursor(0, 7);
			input_buf[idx] = 0;
			printf("%s", input_buf);
		}	
	}

	start_msg(3);
	move_cursor(0, 2);
	printf("진행도 : %3d%%\t현재타수 : %3d\t최고타수 : %3d\t정확도 : %d%%\n", progress, current_speed, max_speed, accuracy);
	move_cursor(0, 7);

	while(getch() != ESC);
}

void exercise_long(void) {
	start_msg(4);
	char *articles[LONG_SIZE] = {
		
	};
	
	while(getch() != ESC);
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
