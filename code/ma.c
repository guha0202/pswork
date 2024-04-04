#include <stdio.h>
#include <string.h>
#define X 10
#define Y 9

char qipan[10][9];
int dir[8][2] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
int vis[10][9];
int flag = 0;
int in(int i,int j)
{
    if(0<=i&&i<X&&0<=j&&j<Y)
        return 1;
    return 0;
}

int dfs(int u,int v)
{
    vis[u][v]=1;
    for(int i =0;i<8;i++)
    {
        int nexu = u+dir[i][0];
        int nexv = v+dir[i][1];
        if(in(nexu,nexv)&&qipan[nexu][nexv]=='.'&&!vis[nexu][nexv])
            dfs(nexu,nexv);
        else if(in(nexu,nexv)&&qipan[nexu][nexv]=='T')
            flag = 1;
    }
    if(flag)
        return 1;
    return 0;
}
int main()
{
    memset(vis,0,sizeof(vis));
    int flagi,flagj;
    for(int i =0;i<X;i++)
    {
        for(int j =0;j<Y;j++)
        {
            scanf("%c",&qipan[i][j]);
            if(qipan[i][j]=='S')
            {
                flagi = i;
                flagj = j;
            }
        }
        getchar();
    }
    if(dfs(flagi,flagj))
        printf("Yes");
    else
        printf("No");
    return 0;
}


