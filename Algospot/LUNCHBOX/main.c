//MK: 분할 정복 알고리즘을 사용하여 문제를 해결함
#include <stdio.h>

//MK: Visual Studio를 사용시 scanf 에러 제거함
#pragma warning(disable: 4996) 
#define MAXSIZE 10000

#define MAX(a,b) (a)>(b)?(a):(b)

int microTime[MAXSIZE];
int eatingTIme[MAXSIZE];

int inputSize;

//MK: Quick Sort 코드
void sort(int lhs, int rhs) {
	if (lhs < rhs) {
		int i = lhs;
		int j = rhs;
		int p = lhs;
		while (i < j) {
			while (eatingTIme[i] <= eatingTIme[p] && i <= rhs) {
				i++;
			}
			while (eatingTIme[j] > eatingTIme[p]) {
				j--;
			}
			if (i < j) {
				int tmp = microTime[i];
				microTime[i] = microTime[j];
				microTime[j] = tmp;
				tmp = eatingTIme[i];
				eatingTIme[i] = eatingTIme[j];
				eatingTIme[j] = tmp;
			}
		}
		int tmp = microTime[j];
		microTime[j] = microTime[p];
		microTime[p] = tmp;
		tmp = eatingTIme[j];
		eatingTIme[j] = eatingTIme[p];
		eatingTIme[p] = tmp;
		sort(lhs, j - 1);
		sort(j + 1, rhs);
	}
}

//MK: Sort 여부를 확인 하기 위한 Print 코드
void printList() {
	for (int i = 0; i < inputSize; i++) {
		printf("(%d %d) - ", microTime[i], eatingTIme[i]);
	}
	printf("\n");
}

//MK: 탐욕법을 사용하여 문제를 해결하는 코드
int findAnswer() {
	int ret = 0;
	int sumTime = 0;
	for (int i = inputSize-1; i >= 0; i--) {
		sumTime += microTime[i];
		ret = MAX(ret, sumTime + eatingTIme[i]);
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	int testCase = 0;
	scanf("%d", &testCase);
	for (int m = 1; m <= testCase; m++) {
		scanf("%d", &inputSize);
		for (int i = 0; i < inputSize; i++) {
			scanf("%d", &microTime[i]);
		}
		for (int i = 0; i < inputSize; i++) {
			scanf("%d", &eatingTIme[i]);
		}
		sort(0, inputSize-1);
		//printList();
		printf("%d\n", findAnswer());
	}
	return 0;
}