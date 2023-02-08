#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include"drivers.h"
#include"users.h"
#include"rides.h"
#include"stats.h"
#include"parser.h"
#include"batch.h"
#include"queries.h"

#define RUNS 4		// Number of queries runs
#define DIFF_MODE 1	// Set to 0 to disable (requires diff linux command)

#define MAX_FILENAME 128

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KCYN "\x1B[36m"

void test_parser(char* path_csvs, Drivers ds, Users us, Rides rs, Stats s) {
	
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	data_parser(path_csvs, ds, us, rs, s);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Parsing data time: %.2fs\n", cpu_time_used);
}

void test_query(int query, char* token_line, Drivers drivers, Users users, Rides rides, Stats stats, int n) {
	clock_t start = 0, end = 0;
	double cpu_time_used = 0, total_time = 0;

	for (int i=0; i<RUNS; i++) {
		if (query == 1){
			start = clock();
			query1(token_line, drivers, users, rides, n);
			end = clock();
		}
		else if (query == 2) {
			start = clock();
			query2(token_line, stats, n);
			end = clock();
		}
		else if (query == 3) {
			start = clock();
			query3(token_line, stats, n);
			end = clock();
		}
		else if (query == 4) {
			start = clock();
			query4(token_line, stats, n);
			end = clock();
		}
		else if (query == 5) {
			start = clock();
			query5(token_line, drivers, rides, n);
			end = clock();
		}
		else if (query == 6) {
			start = clock();
			query6(token_line, rides, n);
			end = clock();
		}
		else if (query == 7) {
			start = clock();
			query7(token_line, stats, drivers, n);
			end = clock();
		}
		else if (query == 8) {
			start = clock();
			query8(token_line, rides, n);
			end = clock();
		}
		else if (query == 9) {
			start = clock();
			query9(token_line, stats, n);
			end = clock();
		}

		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		total_time += cpu_time_used;
	}

	printf("Query %d | %.8fs | \"%d %s\"\n", query, cpu_time_used/RUNS, query, token_line);
}


int compare(FILE* fp_out, FILE* fp_res) {
	char ch1 = ' ', ch2 = ' ';
	while (ch1 != EOF && ch2 != EOF){
		ch1 = fgetc(fp_out);
		ch2 = fgetc(fp_res);
		if (ch1 != ch2) return -1;
	}
	if (ch1 == EOF && ch2 == EOF) return 0;
	return -1;

}

int count_lines(FILE* fp) {
	int count = 0;
	for (char c=getc(fp); c!=EOF; c=getc(fp))
		if (c == '\n') count++;
	return count;
}

int main(int argc, char *argv[]) {

	int diff_mode = DIFF_MODE;

	if (argc < 3){
		printf("Enter the dataset path and inputs.txt + commands_output.txt path to test.\n");
		return -1;
	}

	char* path_csvs = argv[1];
	char* path_in_out = argv[2];
	char* path_in = (char*) malloc(sizeof(char) * MAX_FILENAME);
	char* path_out = (char*) malloc(sizeof(char) * MAX_FILENAME);
	char* path_res = (char*) malloc(sizeof(char) * MAX_FILENAME);

	FILE* fp_in = NULL;
	FILE* fp_out = NULL;
	FILE* fp_res = NULL;

	Drivers drivers = init_drivers();
	Users users = init_users();
	Rides rides = init_rides();
	Stats stats = init_stats();

	// Teste de desempenho - Parsing dos dados
	printf("%s\nTeste de desempenho - Parsing dos dados%s\n", KCYN, KNRM);
	test_parser(path_csvs, drivers, users, rides, stats);

	// Teste de desempenho - Avaliação de queries
	printf("%s\nTeste de desempenho - Avaliação de queries%s\n", KCYN, KNRM);
	test_query(1, "SaCruz110",                   drivers, users, rides, stats, 100);
	test_query(2, "50",                          drivers, users, rides, stats, 200);
	test_query(3, "50",                          drivers, users, rides, stats, 300);
	test_query(4, "Braga",                       drivers, users, rides, stats, 400);
	test_query(5, "01/01/2021 01/02/2021",       drivers, users, rides, stats, 500);
	test_query(6, "Porto 01/01/2021 01/02/2021", drivers, users, rides, stats, 600);
	test_query(7, "50 Lisboa",                   drivers, users, rides, stats, 700);
	test_query(8, "M 12",                        drivers, users, rides, stats, 800);
	test_query(9, "01/01/2021 01/02/2021",       drivers, users, rides, stats, 900);

	// Teste funcional - Validação de queries
	printf("%s\nTeste funcional - Execução de queries%s\n", KCYN, KNRM);
	sprintf(path_in, "%s%s", path_in_out, "input.txt");
	parse_queries(path_in, drivers, users, rides, stats);
	printf("%s\nTeste funcional - Validação de queries%s\n", KCYN, KNRM);
	fp_in = fopen(path_in, "r");
	if (!fp_in) {
		perror("tests.c");
		return -1;
	}
	int count = count_lines(fp_in); 
	for (int i=1; i<=count; i++){
		sprintf(path_out, "%s%s%d%s", path_in_out, "command", i, "_output.txt");
		sprintf(path_res, "%s%d%s", "Resultados/command", i, "_output.txt");
		fp_out = fopen(path_out, "r");
		fp_res = fopen(path_res, "r");
		if (compare(fp_out, fp_res) == 0)
			printf("command%d_output.txt:\t%sPass ✔%s\n", i, KGRN, KNRM);
		else {
			printf("command%d_output.txt:\t%sFail ❌%s\n", i, KRED, KNRM);
			if (diff_mode == 1) {
				char* cmd = (char*) malloc(sizeof(char) * MAX_FILENAME * 2);
				sprintf(cmd, "diff %s %s", path_res, path_out);
				int exit_code = system(cmd);
				if (exit_code != 1)
					printf("%s returned %d\n", cmd, exit_code);
			}
			
		}
	}

	printf("\nmalloc_stats\n");
	malloc_stats();

	fclose(fp_in); fclose(fp_out); fclose(fp_res);
	free(path_in); free(path_out); free(path_res);
	free_drivers(drivers); free_users(users); free_rides(rides); free_stats(stats);

	printf("\nmalloc_stats after freeing memory\n");
	malloc_stats();

	return 0;
}
