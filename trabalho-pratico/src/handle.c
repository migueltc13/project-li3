#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"handle.h"
#include"stats.h"
#include"queries.h"

/* Função auxiliar que escreve o resultado no ficheiro command(n)_output.txt
na diretoria: trabalho-pratico/Resultados/
   Utilizada no modo Batch */ 
void write_output(char* result, int n) {

        char* output_path = (char*) malloc(sizeof(char) * 100);
        sprintf(output_path,"%s%d%s", "Resultados/command", n, "_output.txt");

        FILE* fp = NULL;
        int exit_code = system("mkdir -p Resultados");
        if (exit_code != 0)
                printf("mkdir -p Resultados returned %d\n", exit_code);
        fp = fopen(output_path, "w");
        if (!fp)
                perror("handle.c");
        fprintf(fp, "%s", result);
        fclose(fp); free(output_path);
}

void handle(char* buffer, Drivers drivers, Users users, Rides rides, Stats stats, int n, int mode) {
        char* aux = buffer;
        int query = atoi(strsep(&aux, " "));
        char* token_line = strsep(&aux, "\n");
        char* result = "";

        if(query == 1) {
                result = query1(token_line, drivers, users, rides, n);
        }
        else if(query == 2) {
                result = query2(token_line, stats, n);
        }
        else if(query == 3) {
                result = query3(token_line, stats, n);
        }
        else if(query == 4) {
                result = query4(token_line, stats, n);
        }
        else if(query == 5) {
                result = query5(token_line, drivers, rides, n);
        }
        else if(query == 6) {
                result = query6(token_line, rides, n);
        }
        else if(query == 7) {
                result = query7(token_line, stats, drivers, n);
        }
        else if(query == 8) {
                result = query8(token_line, rides, n);
        }
        else if(query == 9) {
                result = query9(token_line, stats, n);
        }

        if (mode == 1){
                //printf("Command %d:\t\"%d %s\"\n", n, query, token_line);
                write_output(result, n);
        }
        else printf("%s",result);
        free(result);
}
