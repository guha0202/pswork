#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30000

long int p[N];
struct edge{
    long int v,next;
}e[N];
long int vis[N];
long int eid = 0;
long int l,r;
long int q[N];
void insert(long int u,long int v)
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
long int bfs(long int u,long int h)
{
    l=0;r=0;
    memset(vis,-1,sizeof(vis));
    vis[u] = 0;
    q[r++] = u;
    while(l<r)
    {
        long int now = q[l++];
        if(now == h)
            return vis[now]-1;
        for (long int i = p[now]; ~i; i = e[i].next)
        {
            long int v = e[i].v;
            if (vis[v] == -1) 
            {
                vis[v] = vis[now] + 1;
                q[r++] = v;
            }
        }
    }
    return -1;
}

int main()
{
    long int t;
    scanf("%ld",&t);
    long int num = t;
    getchar();
    long long int x[20][1005],y[20][1005],z[20][1005];
    long long int n[20];
    long long int h[20],d[20];
    while(t--)
    {
        scanf("%lld%lld%lld",&n[t],&h[t],&d[t]);
        getchar();
        for(long long int i = 0;i < n[t];i++)
        {
            scanf("%lld%lld%lld",&x[t][i],&y[t][i],&z[t][i]);
            if(t!=0||i!=n[t]-1)
                getchar();   
        }
    }    
    while(num--)
    {
        memset(e,-1,sizeof(e));
        memset(p,-1,sizeof(p));
        memset(q,-1,sizeof(q));
        eid = 0;
        for(long int i = 0;i < n[num];i++)
        {
            for(long int j = 0;j < i;j++)
            {
                long long int distance;
                distance = (x[num][i]-x[num][j])*(x[num][i]-x[num][j]);
                distance += (y[num][i]-y[num][j])*(y[num][i]-y[num][j]);
                distance += (z[num][i]-z[num][j])*(z[num][i]-z[num][j]);
                
                long long int d2;
                d2 = d[num]*2;
                d2 = d2*d2;
                if(d2 >= distance)
                    insert2(i+2,j+2);
            }
            if(z[num][i]<=d[num])
                insert2(0,i+2);
            if(z[num][i]>=h[num]-d[num])
                insert2(i+2,1);
        }

        printf("%ld",bfs(0,1));
        if(num!=0)
            printf("\n");
    }
    return 0;
}
