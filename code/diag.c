#include <stdio.h>
#define MAX 100
int diag[MAX][MAX];
void dispdiag(int m, int n)
{
    if(m == 1 || n ==1)
    {
        for (int i = 0; i < m; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                printf("%d", diag[i][j]);
                if(i != m-1 || j != n-1)
                    printf(" ");
            }
        }
    }
    else
    {
        int i = 0, j = 0;
        while(i<=m-1&&j<=n-1){
            if(i == 0 && j == 0)
            {
                printf("%d ",diag[i][j++]);
                printf("%d ",diag[i++][j--]);
                printf("%d ",diag[i][j]);
            }
            else if(j == 0)
            {
                if(i!=m-1)
                {
                    printf("%d ",diag[++i][j]);
                    while(i>0&&j<n-1)
                        printf("%d ",diag[--i][++j]);             
                }
                else
                {
                    printf("%d ",diag[i][++j]);
                    while(i>0&&j<n-1)
                        printf("%d ",diag[--i][++j]);
                }
            }
            else if(i == 0)
            {
                if(j!=n-1)
                {
                    printf("%d ",diag[i][++j]);
                    while(i<m-1&&j>0)
                        printf("%d ",diag[++i][--j]);
                }
                else
                {
                    printf("%d ",diag[++i][j]);
                    while(i<m-1&&j>0)
                        printf("%d ",diag[++i][--j]);
                }
            }
            else if(j == n-1&&i != m-1)
            {
                printf("%d ",diag[++i][j]);
                while(i<m-1&&j>0)
                    printf("%d ",diag[++i][--j]);
            }
            else if(i == m-1&&j != n-1)
            {
                printf("%d ",diag[i][++j]);
                while(i>0&&j<n-1)
                   printf("%d ",diag[--i][++j]);
            }
            else
                return;
        }
    }
}


int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    getchar();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &diag[i][j]);
        }
    }
    
    dispdiag(m, n);
    return 0;
}
