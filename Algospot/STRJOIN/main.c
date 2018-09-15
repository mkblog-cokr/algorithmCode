//MK: 탐욕방법을 사용한 문제 해결 코드
#include <stdio.h>

//MK: Visual Studio를 사용시 scanf 에러 제거함
#pragma warning(disable: 4996) 

#define MAXSIZE 101

int inputList[MAXSIZE];

int treeSize;

//MK: Priority Queue (Tree)에 추가하는 부분
void insertIntoTree(int input) {
	inputList[treeSize] = input;
	int ptr = treeSize;
	treeSize++;
	while (ptr != 0) {
		int parent = (ptr - 1) / 2;
		if (inputList[parent] > inputList[ptr]) {
			int tmp = inputList[parent];
			inputList[parent] = inputList[ptr];
			inputList[ptr] = tmp;
			ptr = parent;
		}
		else {
			break;
		}
	}
}

//MK: Priority Queue에서 가장 작은 수를 Return하는 함수
int popFromTree() {
	treeSize--;
	int ret = inputList[0];
	inputList[0] = inputList[treeSize];
	inputList[treeSize] = 0;
	int ptr = 0;
	while (ptr < treeSize) {
		int lhs = ptr * 2 + 1;
		int rhs = ptr * 2 + 2;
		if ((inputList[lhs] < inputList[ptr] && lhs < treeSize) && (inputList[rhs] < inputList[ptr] && rhs < treeSize)) {
			if (inputList[lhs] < inputList[rhs] ) {
				int tmp = inputList[lhs];
				inputList[lhs] = inputList[ptr];
				inputList[ptr] = tmp;
				ptr = lhs;
			}
			else{
				int tmp = inputList[rhs];
				inputList[rhs] = inputList[ptr];
				inputList[ptr] = tmp;
				ptr = rhs;
			}
		}
		else if (inputList[lhs] < inputList[ptr] && lhs < treeSize) {
			int tmp = inputList[lhs];
			inputList[lhs] = inputList[ptr];
			inputList[ptr] = tmp;
			ptr = lhs;
		}
		else if (inputList[rhs] < inputList[ptr] && rhs < treeSize) {
			int tmp = inputList[rhs];
			inputList[rhs] = inputList[ptr];
			inputList[ptr] = tmp;
			ptr = rhs;
		}
		else {
			break;
		}
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	int testCase = 0;
	scanf("%d", &testCase);
	for (int m = 0; m < testCase; m++) {
		treeSize = 0;
		int tmpSize;
		scanf("%d", &tmpSize);
		for (int i = 0; i < tmpSize; i++) {
			int tmp;
			scanf("%d", &tmp);
			insertIntoTree(tmp);
		}
		int result = 0;
		//MK: 탐욕법으로 문제를 해결하는 부분 (함수를 만들기에 너무 짧음)
		while (treeSize > 1) {
				int tmp0 = popFromTree();
				int tmp1 = popFromTree();
				result += (tmp0 + tmp1);
				insertIntoTree((tmp0 + tmp1));
		}
		printf("%d\n", result);
	}
	return 0;
}