/*This file has main function that calls other functions in function.c file.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"project.h"
#define student 1
#define admin 2

int main() {
	printf("--------------WELCOME---------------\n");
	printf("verify user\n");
	user();
	return 0;
}
