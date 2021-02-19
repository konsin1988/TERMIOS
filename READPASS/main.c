#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(void) 
{
	struct termios ts, ots;
	char passbuff[1024];

	// get and save current settings
	tcgetattr(STDIN_FILENO, &ts);
	ots = ts;

	//set new settings
	ts.c_lflag &= ~ECHO;
	ts.c_lflag |= ECHONL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);

	//check the settings
	tcgetattr(STDIN_FILENO, &ts);
	if( ts.c_lflag & ECHO) 
	{
		fprintf(stderr, "Error due to switch off the echo-ctl\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &ots);

		exit(1);
	}

	// get end print pass
	
	printf("Enter password: \t");
	fflush( stdout );
	fgets( passbuff, 1024, stdin );
	printf( "Read the password: %s", passbuff );
	// in the passbuf there was terminal simbol \n
	
	// reset recent settings termios
	tcsetattr(STDIN_FILENO, TCSANOW, &ots);

	exit(0);
}
