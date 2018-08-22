//MK: 분할 정복 알고리즘을 사용하여 문제를 해결함
#include <stdio.h>

//MK: Visual Studio를 사용시 scanf 에러 제거함
#pragma warning(disable:4996)

#define MAXSIZE 21
#define INPUTSIZE 7

int inputList[INPUTSIZE];
int answer[INPUTSIZE];
int input[MAXSIZE][2];
int position[MAXSIZE][INPUTSIZE];

typedef unsigned long long ull;
ull numShuffle, totalShuffle;

//MK: 아래 moveTwice 연산 후 결과를 계산하는 부분
void combine() {
	int tmp[INPUTSIZE];
	for (int i = 0; i < INPUTSIZE; i++) {
		tmp[i] = answer[i];
	}
	for (int i = 0; i < INPUTSIZE; i++) {
		answer[i] = tmp[inputList[i]];
	}
}

//MK: 현재 주어진 카드 순서를 2배수 만큼 더 교환했을때 결과를 계산하는 부분
void moveTwice() {
	int tmp[INPUTSIZE];
	for (int i = 0; i < INPUTSIZE; i++) {
		tmp[i] = inputList[i];
	}
	for (int i = 0; i < INPUTSIZE; i++) {
		inputList[i] = tmp[tmp[i]];
	}
}

//MK: moveTwice로 연산을 완료 후 남은 교환 횟수 만큼 연산을 하는 부분
void moveByPtr(ull ptr) {
	int tmp[INPUTSIZE];
	for (int i = 0; i < INPUTSIZE; i++) {
		tmp[i] = answer[i];
	}
	for (int i = 0; i < INPUTSIZE; i++) {
		answer[i] = tmp[position[ptr][i]];
	}
}

//MK: 결과 계산하는 부분
void printAnswer(int testcase) {
	printf("#%d ", testcase);
	for (int i = 0; i < INPUTSIZE; i++) {
		printf("%d", answer[i]);
	}
	printf("\n");
}

int main() {
	freopen("input.txt", "r", stdin);

	int testCase;
	scanf("%d", &testCase);
	for (int m = 0; m < testCase; m++) {
		for (int i = 0; i < INPUTSIZE; i++) {
			position[0][i] = i;
			answer[i] = i;
		}
		scanf("%lld %lld", &numShuffle, &totalShuffle);
		for (int i = 1; i <= numShuffle; i++) {
			for (int j = 0; j < INPUTSIZE; j++) {
				position[i][j] = position[i - 1][j];
			}
			scanf("%d %d", &input[i][0], &input[i][1]);
			input[i][0]--;
			input[i][1]--;
			int tmp = position[i][input[i][0]];
			position[i][input[i][0]] = position[i][input[i][1]];
			position[i][input[i][1]] = tmp;
		}
		//MK: 결과를 계산하는 부분
		if (totalShuffle <= numShuffle) {
			moveByPtr(totalShuffle);
		}
		else {
			ull currentTurn = 0;
			while (1) {
				ull nextMax = totalShuffle - currentTurn;
				if (nextMax <= numShuffle) {
					moveByPtr(nextMax);
					break;
				}
				for (int i = 0; i < INPUTSIZE; i++) {
					inputList[i] = position[numShuffle][i];
				}
				ull nextTurn = numShuffle;
				//MK: 현재의 카드 순서를 가지고 2배수 만큼 교환을 하였을때 결과를 계산하는 부분
				while ((nextTurn * 2) < nextMax) {
					moveTwice();
					nextTurn *= 2;
				}
				combine();
				currentTurn += nextTurn;
			}
		}
		printAnswer(m + 1);
	}
	return 0;
}