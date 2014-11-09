#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

char* menu[] = {
	"a - add new record",
	"b - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greet, char *choices[], FILE* in, FILE* out);

int main()
{
	int choice = 0;
	FILE* input;
	FILE* output;
	struct termios initialrsettings, newrsettings;

	//check is the output a tty
	if(!isatty(fileno(stdout))){
		fprintf(stderr, "You are not terminal, OK.\n");
		//exit(1);
	}
	
	input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if(!input || !output){
		fprintf(stderr, "Unable to open /dev/tty\n");
		exit(1);
	}
	
	tcgetattr(fileno(input), &initialrsettings);
	newrsettings = initialrsettings;
	newrsettings.c_lflag &= ~ICANON;
	newrsettings.c_lflag &= ~ECHO;
	newrsettings.c_cc[VMIN] = 1;
	newrsettings.c_cc[VTIME] = 0;
	newrsettings.c_lflag &= ~ISIG;
	if(tcsetattr(fileno(input), TCSANOW, &newrsettings) != 0){
		fprintf(stderr, "could not set attributes\n");
	}


	//
	do{
		choice = getchoice("Please select an action", menu, input, output);
		printf("You have chosen: %c\n", choice);
	}while(choice != 'q');
	tcsetattr(fileno(input), TCSANOW, &initialrsettings);
	exit(0);
}

int getchoice(char* greet, char* choices[], FILE* in, FILE* out){
	int chosen = 0;
	int selected;
	char **option;

	do{
		fprintf(out, "Choice: %s\n", greet);
		option = choices;
		while(*option){
			fprintf(out, "%s\n", *option);
			option++;
		}
	
		//ignore LF
		do{
			selected = fgetc(in);
		}while(selected == '\n' || selected == '\r');

		option = choices;
		while(*option){
			if(selected == *option[0]){
				chosen = 1;
				break;	
			}
			option++;
		}
		if(!chosen){
			fprintf(out, "Incorrect choice, select again\n");
		}
	}while(!chosen);

	return selected;
}
