#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


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


int forkComparador(char *i, int c, char *p, int n, int l)		// Función que forkea un comparador
{
	char caux[12];
	char naux[12];
	char laux[12];
	sprintf(caux, "%d", c);
	sprintf(naux, "%d", n);
	sprintf(laux, "%d", l);

	int pid = fork();
	if(pid==0) 
	{
		execl("./comparador", "./comparador","-i",i,"-c",caux,"-p",p,"-n",naux,"-l",laux, (const char *)NULL);
		//printf("exec falló\n");
		return 0;
	} else if (pid > 0) 
	{
    	//wait(NULL); // Si se usa este wait se espera a que termine cada proceso cada vez que se crea uno
	} 
	else 
	{
		// No se pudo forkear comparador
		printf("Fork falló");
		return 0;
	}
	//return getpid();	// retornar el pid del comparador creado
	return 1;
}



int forkComparadores(char *i, char *p, int n, int nProcesos)		//Función que forkea todos los comparadores
{
	int lines = countLines(i, n);		//Se cuentan las líneas del archivo
	int actualLine = 0;			//Línea actual

	if(nProcesos>lines)			// Error si el número de procesos es mayor al número de lineas
	{
		printf("Error: Número de procesos mayor que el número de líneas\n");
		return 0;
	}
	if(lines%nProcesos==0) 		//Todos los procesos trabajan el mismo número de líneas
	{
		printf("se crean %d procesos y trabajan %d líneas cada uno\n", nProcesos, lines/nProcesos);

		int creados = 0;
		int actualLine = 0;
		while(creados < nProcesos)
		{
			if (forkComparador(i, actualLine, p, n, lines/nProcesos))	//Si fork es exitoso
			{
				actualLine = actualLine + lines/nProcesos;
				creados++;
			}
			else return 0; //Falla un fork, no se pudieron forkear todos los procesos
		}
		return 1;

	}
	else			//El último proceso trabaja distinto número de líneas
	{
		printf("Los primeros %d procesos trabajan %d líneas cada uno.\n", nProcesos-1, lines/nProcesos);
		printf("El último proceso trabaja %d líneas.\n", (lines/nProcesos)+(lines%nProcesos));

		int creados = 0;
		while(creados < nProcesos-1)
		{
			if (forkComparador(i, actualLine, p, n, lines/nProcesos))	//Si fork es exitoso
			{
				actualLine = actualLine + lines/nProcesos;
				creados++;
			}
			else return 0;	//Falla un fork, No se pudieron forkear todos los procesos

		}

		if (forkComparador(i, actualLine, p, n, (lines/nProcesos)+(lines%nProcesos))) 
			{
				actualLine = actualLine + (lines/nProcesos)+(lines%nProcesos);
				creados++;
				return 1;
			}
		else return 0;		//Falla un fork, No se pudieron forkear todos los procesos
	}

	return 0; 	//No se pudieron forkear todos los procesos
}