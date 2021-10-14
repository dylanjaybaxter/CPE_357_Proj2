/*
main.c
Project: CPE 357 Project 2
Author: Dylan Baxter, Van Park
Description: This is the header file for a function that reads
1 word from it into dynamically allocated memory. If the end of the file is
reached, it returns NULL, and if it should return anything other than a string
of alphanumeric characters, it returns '!'
*/
#include<stdio.h>
#include<unistd.h>
#include<ctype.h>

char *rlword(FILE * file);
