#include <stdio.h>

void readFile(const char* filename);
void writeFile(const char*filename, nodo root);

void readFile (const char* filename)
{
	FILE* file = fopen (filename, "r");
	int i = 0;

	fscanf (file, "%d", &i);
	while (!feof (file))
	{
		insertarUltimo (i);	
		fscanf (file, "%d", &i);
	}

	fclose (file);
}

void writeFile (const char* filename, nodo root)
{
	FILE* file = fopen (filename, "w");
	nodo aux = root;
	int i;

	if (file != NULL)
	{
		while (aux != NULL && aux->sig != root)
		{
			i = aux->info;
			fprintf (file, "%d\n", i);
			aux = aux->sig;
		}
		if (aux != NULL)
		{
			i = aux->info;
			fprintf (file, "%d\n", i);
		}
	}
	fclose (file);
}
