#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define ValueMaxSize 20
#define DictSize 10
#define MasSize 100

typedef struct Keys {
	char key[ValueMaxSize];
};

typedef union TypeValue {
	char character[ValueMaxSize];
	int integ;
	double doubling;
};

typedef struct Values {
	int choose_type;
	TypeValue type;
};

typedef struct MyDict {
	Keys* keys = (Keys*)calloc(MasSize, sizeof(Keys));
	Values* values = (Values*)calloc(MasSize, sizeof(Values));
	int max_size = DictSize;
	int current_size = 0;
} MyDict;

enum {
	str = 0, dble = 1, integer = 2
};

enum {
	was_not_find = 0, was_find = 1
};

int main() {
	MyDict mydict;
	printf("Welcome to my humble vocabulary!\n");
	printf("Instruction: \n1. get - to get value by key \n2. put - to put key and value \n3. exite - to exite program\n");

	for (char* cmd = (char*)calloc(MasSize, sizeof(char)); strcmp("exite", cmd) != 0; scanf("%s", cmd)) {
		if (strcmp("get", cmd) == 0) {
			printf("Okey, enter the key to get the value\n");
			char* temp = (char*)calloc(MasSize, sizeof(char));
			scanf("%s", temp);
			int flag = was_not_find;
			for (int i = 0; i < mydict.current_size; i++) {
				if (strcmp(mydict.keys[i].key, temp) == 0) {
					flag = was_find;
					switch (mydict.values[i].choose_type) {
					case 0:
						printf("%s\n", mydict.values[i].type.character);
						break;

					case 1:
						printf("%lf\n", mydict.values[i].type.doubling);
						break;
					case 2:
						printf("%d\n", mydict.values[i].type.integ);
					}
				}
				if (flag == was_not_find) printf("Error, the key does not exist\n");

			}
			printf("Enter next operation:\n");
		}


		else if (strcmp("put", cmd) == 0) {
			printf("Okey, enter the key:\n");
			char* temp = (char*)calloc(MasSize, sizeof(char));
			scanf("%s", temp);
			strcpy(mydict.keys[mydict.current_size].key, temp);


			printf("Okey, enter the value:\n");
			scanf("%s", temp);
			int amount_of_points = 0;
			int flag = 2;
			for (int i = 0; i < strlen(temp); i++) {
				if (temp[i] == '.') amount_of_points++;
				if (((int)temp[i] > 57 || (int)temp[i] < 48) && (int)temp[i] != '.') flag = str;
			}

			if (amount_of_points == 1) {
				flag = dble;
			}
			else if (flag == str) {
				flag = str;
			}
			else {
				flag = integer;
			}
			switch (flag) {
			case str:
				strcpy(mydict.values[mydict.current_size].type.character, temp);
				mydict.values[mydict.current_size].choose_type = str;
				break;
			case dble:
				mydict.values[mydict.current_size].type.doubling = atof(temp);
				mydict.values[mydict.current_size].choose_type = dble;
				break;
			case integer:
				mydict.values[mydict.current_size].type.integ = atoi(temp);
				mydict.values[mydict.current_size].choose_type = integer;
				break;
			}
			printf("Operation completed successfully\n");
			printf("Enter next operation:\n");
			mydict.current_size++;
		}
	}

	return 0;
}