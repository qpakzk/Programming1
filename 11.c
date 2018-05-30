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
				right++;
				pro+=5;
				}
			else
				err++;
		}

		else { 					     // 대문자 일때
			char d = rand()%26+65;   // 대문자 랜덤
			printf("%c\n", d);
			input = getch();
			if ( input == d ){
				right++;
				pro+=5;
				}
			else
				err++;
		} 
	}


	start_msg(1);
	move_cursor(0,2);
	printf("진행도 : %3d%%\t오타수 : %2d\t정확도 : %d%%\n", pro, err, acc);
	move_cursor(0 ,5);
	printf("종료하려면 enter를 누르세요.");
	while(getch() != '\n');
}
