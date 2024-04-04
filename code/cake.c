#include <stdio.h>
#include <string.h>
#define MAX 1000

int in(int x,int y,int r,int c)
{
    if(0<=x&&x<r&&0<=y&&y<c)
        return 1;
    return 0;
}
long int ans = 0;
long int cnt = 0;
int vis[MAX][MAX];
char cake[MAX][MAX];
int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

void dfs(int u,int v,int r, int c)
{
    vis[u][v] = 1;
    cnt++;
    for(int i = 0;i < 4;i++)
    {
        int nexu = u+dir[i][0];
        int nexv = v+dir[i][1];
        if(in(nexu,nexv,r,c)&&!vis[nexu][nexv]&&cake[nexu][nexv]=='#')
        {
            vis[nexu][nexv] = 1;
            dfs(nexu,nexv,r,c);
        }
    }
}

int main()
{
    int r,c;
    scanf("%d%d",&r,&c);
    getchar();
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++) 
        {
            scanf("%c",&cake[i][j]);
        }
	getchar();
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++) 
        {
            if(cake[i][j] == '#'&&!vis[i][j])
            {
                dfs(i,j,r,c);
                if (cnt > ans) 
                    ans = cnt; // 求最大连通块 
		cnt = 0;
            }
        }
    }
    printf("%ld",ans);
    return 0;
}

