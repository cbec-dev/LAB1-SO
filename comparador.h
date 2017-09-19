#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findString(char *str, char *search) 
{
    int i = 0;
    int j = 0;
    int cont = 0;
    while(i < strlen(str))
    {
        if (str[i]==search[j])
        {
            cont++;
            j++;
            if (cont == strlen(search))
            {
                //printf("Encontrado!\n");
                return 1;
                break;
            }
        }
        else
        {
            j = 0;
            cont = 0;
        }

        i++;

        //printf("%i", cont);

    }
    return 0;
    //printf("\n");
    //printf("%i", strlen(search));

}



char **linesToCompare(char* name, int cursor, int lines){
    FILE *in;
    in = fopen(name, "r");
    char linea[100];


    int cont=0;
    int aux=cursor;
    int aux2=0;


    char **result=NULL;
    result=(char **)malloc(sizeof(char*)*(lines));
    for (int i = 0; i < lines; ++i){
        result[i]=(char*)malloc(sizeof(char)*100);
    }



    while(feof(in)==0){
        fgets(linea,100,in);
        linea[strcspn(linea, "\n")] = 0;       //Para quitar el salto de línea al final de linea
        if (cont==aux){
            if (aux2<lines)
            {
                //result[aux2]=linea;
                strcpy(result[aux2], linea);
                //printf("result: %s\n", result[aux2]);
                //printf("linea: %s\n", linea);
                aux2++;
                aux++;
            }
        }
        cont++;
    } 
    fclose(in);


    //printf("%s\n", result[0]);
    //printf("%s\n", result[1]);

    return result;
}