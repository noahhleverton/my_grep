CC = gcc

grep: grep.c
	$(CC) grep.c -o grep -Wall -Wextra -pedantic
