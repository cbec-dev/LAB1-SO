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
void main()
{
    char *str;
    char *search;
    char *name;
    int linesToRead = 2;
    int cursor = 2;



    str =(char *) malloc(60*sizeof(char));
    search =(char *) malloc(4*sizeof(char));

    strcpy(str, "AGAAAGGCATAAATATATTAGTATTTGTGTACATCTGTTCCTTCCTGTGTGACCCTAAGT");
    strcpy(search, "AAAA");

//    int hola = findString(str, search);
//    int aux= cantidadLineas("ejemplo1.txt");


//    printf("%i\n", hola);
//    printf("%i\n", aux);


    char **lines;
    lines = linesToCompare("ejemplo1.txt", cursor, linesToRead);

    int i = 0;
    while(i<linesToRead)
    {
        int aux = findString(lines[i], "TGAG");
        printf("%s: %i \n", lines[i], aux);
        i++;
    }
}