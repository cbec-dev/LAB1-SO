#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int countLines(char *fileName, int lineSize)	//Función que cuenta las lineas del archivo de entrada
{
	FILE *file;
	file = fopen(fileName, "r");
	int count = 0;
	char line[lineSize+2];
	int countAux = 0;
	char c;
	while(feof(file)==0)
	{
		c = fgetc(file);
		if(countAux==60) 
		{
			c = fgetc(file);
			countAux = 0;
			count++;
		}
		countAux++;
	}
	fclose(file);
	return count;
}


int forkComparador(char *i, int c, char *p, int n, int l)
{
	char caux[12];
	char naux[12];
	char laux[12];
	sprintf(caux, "%d", c);
	sprintf(naux, "%d", n);
	sprintf(laux, "%d", l);

	int pid1 = fork();
	if(pid1==0) 
	{
		execl("./comparador", "./comparador","-i",i,"-c",caux,"-p",p,"-n",naux,"-l",laux, (const char *)NULL);
		printf("exec falló\n");
	}
	//return getpid();	// retornar el pid del comparador creado
	return 1;
}



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






	int lines = countLines(file, lineSize);

	printf("%i\n", lines);
	if(nProcesos>lines)
	{
		printf("Error: Número de procesos mayor que el número de líneas\n");
		return 0;
	}
	if(lines%nProcesos==0) printf("se crean %d procesos y trabajan %d líneas cada uno\n", nProcesos, lines/nProcesos);
	else
	{
		printf("Los primeros %d procesos trabajan %d líneas cada uno.\n", nProcesos-1, lines/nProcesos);
		printf("El último proceso trabaja %d líneas.\n", (lines/nProcesos)+(lines%nProcesos));
	}

	//forkComparador(file, 3, search, lineSize, 2); por ahora la funcion solo forkea un comparador...

}