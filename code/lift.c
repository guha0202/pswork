#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct edge{
     int v,next;
}e[400];
int eid = 0;
int p[200];
int sec[10000];
int q[200];
long int l,r;
void insert(int u,int v)
{
    e[eid].v = v;
    e[eid].next = p[u];
    p[u] = eid++;
}

int bfs(int a,int b)
{
    sec[a] = 0;
    l = r = 0;
    q[r++] = a;
    while(l < r)
    {
        int now = q[l++];
        for(int i = p[now];~i;i = e[i].next)
        {
            int v = e[i].v;
            if(sec[v] == -1)
            {
                sec[v] = sec[now]+1;
                q[r++] = v;
            }
            if(v==b)
                return sec[v];
        }
    }
    return -1;
}

int main()
{
    int n,a,b;
    int v;
    memset(p,-1,sizeof(p));
    memset(sec,-1,sizeof(sec));
    scanf("%d%d%d",&n,&a,&b);
    getchar();
    for(int i = 1;i <= n;i++)
    {
        scanf("%d",&v);
        if(i+v<=n)
            insert(i,v+i);
        if(i-v>0)
            insert(i,i-v);
    }
    printf("%d",bfs(a,b));
    
    return 0;
}
