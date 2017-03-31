#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define PASSWORD_LEN 20

int main(void)
{
	struct termios initsetting, newsetting;
	char pw[PASSWORD_LEN + 1];
	
	tcgetattr(fileno(stdin), &initsetting);
	newsetting = initsetting;
	newsetting.c_lflag &= ~ECHO; 
	printf("Enter password: ");
	if (tcsetattr(fileno(stdin), TCSAFLUSH, &newsetting) != 0) {
		fprintf(stderr, "Could not set attributes!\n");
	} else {
		fgets(pw, PASSWORD_LEN, stdin);
		tcsetattr(fileno(stdin), TCSANOW, &initsetting);
		fprintf(stdout, "\nYou enterned %s\n", pw);
	}
	
	return 0;
}