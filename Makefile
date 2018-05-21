CC=gcc
DEPS = typing_exercise.h
OBJ = typing_exercise.o typing_alphabet.o typing_word.o typing_short_article.o typing_long_article.o

program: $(OBJ)
	gcc -o $@ $^
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

clean:
	rm -rf *.o program