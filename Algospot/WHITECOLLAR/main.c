//MK: WhiteCollar 문제 해결 코드
#include <stdio.h>
#include <string.h>
 
//MK: Visual Studio를 사용시 scanf 에러 제거함.
#pragma warning(disable:4996)
 
#define MAXCITY 1001
#define MAXROAD 50001
#define MAXBIT 33
 
int allRoads[MAXROAD][2];
 
typedef struct cityInfo {
	int counter;
	int visitedInfo[MAXBIT];
}node;
 
node list[MAXCITY];
int numCity;
int numRoad;
 
int stack[MAXCITY];
int stackPtr;
int stackEnd;
 
int answer[MAXCITY];
 
//MK: Stack 초기화 및 시작 Node를 추가하는 부분
void init() {
	stackPtr = 0;
	stackEnd = 0;
	for (int i = 1; i <= numCity; i++) {
		answer[i] = 0;
		list[i].counter = 0;
		memset(list[i].visitedInfo, 0, sizeof(int) * MAXBIT);
		if (i == 1) {
			list[i].counter = 1;
			list[i].visitedInfo[0] = 1 << 1;
		}
	}
	stack[stackEnd] = 1;
	stackEnd++;
}
 
//MK: 단순히 Node를 복사하는 부분
void copyNode(int srcPtr, int desPtr) {
	node *src = &list[srcPtr];
	node *des = &list[desPtr];
	des->counter = src->counter;
	for (int i = 0; i < MAXBIT; i++) {
		des->visitedInfo[i] = src->visitedInfo[i];
	}
}
 
//MK: Node의 Visited 도시 정보만 복사
void copyNodeListOnly(int srcPtr, int desPtr) {
	node *src = &list[srcPtr];
	node *des = &list[desPtr];
	for (int i = 0; i < MAXBIT; i++) {
		des->visitedInfo[i] |= src->visitedInfo[i];
	}
}
 
//MK: Stack에 추가하는 부분
void insertStack(int srcPtr, int desPtr) {
	if (list[desPtr].counter == 0) {
		copyNode(srcPtr, desPtr);
		node *des = &list[desPtr];
		int ptr = desPtr / 31;
		int rem = desPtr % 31;
		des->visitedInfo[ptr] |= 1 << rem;
		des->counter++;
		stack[stackEnd] = desPtr;
		stackEnd++;
		if (stackEnd >= MAXCITY - 1) {
			stackEnd = 0;
		}
	}
	else {
		node *src = &list[srcPtr];
		node *des = &list[desPtr];
		if ((src->counter + 1) == des->counter) {
			copyNodeListOnly(srcPtr, desPtr);
		}
	}
}
 
//MK: Stack에 Pop하는 부분
int popStack() {
	if (stackPtr == stackEnd) {
		return -1;
	}
	int ret = stack[stackPtr];
	stackPtr++;
	if (stackPtr >= MAXCITY - 1) {
		stackPtr = 0;
	}
	return ret;
}
 
//MK: Stack을 사용하여 문제를 해결하는 부분
void findResult() {
	int minValue = 0;
	while (1) {
		int ptr = popStack();
		if (ptr == -1) {
			return;
		}
		for (int i = 0; i < numRoad; i++) {
			//MK: 이부분 엄청난 Overhead로 작용함
			//MK: 이부분에서 빨리 끝나기 때문에 실행시간이 빨라 질것이라 판단했으나, 매번 검사하는 Overhead가 더 큰것 같음
			/*if (minValue != 0 && minValue < list[ptr].counter) {
				return;
			}*/ 
			if (allRoads[i][0] == ptr) {
				if (allRoads[i][1] == numCity) {
					if (minValue != 0 && minValue != list[ptr].counter) {
						return;
					}
					insertStack(ptr, numCity);
					if (minValue == 0) {
						//answer[numCity] = 1;
						int ans = numCity / 31;
						int rem = numCity % 31;
						list[numCity].visitedInfo[ans] |= (1 << rem);
						minValue = list[ptr].counter;
					}
				}
				else {
					insertStack(ptr, allRoads[i][1]);
				}
			}
		}
	}
}
 
int main() {
	freopen("input.txt", "r", stdin);
 
	int testCase;
	scanf("%d", &testCase);
	for (int m = 1; m <= testCase; m++) {
		scanf("%d %d", &numCity, &numRoad);
		init();
		for (int i = 0; i < numRoad; i++) {
			scanf("%d %d", &allRoads[i][0], &allRoads[i][1]);
		}
		findResult();
		for (int i = 1; i <= numCity; i++) {
			int ptr = i / 31;
			int rem = i % 31;
			int tmp = (list[numCity].visitedInfo[ptr] & (1 << rem));
			if (tmp > 0)
				printf("%d ", i);
		}
		printf("\n");
	}
 
	return 0;
}