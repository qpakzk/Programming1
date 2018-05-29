void exercise_word(void)
{
char word[100]{"appointment","communication","doubt","remind","phenomenon", "meanwhile", "import", "interacrion","likewise", "logger","munufacture","maximize", "diminish", "renew", "add", "physical", "content","extend","ingrident", "gaze", "regular", "minimize", "content", "transform", "intend", "expend","official", "special", "combine", "reputation", "devote", "gradual","therefore","class", "indeed", "require", "comprehend", "dabate", "anounce", "structure", "indicate", "resist","exit", "resource", "function","tough","postpone","outcome", "undergo","preceive", "circular", "hospital"," outstand", "expose", "enforce", "biography", "concern", "circumstance", "isolation", "analyze", "commute", " solve", "abstraction", "state", "common", "charater", "last","perhaps", "matter","privilege", "iron", "vanity", "fatigue", "calamity", "virtur","impulse", "hyprocrisy", "system", "monotony", "conquest", "insight", "influence", "fortitude", "compromise", "prosperity", "comfort", "symphony", "candidate", "homage", "conceit", "frustration", "impression", "identity", "eloquence","adloescence", "heritage"};
int no ;

int round = 20;
int progress = 0, current_speed = 0, max_speed = 0 , accuracy = 200;
int input;
char input_buf[MAX_BUF];
int idx = 0, i;

memset(intput_buf,0x00, MAX_BUF);
srand(time(NULL));

while(round--){
	no = random() % word;
	while(1) {
		start_msg(2) ;
		move_cursor(0,2);
		printf("진행도 %3d%%\t현재타수 : %3d\t최고타수: %3d\t 정확도 : %d%%\n", progress, current_speed, max_speed, accuracy);
		move_cursor(0, 5);
		printf("%s\n", word[no]);
	   move_cursor(idx, 7);
   input = getch();
intput_buf[idxx++] = input;

move_cursor(0,7);
intput_buf[idx] = 0,
	printf("%s", input_buf);

if (input == '\n') {
	progress += 20 ;
	memset(intput_buf,0x00, MAX_BUF);
	idx = 0;
	break;
}
}
}




