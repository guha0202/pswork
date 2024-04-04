#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define H 1000000

long int h[20];
long int ans = 1000000;
void dfs(long int s, long int b, int idx,int n)
{
    if(s - b >= ans)
        return;
    else if(s < b)
    {
        if(idx < n)
        {
            dfs(s+h[idx],b,idx+1,n);
            dfs(s,b,idx+1,n);
        }
        else
            return;
    }
    else
        ans = s - b;
}

int main()
{
    int n;
    long int b;
    scanf("%d%ld", &n, &b);
    for(int i = 0;i < n;i++)
    {
        scanf("%ld",&h[i]);
        if(i != n-1)
            getchar();
    }
    dfs(0,b,0,n);
    printf("%ld",ans);
    return 0;
}
