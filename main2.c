#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

static char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL	,
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out)
{
	int chosen = 0;
	int selected;
	char **option;
	
	do {
		fprintf(out, "%s\n", greet);
		option = choices;
		while (*option) {
			fprintf(out, "%s\n", *option);
			option++;
		}
		
		do {
			selected = fgetc(in);
		} while (selected == '\n' || selected == '\r');
		
		option = choices;
		while (*option) {
			if (selected == *option[0]) {
				chosen = 1;
				break;
			}
			
			option++;
		}
		
		if (!chosen) {
			fprintf(out, "Incorrect choice, select again\n");
		}
	} while (!chosen);
	
	return selected;
}

int main(void)
{
	int choice = 0;
	FILE *input, *output;
	struct termios initsetting, newsetting;
	
	if (!isatty(fileno(stdout))) {
		fprintf(stderr, "You are not at a terminal!\n");
	}
	
	input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if (!input || !output) {
		fprintf(stderr, "Unable to open /dev/tty\n");
	}
	
	tcgetattr(fileno(input), &initsetting);
	newsetting = initsetting;
	newsetting.c_lflag &= ~(ICANON | ECHO | ISIG);
	newsetting.c_cc[VMIN] = 1;
	newsetting.c_cc[VTIME] = 0;
	if (tcsetattr(fileno(input), TCSANOW, &newsetting) != 0) {
		fprintf(stderr, "Could not set attribute!\n");
	}
	
	do {
		choice = getchoice("Please select an action: ", menu, input,output);
		printf("You have chosen: %c\n", choice);
	} while (choice != 'q');
	tcsetattr(fileno(input), TCSANOW, &initsetting);
	
	return 0;
}
