/*
#include <stdio.h>
#include <string.h>
#define MAX 250000
int vis[MAX];
int p[MAX];
int count = 0;
int eid = 0;
struct edge{
    int v,next;
}e[MAX*2];

void insert(int u,int v)
{
    e[eid].v = v;
    e[eid].next = p[u];
    p[u] = eid++;
}

void dfs(int x)
{
    vis[x] = 1;
    for(int i = p[x];~i;i = e[i].next)
    {
        int v = e[i].v;
        if(!vis[v])
            dfs(v);
    }
}

int main()
{
    int n,m;
    char map[MAX];
    memset(p, -1, sizeof(p));
    memset(vis, 0, sizeof(vis));

    scanf("%d %d",&n,&m);
    getchar();
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < m;j++)
        {
            scanf("%c",&map[i*m+j]);
        }
        if(i!=n-1)
            getchar();
    }
    for(int i = 0;i < n*m;i++)
    {
        if(map[i] == '1') 
        {
            int row = i / m, col = i % m;
            for(int j = 0;j < m;j++)
            {
                if(map[row * m + j] == '1' && j != col) 
                    insert(i, row * m + j);
            }
            for(int j = 0;j < n;j++)
            {
                if(map[j * m + col] == '1' && j != row) 
                    insert(i, j * m + col);
            }
        }
    }
    for(int i = 0;i < n*m;i++)
    {
        if(!vis[i]&&map[i]=='1')
        {
            count++;
            dfs(i);
        }
    }
    printf("%d",count);
    return 0;
}
*/
#include <stdio.h>
#include <stdbool.h>

int n, m; // 地图的行数和列数
char grid[500][500]; // 地图信息
bool visited[500][500]; // 记录地图上的方格是否已经被访问过

// 进行深度优先搜索
void dfs(int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= m || visited[r][c] || grid[r][c] == '0') {
        return;
    }

    visited[r][c] = true;

    // 在当前位置的上、下、左、右四个方向进行递归搜索
    for(int i = 1;r-i>=0;i++)
        dfs(r - i, c); // 上
    for(int i = 1;r+i<n;i++)
        dfs(r + i, c); // 下
    for(int i = 1;c-i>=0;i++)
        dfs(r, c - i); // 左
    for(int i = 1;c+i<m;i++)
        dfs(r, c + i); // 右
}

// 计算最少需要手动引爆的炸弹数
int countBombs() {
    int count = 0; // 引爆的炸弹数

    // 初始化visited数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    }

    // 遍历地图上的每个方格
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == '1') {
                count++;
                dfs(i, j);
            }
        }
    }

    return count;
}

int main() {
    // 读取输入
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    // 计算最少需要手动引爆的炸弹数并输出结果
    int result = countBombs();
    printf("%d\n", result);

    return 0;
}
/*
#include <stdio.h>
#include <stdbool.h>

int n, m; // 地图的行数和列数
char grid[500][500]; // 地图信息
bool visited[500][500]; // 记录地图上的方格是否已经被访问过

// 进行深度优先搜索
void dfs(int r, int c) {
    if (r < 0 || r >= n || c < 0 || c >= m || visited[r][c] || grid[r][c] == '0') {
        return;
    }

    visited[r][c] = true;

    // 在当前位置的上、下、左、右四个方向进行递归搜索
    for(int i = 1;r-i>=0;i++)
        dfs(r - i, c); // 上
    for(int i = 1;r+i<n;i++)
        dfs(r + i, c); // 下
    for(int i = 1;c-i>=0;i++)
        dfs(r, c - i); // 左
    for(int i = 1;c+i<m;i++)
        dfs(r, c + i); // 右
}

// 计算最少需要手动引爆的炸弹数
int countBombs() {
    int count = 0; // 引爆的炸弹数

    // 初始化visited数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    }

    // 遍历地图上的每个方格
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == '1') {
                count++;
                dfs(i, j);
            }
        }
    }

    return count;
}

int main() {
    // 读取输入
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    // 计算最少需要手动引爆的炸弹数并输出结果
    int result = countBombs();
    printf("%d\n", result);

    return 0;
}
*/
