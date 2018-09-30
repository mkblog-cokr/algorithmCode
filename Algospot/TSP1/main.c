//MK: 완전 탐색 + 가지치기 방법을 사용한 코드
#include <stdio.h>

//MK: Visual Studio를 사용시 scanf 에러 제거함.
#pragma warning(disable:4996)

#define MAXSIZE 9
#define MIN(a,b) (a)<(b)?(a):(b)

double distance[MAXSIZE][MAXSIZE];
int inputSize;
double tmpAnswer;
int visited[MAXSIZE];

//MK: 모든 도시를 방문했는지를 판단하는 함수 
int allVisited() {
	for (int i = 0; i <= inputSize; i++) {
		if (visited[i] == 0) {
			return 0;
		}
	}
	return 1;
}

//MK: 모든 가능한 방법을 다 찾기 위한 완전탐색 코드
void findAnswer(int ptr, double dist) {
	if (allVisited() == 1) {
		tmpAnswer = MIN(tmpAnswer, dist);
		//printf("%f\n", dist);
	}
	//MK: 기존의 답 보다 긴 경우 가지치기를 하여서 더 이상 탐색을 수행하지 않음
	if (dist > tmpAnswer) {
		return;
	}
	for (int i = 1; i <= inputSize; i++) {
		if (i == ptr) {
			continue;
		}
		if (visited[i] == 0) {
			visited[i] = 1;
			findAnswer(i, dist + distance[ptr][i]);
			visited[i] = 0;
		}
	}
}

int main(void)
{
	int testCase;
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &testCase);
	for (int m = 1; m <= testCase; m++)
	{
		for (int i = 0; i < MAXSIZE; i++) {
			visited[i] = 0;
		}
		tmpAnswer = 0;
		scanf("%d", &inputSize);
		for (int i = 0; i <= inputSize; i++) {
			distance[i][0] = 0;
			distance[0][i] = 0;
		}
		for (int i = 1; i <= inputSize; i++) {
			for (int j = 1; j <= inputSize; j++) {
				scanf("%lf", &distance[i][j]);
				if ((i + 1) == j) {
					tmpAnswer += distance[i][j];
				}
			}
		}
		visited[0] = 1;
		findAnswer(0, 0);
		printf("%.10lf\n", tmpAnswer);
	}
	return 0;
}