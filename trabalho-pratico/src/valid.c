#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"valid.h"

void str_to_lower(char *str) {
	for (int i = 0; str[i]; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] - 'A' + 'a';
		}
	}
}

int is_valid_status(char* str) {
	str_to_lower(str);
	if (strcmp(str,"active") == 0 || strcmp(str,"inactive") == 0)
		return 0;
	return 1;
}

int is_valid_car_class(char* str) {
	str_to_lower(str);
	if (strcmp(str,"basic") == 0 || strcmp(str,"green") == 0 || strcmp(str,"premium") == 0)
		return 0;
	return 1;
}

int is_valid_int(const char *str) {
	int len = strlen(str);

	if (len == 0) return 1;

	for (int i=0; i<len; i++)
		if (str[i]<'0' || str[i]>'9') return 1;

	int num = atoi(str);
	if (num <= 0) return 1;

	return 0;
}

int is_valid_double(const char *str) {
	int dot_count = 0;
	int len = strlen(str);

	if (len == 0) return 1;

	for (int i=0; i<len; i++) {
		if (str[i] == '.') {
			dot_count++;
			if (dot_count > 1) return 1;
		}
		else if (str[i]<'0' || str[i]>'9') return 1;
	}
	double value = atof(str);
	if (value < 0) return 1;
	return 0;
}

int is_id(const char* s) {
	int n = strlen(s);
	if (n > 12) return 1;
	for (int i=0; i<n; i++)
		if (!(s[i]>='0' && s[i]<='9')) return 1;
	return 0;
}
