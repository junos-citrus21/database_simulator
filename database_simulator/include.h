#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum logic { FALSE, TRUE, SAME = 0 };
enum mode { ADD, INSERT, EDIT, DELETE };
enum score { ZERO, ONE, TWO, THREE, FOUR, ASCII_ZERO = 48, HUNDRED = 100 };
enum string_length { MAJOR = 3, SCORE = 4, STUDENT_NUMBER = 9, NAME = 11 };

typedef struct _data {
	int delete;
	int mode;
	char number[STUDENT_NUMBER];
	char name[NAME];
	char major[MAJOR];
	char grade;
	char score[SCORE];
} data_t;

int create_master_file(void);
int create_transaction_file(void);
int view_master_file(void);
int view_transaction_file(void);
int renew(void);
int view_master_error(void);
int view_transaction_error(void);