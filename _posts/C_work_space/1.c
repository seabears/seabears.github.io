#include <stdio.h>

#define MAX_NM 50

int N, M;
int parent[MAX_NM + 1];  // 유니온 파인드 부모 배열
int arr_came_party[MAX_NM][MAX_NM + 1];  // 파티 참석자 정보
int truth_known[MAX_NM + 1];  // 진실을 아는 사람 여부

// 유니온 파인드: 루트 찾기
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

// 유니온 파인드: 합치기
void union_sets(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[b] = a;  // 하나의 그룹으로 합침
}

int main() {
    scanf("%d %d", &N, &M);

    // 유니온 파인드 초기화 (각 사람이 자기 자신을 루트로 설정)
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int known_num;
    scanf("%d", &known_num);

    // 진실을 아는 사람 저장
    for (int i = 0; i < known_num; i++) {
        int person;
        scanf("%d", &person);
        truth_known[person] = 1;  // 진실을 아는 사람 표시
    }

    // 파티 참석 정보 입력 및 그룹 연결
    for (int i = 0; i < M; i++) {
        scanf("%d", &arr_came_party[i][0]);  // 파티에 참여한 사람 수

        if (arr_came_party[i][0] > 0) {
            scanf("%d", &arr_came_party[i][1]);  // 첫 번째 사람
            for (int j = 2; j <= arr_came_party[i][0]; j++) {
                scanf("%d", &arr_came_party[i][j]);
                // 같은 파티에 있는 사람들을 하나의 그룹으로 연결
                union_sets(arr_came_party[i][1], arr_came_party[i][j]);
            }
        }
    }

    // 진실을 아는 사람들의 그룹 루트를 모두 찾고, 해당 그룹에 속한 사람들 표시
    for (int i = 1; i <= N; i++) {
        if (truth_known[i]) {
            truth_known[find(i)] = 1;  // 해당 그룹을 진실을 알아야 하는 그룹으로 설정
        }
    }

    // 거짓말할 수 있는 파티 개수 계산
    int max_lie = 0;
    for (int i = 0; i < M; i++) {
        int can_lie = 1;  // 기본적으로 거짓말 가능하다고 가정

        for (int j = 1; j <= arr_came_party[i][0]; j++) {
            int person = arr_came_party[i][j];
            if (truth_known[find(person)]) {  // 해당 사람이 속한 그룹이 진실을 알아야 하는 그룹이면
                can_lie = 0;  // 거짓말할 수 없음
                break;
            }
        }

        if (can_lie) {
            max_lie++;  // 거짓말할 수 있는 파티 증가
        }
    }

    printf("%d\n", max_lie);
    return 0;
}
/*
#1)
4 3
0
2 1 2
1 3
3 2 3 4



*/