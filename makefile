# Main makefile

main: main.c
	gcc main.c -std=c11 -Wall -Wextra -Werror -o final -lncurses
