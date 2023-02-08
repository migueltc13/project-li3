#include<stdio.h>
#include<stdlib.h>
#include"batch.h"
#include"interact.h"

int main(int argc, char *argv[]) {

	if (argc < 3) interact();
	else batch(argv[1], argv[2]);

	return 0;
}
