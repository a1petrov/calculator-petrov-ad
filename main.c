#include <stdlib.h>
#include <stdio.h>

int my_strlen(char* str) {
	int i = 0;
	while (str[i] != '\n' && str[i] != '\0') {
		i++;
	}
	return i;
}

int exe(int a1,int a2,char op) {
	if (op == '+') {
		return a1 + a2;
	}
	if (op == '-') {
		return a1 - a2;
	}
	if (op == '*') {
		return a1 * a2;
	}
	if (op == '/') {
		if (a2 != 0) {
			return a1 / a2;
		}
		else {
			exit(11);
		}
	}
	return 0;
}

int RangeOp(char op) {
	switch (op) {
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	default: return 0;
	}
}

char* DeleteWhiteSpaces2(char* str) {
	char tmp[100];
	int t = 0;
	for (int i = 0; i < my_strlen(str);) {
		if (str[i] == ' ') {
			i++;
			continue;
		}
		tmp[t] = str[i];
		i++;
		t++;
	}
	tmp[t] = '\0';
	return tmp;
}
int isDigit(char c) {
	return (c >= '0' && c <= '9');
}

void getOp(int val[3], char* ops) {
	if ((val[1] == -1 && val[0] != -1) || (val[0] == -1) || my_strlen(ops)==0) {
		return;
	}
	int num1 = -1;
	int num2 = -1;
	if (val[2] == -1) {
		int num1 = val[0];
		int num2 = val[1];
		val[0] = -1;
		val[1] = -1;
	}
	else {
		int num1 = val[1];
		int num2 = val[2];
		val[2] = -1;
		val[1] = -1;
	}
	char curOp = ops[my_strlen(ops)];
	ops[my_strlen(ops)] = ' ';
	free(ops[my_strlen(ops)]);
	switch (curOp) {
	case '+':
		if (val[0] == -1) {
			val[0] = num1+num2;
		}
		else if (val[1] == -1 && val[0] != -1) {
			val[1] = num1 + num2;;
		}
		else if (val[2] == -1 && val[1] != -1 && val[0] != -1) {
			val[2] = num1 + num2;;
		}
		break;
	case '-':
		if (val[0] == -1) {
			val[0] = num1 - num2;
		}
		else if (val[1] == -1 && val[0] != -1) {
			val[1] = num1 - num2;;
		}
		else if (val[2] == -1 && val[1] != -1 && val[0] != -1) {
			val[2] = num1 - num2;;
		}
		break;
	case '*':
		if (val[0] == -1) {
			val[0] = num1 * num2;
		}
		else if (val[1] == -1 && val[0] != -1) {
			val[1] = num1 * num2;;
		}
		else if (val[2] == -1 && val[1] != -1 && val[0] != -1) {
			val[2] = num1 * num2;;
		}
		break;
	case '/':
		if (num2 == 0)
			break;
		if (val[0] == -1) {
			val[0] = num1 / num2;
		}
		else if (val[1] == -1 && val[0] != -1) {
			val[1] = num1 / num2;;
		}
		else if (val[2] == -1 && val[1] != -1 && val[0] != -1) {
			val[2] = num1 / num2;;
		}
		break;
	}
}

int calc(char* str) {
	//char* clc = DeleteWhiteSpaces2(str);
	char* clc = malloc(100);
		clc = DeleteWhiteSpaces2(str);
	int val[3] = {-1,-1,-1};
	//char* ops = "\0";
	char* ops = malloc(1);
	ops[0] = '\0';
	for (int i = 0; i < my_strlen(clc); i++) {
		if (isDigit(clc[i])) {
			int tmp = 0;
			while (isDigit(clc[i])) {
				tmp = tmp * 10 + (atoi(clc[i]));
				i++;
			}
			if (val[0]==-1) {
				val[0] = tmp;
			}
			else if (val[1] == -1 && val[0] != -1) {
				val[1] = tmp;
			}
			else if (val[2] == -1 && val[1] != -1 && val[0] != -1) {
				val[2] = tmp;
			}
			continue;
		}
		else if (clc[i]=='(') {
			ops = realloc(ops, my_strlen(ops) + 1);
			ops[my_strlen(ops) + 1] = clc[i];
			continue;
		}
		else if (clc[i] == ')') {
			while (my_strlen(ops)!=0 && ops[my_strlen(ops) + 1] != '(') {
				getOp(val, ops);
			}
			ops[my_strlen(ops)] = ' ';
			free(ops[my_strlen(ops)]);
			i++;
			continue;
		}
		else {
			while (my_strlen(ops)!=0 && RangeOp(ops[my_strlen(ops)]) >= RangeOp(clc[i])) {
				getOp(val, ops);
			}
			ops = realloc(ops, my_strlen(ops) + 1);
			ops[my_strlen(ops) + 1] = clc[i];
			i++;
		}
	}
	while (my_strlen(ops) != 0) {
		getOp(val, ops);
	}
	return val[0];
}

int main()
{
	char* str = (char*)malloc(1000);

	fgets(str, 1000, stdin);
	str[my_strlen(str)] = '\0';

	//int Valid_Val = valid_string(str);
	//if (Valid_Val == 0) {
		printf("%d", calc(str));
	//}
}

