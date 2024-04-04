#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct edge{
    long int v,next;
}e[100000];
long int eid = 0;
long int p[100000];
long int sec[100000];
long int q[100000];
long int l,r;
void insert(int u,int v)
{
    e[eid].v = v;
    e[eid].next = p[u];
    p[u] = eid++;
}
void insert2(long int u,long int v)
{
    insert(u,v);
    insert(v,u);
}

long int bfs(long int c,long int m)
{
    sec[c] = 1;
    l = r = 0;
    long int ans;
    q[r++] = c;
    while(l < r)
    {
        long int now = q[l++];
        for(long int i = p[now];~i;i = e[i].next)
        {
            long int v = e[i].v;
            if(sec[v] == -1)
            {
                sec[v] = sec[now]+1;
                q[r++] = v;
                ans = sec[v]+m;
            }
        }
    }
    return ans;
}

int main()
{
    long int n,pi,c;
    long int m;
    long int u,v;
    memset(sec,-1,sizeof(sec));
    memset(p,-1,sizeof(p));
    scanf("%ld%ld%ld",&n,&pi,&c);
    getchar();
    scanf("%ld",&m);
    for(long int i = 0;i < pi;i++)
    {
        scanf("%ld%ld",&u,&v);
        insert2(u,v);
        if(i!=pi-1)
            getchar();
    }
    printf("%ld",bfs(c,m));
    
    return 0;
}
