#include <stdio.h>
#include<stdlib.h>
#define M 20
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//lixiaoyao//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
char mir[M][M];
int vis[M][M];
int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
int l,r;
int in(int u,int v,int m,int n)
{
    if(0<=u&&u<m&&0<=v&&v<n)
        return 1;
    return 0;
}
struct node{
    int u,v,d;
}q[M*M];
int bfs(int u,int v,int m,int n)
{
    l = 0;r = 0;
    vis[u][v]=1;
    struct node t = {u,v,0};
    q[r++] = t;
    while(l!=r)
    {
        struct node now = q[l++];
        if (mir[now.u][now.v] == '*') {
            return now.d;
        }
        for (int i = 0; i < 4; i++) {
            int tu = now.u + dir[i][0];
            int tv = now.v + dir[i][1];
            if (in(tu,tv,m,n) && mir[tu][tv] != '#' && !vis[tu][tv]) {
                vis[tu][tv] = 1;
                struct node t = {tu, tv, now.d + 1};
                q[r++] = t;
            }
        }
    }
    return -1;
}

int main()
{
    int m,n,u,v;
    scanf("%d%d",&m,&n);
    getchar();
    for(int i = 0;i < m;i++)
    {
        for(int j = 0;j < n;j++)
        {
            scanf("%c",&mir[i][j]);
            if(mir[i][j]=='@')
            {
                u = i;
                v = j;
            }
        }
        if(i!=m-1)
            getchar();
    }
    printf("%d",bfs(u,v,m,n));
    return 0;
}
