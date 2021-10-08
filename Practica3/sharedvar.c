#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main ()
{
	int compartida = 48;
	int pid, time = 0;
	FILE *sharedFile = fopen ("sharedfile.txt", "w");
	fprintf (sharedFile, "%d", compartida);

	pid = fork ();
	while (compartida != 50 && time <= 150)
	{
		if (pid != 0)
		{
			if (time % 3 == 0)
			{
				FILE *sharedFile = fopen ("sharedfile.txt", "w");
				++compartida;
				printf ("padre: %d\n", compartida);
				fprintf (sharedFile, "%d",  compartida);
				fclose (sharedFile);
			}
		}
		else
		{
			if (time % 4 == 0)
			{
				FILE *sharedFile = fopen ("sharedfile.txt", "r");
				fscanf (sharedFile, "%d", &compartida);
				printf ("hijo: %d\n", compartida);
				fclose (sharedFile);
			}
		}
		time++;
		sleep (1);
	}
	return 0;
}
