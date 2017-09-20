#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "coordinador.h"




int main (int argc, char **argv)
{

	char *file = NULL;		//Archivo a leer
	int nProcesos = 0;		//N° de procesos
	int lineSize = 0;		//Tamaño de linea (cantidad de carácteres)
	char *search = NULL;	//String a buscar
	int flagShow = 0;			//Flag para mostrar o no por pantalla

	int index;
	int c;

	opterr = 0;

		while ((c = getopt (argc, argv, "i:n:c:p:d")) != -1)	//i: archivo, n: numero procesos, c: tamaño linea,
	  															//p: cadena a buscar, d: flag mostrar resultados
		switch (c)
		{
		case 'i':
			file = optarg;
			break;
		case 'n':
			nProcesos = atoi(optarg);
			break;
		case 'c':
			lineSize = atoi(optarg);
			break;
		case 'p':
			search = optarg;
			break;
		case 'd':
			flagShow = 1;
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

	for (index = optind; index < argc; index++)
		printf ("Argumento sin opción %s\n", argv[index]);
	printf("-----------------------------------\n");
	printf("COORDINADOR\n");
	printf("pid: %i\n", getpid());
	printf("archivo: %s\n", file);
	printf("numero procesos: %i\n", nProcesos);
	printf("tamaño linea: %i\n", lineSize);
	printf("cadena a buscar: %s\n", search);
	printf("mostrar resultados: %i\n", flagShow);
	printf("-----------------------------------\n");






	//int lines = countLines(file, lineSize);			//Se cuentan las lineas

	//forkComparador(file, 3, search, lineSize, 2); por ahora la funcion solo forkea un comparador...
	forkComparadores(file, search, lineSize, nProcesos);


	return 1;

}