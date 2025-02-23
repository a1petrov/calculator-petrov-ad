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
	char* tmp2=tmp;
	return tmp2;
}

int isDigit(char c) {
	return (c >= '0' && c <= '9');
}

void append_in_ops(char ops[], char op) {
	int i = 0;
	for (; ops[i] != ' ';) {
		i++;
	}
	ops[i] = op;
	return;
}

void erase_frm_ops(char ops[]) {
	int j = 0;
	for (; ops[j] != ' ';) {
		j++;
	}
	ops[j-1] = ' ';
	return;
}

char get_last_f_ops(char ops[]) {
	int k = 0;
	for (; ops[k] != ' ';) {
		k++;
	}
	return	ops[k-1];
}

void getOp(int val[3], char* ops) {
	if ((val[1] == -1 && val[0] != -1) || (val[0] == -1) || ops[0]==' ') {
		return;
	}
	int num1 = -1;
	int num2 = -1;
	if (val[2] == -1) {
		num1 = val[0];
		num2 = val[1];
		val[0] = -1;
		val[1] = -1;
	}
	else {
		num1 = val[1];
		num2 = val[2];
		val[2] = -1;
		val[1] = -1;
	}
	char curOp = get_last_f_ops(ops);
	erase_frm_ops(ops);
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
	char* clc = DeleteWhiteSpaces2(str);
	int val[3] = {-1,-1,-1};
	char ops[50] = "                                                 e";
	for (int i = 0; i < my_strlen(clc);) {
		if (isDigit(clc[i])) {
			int tmp = 0;
			while (isDigit(clc[i])) {
				tmp = tmp * 10 + (clc[i] - '0');
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
			append_in_ops(ops, clc[i]);
			i++;
			continue;
		}
		else if (clc[i] == ')') {
			while (ops[0]!=' ' && get_last_f_ops(ops) != '(') {
				getOp(val, ops);
			}
			erase_frm_ops(ops);
			i++;
			continue;
		}
		else {
			while (ops[0] != ' ' && RangeOp(get_last_f_ops(ops)) >= RangeOp(clc[i])) {
				getOp(val, ops);
			}
			append_in_ops(ops,clc[i]);
			i++;
		}
	}
	while (ops[0]!=' ') {
		getOp(val, ops);
	}
	return val[0];
}

int main()
{
	char* str = (char*)malloc(1000);
	fgets(str, 1000, stdin);
	str[my_strlen(str)] = '\0';

	printf("%d", calc(str));
}

