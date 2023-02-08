#include<stdio.h>
#include<stdlib.h>
#include"parser.h"
#include"drivers.h"
#include"users.h"
#include"rides.h"
#include"stats.h"
#include"batch.h"
#include"handle.h"

void batch(char* path_csvs, char* path_input) {

        clock_t start, end;
        double batch_time, parser_time, total_time;

        Drivers drivers = init_drivers();
        Users users = init_users();
        Rides rides = init_rides();
        Stats stats = init_stats();

        printf("Data parser\n");

        start = clock();
        data_parser(path_csvs, drivers, users, rides, stats);
        end = clock();

        parser_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        //printf("\nExecuting queries\n");

        start = clock();
        parse_queries(path_input, drivers, users, rides, stats);
        end = clock();

        printf("\nParse time %.2fs\n", parser_time);

        batch_time = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Batch time %.2fs\n", batch_time);

        total_time = batch_time + parser_time;
        printf("Total time %.2fs\n", total_time);

        free_drivers(drivers);
        free_users(users); 
        free_rides(rides); 
        free_stats(stats);
}

void parse_queries(char* path_input, Drivers ds, Users us, Rides rs, Stats s) {

        FILE* fp = NULL;
        fp = fopen(path_input, "r");
        if (!fp) {
                perror("batch.c");
                return;
        }

        char* buffer = NULL;
        int counter = 0;
        size_t bufsize = 1;
        ssize_t line_size;

        while((line_size = getline(&buffer, &bufsize, fp)) >= 0){
                counter++;
                handle(buffer, ds, us, rs, s, counter, 1); // batch mode = 1
        }

        free(buffer);
        fclose(fp);
}
