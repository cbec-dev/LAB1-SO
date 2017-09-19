#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "comparador.h"

int main (int argc, char **argv)
{

	char *file = NULL;
	int cursor = 0;
	char *search = NULL;
	int lineSize = 0;
	int linesToRead = 0;
	int index;
	int c;

	opterr = 0;

		while ((c = getopt (argc, argv, "i:c:p:n:l:")) != -1)	//i: archivo, c: cursor(línea), p: cadena a buscar,
	  														//n: n° caracteres en cada línea, l: n° líneas a trabajar
		switch (c)
		{
		case 'i':
			file = optarg;
			break;
		case 'c':
			cursor = atoi(optarg);
			break;
		case 'p':
			search = optarg;
			break;
		case 'n':
			lineSize = atoi(optarg);
			break;
		case 'l':
			linesToRead = atoi(optarg);
			break;
		case '?':
		if (optopt == 'c')
			fprintf (stderr, "Opción -%c requiere un argumento.\n", optopt);
		else if (isprint (optopt))
		  	fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
		else
		  	fprintf (stderr,
           		"Opción con caracter desconocido `\\x%x'.\n",
				optopt);
			return 1;
		default:
		abort ();
		}

	printf ("Archivo: %s\nLínea inicial: %i\nString: %s\nTamaño línea: %i\nLíneas a trabajar: %i\n",
	          file, cursor, search, lineSize, linesToRead);

	for (index = optind; index < argc; index++)
		printf ("Argumento sin opción %s\n", argv[index]);


    char **lines;
    lines = linesToCompare(file, cursor, linesToRead);

    int i = 0;
    while(i<linesToRead)
    {
        int aux = findString(lines[i], search);
        if(aux==1) printf("%s: SI\n", lines[i]);
        if(aux==0) printf("%s: NO\n", lines[i]);
        i++;
    }


    return 0;
}