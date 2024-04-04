#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct state {
    char digits[5];
    int steps;
} q[10000];

int visited[10][10][10][10];
int r,l;
int min = 100;

int bfs(char* start, char* target) {
    struct state s;
    strcpy(s.digits, start);
    s.steps = 0;

    // 初始化visited数组
    memset(visited, 0, sizeof(visited));

    // 构造队列
    r = 0; l = 0;
    q[r++] = s;
    visited[start[0]-'0'][start[1]-'0'][start[2]-'0'][start[3]-'0'] = 1;

    while (l<r) {
        struct state current = q[l++];

        // 判断是否达到目标状态
        if (strcmp(current.digits, target) == 0) {
            if(min > current.steps)
                min = current.steps;
        }

        // 对每一位数字进行变换操作
        int num1 = 0,num2 = 0,num3 = 0;
        for (int i = 0; i < 4; i++) {
            struct state next;

            // 递增
            if(next.digits[i]==target[i])
                continue;
            next.digits[i] = current.digits[i] + 1;
            if (next.digits[i] > '9') {
                next.digits[i] = '1';
            }
            for(int j = 0;j < 4;j++)
            {
                if(j!=i)
                   next.digits[j] = current.digits[j]; 
            }
            next.steps = current.steps + 1;

            if (!visited[next.digits[0]-'0'][next.digits[1]-'0'][next.digits[2]-'0'][next.digits[3]-'0']) {
                q[r++] = next;
                visited[next.digits[0]-'0'][next.digits[1]-'0'][next.digits[2]-'0'][next.digits[3]-'0'] = 1;
            }
            
            
            if(next.digits[i]==target[i])
                continue;
            next.digits[i] = current.digits[i] - 1;
            if (next.digits[i] < '1') {
                next.digits[i] = '9';
            }
             for(int j = 0;j < 4;j++)
            {
                if(j!=i)
                   next.digits[j] = current.digits[j]; 
            }
            next.steps = current.steps + 1;

            if (!visited[next.digits[0]-'0'][next.digits[1]-'0'][next.digits[2]-'0'][next.digits[3]-'0']) {
                q[r++] = next;
                visited[next.digits[0]-'0'][next.digits[1]-'0'][next.digits[2]-'0'][next.digits[3]-'0'] = 1;
            }
        }

        for (int i = 0; i < 3; i++) {
            struct state next;
            if(next.digits[i]==target[i]&&next.digits[i+1]==target[i+1])
                continue;
            next.digits[i] = current.digits[i+1];
            next.digits[i+1] = current.digits[i];
            for(int j = 0;j < 4;j++)
            {
                if(j!=i&&j!=i+1)
                   next.digits[j] = current.digits[j]; 
            }
            next.steps = current.steps  + 1;

            if (!visited[next.digits[0]-'0'][next.digits[1]-'0'][next.digits[2]-'0'][next.digits[3]-'0']) {
                q[r++] = next;
                visited[next.digits[0]-'0'][next.digits[1]-'0'][next.digits[2]-'0'][next.digits[3]-'0'] = 1;
            }
        }
    }
    return min;
}

int main() {
    char start[5], target[5];
    scanf("%s", start);
    scanf("%s", target);

    int steps = bfs(start, target);
    printf("%d", steps);

    return 0;
}
