#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

char tree[MAX];   // 배열로 트리 저장 (1번부터 시작)

// 괄호 문자열을 파싱해서 배열에 트리 저장
// expr: 입력 문자열, pos: 현재 파싱 위치, idx: 현재 노드 index
int buildTree(const char* expr, int* pos, int idx) {
    while (expr[*pos] == ' ') (*pos)++;  // 공백 무시

    if (expr[*pos] == '(') {
        (*pos)++;  // '(' 스킵
        while (expr[*pos] == ' ') (*pos)++;

        if (isalpha(expr[*pos])) {
            tree[idx] = expr[*pos];  // 현재 노드 저장
            (*pos)++;

            // 왼쪽 서브트리
            buildTree(expr, pos, idx * 2);

            // 오른쪽 서브트리
            buildTree(expr, pos, idx * 2 + 1);
        }
        while (expr[*pos] == ' ') (*pos)++;

        if (expr[*pos] == ')') {
            (*pos)++;  // ')' 스킵
        }
    }
    return idx;
}

// iterative preorder
void preorder_iter(int root) {
    int stack[MAX], top = -1;
    stack[++top] = root;

    while (top >= 0) {
        int node = stack[top--];
        if (node < MAX && tree[node] != 0) {
            printf("%c ", tree[node]);
            stack[++top] = node * 2 + 1; // 오른쪽 먼저 push
            stack[++top] = node * 2;     // 왼쪽 push
        }
    }
}

// iterative inorder
void inorder_iter(int root) {
    int stack[MAX], top = -1;
    int curr = root;

    while (curr > 0 || top >= 0) {
        if (curr < MAX && tree[curr] != 0) {
            stack[++top] = curr;
            curr = curr * 2; // 왼쪽 이동
        }
        else {
            curr = stack[top--];
            printf("%c ", tree[curr]);
            curr = curr * 2 + 1; // 오른쪽 이동
        }
    }
}

// iterative postorder
void postorder_iter(int root) {
    int stack1[MAX], stack2[MAX];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    while (top1 >= 0) {
        int node = stack1[top1--];
        if (node < MAX && tree[node] != 0) {
            stack2[++top2] = node;
            stack1[++top1] = node * 2;     // 왼쪽
            stack1[++top1] = node * 2 + 1; // 오른쪽
        }
    }

    while (top2 >= 0) {
        printf("%c ", tree[stack2[top2--]]);
    }
}

int main() {
    char input[1000];
    fgets(input, sizeof(input), stdin);

    memset(tree, 0, sizeof(tree));
    int pos = 0;
    buildTree(input, &pos, 1); // root = 1

    printf("pre-order: ");
    preorder_iter(1);
    printf("\n");

    printf("in-order: ");
    inorder_iter(1);
    printf("\n");

    printf("post-order: ");
    postorder_iter(1);
    printf("\n");

    return 0;
}
