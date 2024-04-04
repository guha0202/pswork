#include <stdio.h>
#include <string.h>
#define MAX 20000
struct edge {
    int v, next;
} e[2*MAX];
int p[MAX];
int vis[MAX];
int eid = 0;
int count = 0;
void insert(int x, int y) {
    e[eid].v = y;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert2(int x, int y) {
    insert(x, y);
    insert(y, x);
}

void dfs(int u) {
    vis[u] = 1;
    for (int i = p[u]; ~i; i = e[i].next) {
        int v = e[i].v;
        if (!vis[v]) {
            dfs(v);
        }
    }
}
int main() {
    memset(p, -1, sizeof(p));
    int n, m;
    scanf("%d %d",&n,&m);
    getchar();
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d",&u,&v);
        getchar();
        insert2(u, v);
    }
    for(int i = 1;i <= n;i++)
    {
        if(!vis[i])
        {
            count++;
            dfs(i);
        }
    }
    printf("%d",count);
    return 0;
}

