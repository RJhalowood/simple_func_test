/**
 * test cursor move
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MOVEUP(x) 		printf("\033[%dA", (x))
#define MOVEDOWN(x)		printf("\033[%dB", (x))
#define MOVERIGHT(x)	printf("\033[%dC", (x))
#define MOVELEFT(x)		printf("\033[%dD", (x))
#define MOVETO(x, y)	printf("\033[%d;%dH", (x), (y))
//move to (0,0)
#define RESET_CURSOR()	printf("\033[H")
#define HIDE_CURSOR()	printf("\033[?25l")
#define SHOW_CURSOR()	printf("\033[?25h")
#define CURSOR_END()	printf("\033[K")

#define DEF_MOVE_LEFT()	printf("\033[D")

int main(void)
{
	char cmd[] = "This commond to test backspace char!";
	int cursor_save, cursor_cur;
	int i;
	int len = strlen(cmd);
	
	printf("\033[31mThe color, %s!\033[1m\n", "hello world");
	printf("\033[31mThe color, %s!\033[4m\n", "hello world");
	printf("\033[31mThe color, %s!\033[5m\n", "hello world");
	printf("\033[31mThe color, %s!\033[7m\n", "hello world");
	printf("\033[31mThe color, %s!\033[8m\n", "hello world");
	printf("\033[47;31mThe color, %s!\033[0m\n", "hello world");
	printf("\nThis\n"
		   "\nline\n"
		   "\nused\n"
		   "\nto\n"
		   "\ntest\n"
		   "cursor!");
	
	fflush(stdout);
	sleep(2);
	MOVEUP(2);
	fflush(stdout);
	sleep(2);
	
	MOVELEFT(2);
	fflush(stdout);
	sleep(2);
	
	MOVEDOWN(2);
	fflush(stdout);
	sleep(2);
	
	MOVERIGHT(2);
	fflush(stdout);
	sleep(2);
	
	RESET_CURSOR();
	fflush(stdout);
	sleep(2);
	
	MOVETO(1,10);
	fflush(stdout);
	sleep(2);
	
	HIDE_CURSOR();
	fflush(stdout);
	sleep(2);
	
	SHOW_CURSOR();
	fflush(stdout);
	sleep(2);
	
	//删除当前光标到行尾的所有字符
	CURSOR_END();
	fflush(stdout);
	sleep(2);
	
	DEF_MOVE_LEFT();
	fflush(stdout);
	sleep(2);
	
	printf("\n");
	
	return 0;
}