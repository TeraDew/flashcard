CC=gcc
CFLAGS=-c -Wall

all:	flashcard

flashcard: wordpronun.o flashcard.o
	$(CC) -o flashcard wordpronun.o flashcard.o
wordpronun.o:	wordpronun.c
	$(CC) $(CFLAGS) wordpronun.c
flashcard.o: flashcard.c
	$(CC) $(CFLAGS) flashcard.c
clean:
	del /S *.o *.exe
