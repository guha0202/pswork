#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int l[20];
int cmp(const void *a, const void *b)
{
    return *(long int*)a - *(long int*)b;
}

int dfs(long int target_sum, long int curr_sum, int idx, int subset_count, int n) {
    if (subset_count == 3)
        return 1;
    
    if (curr_sum == target_sum)
        return dfs(target_sum, 0, 0, subset_count + 1, n);
    
    if (idx >= n || curr_sum > target_sum)
        return 0;
    
    for (int i = idx; i < n; i++) {
        if (l[i] != -1) { // 避免重复使用相同的元素
            long int temp = l[i];
            l[i] = -1; // 标记该元素已被使用
            
            if (dfs(target_sum, curr_sum + temp, i + 1, subset_count, n)) {
                l[i] = temp; // 恢复标记
                return 1;
            }
            
            l[i] = temp; // 恢复标记
            if (curr_sum == 0) // 如果当前子集和为0，终止该分支的搜索
                break;
        }
    }
    
    return 0;
}


int main()
{
    int n;
    long int sum = 0;
    scanf("%d", &n);
    for(int i = 0;i < n;i++)
    {
        scanf("%ld", &l[i]);
        sum += l[i];
    }
    if (sum % 4 != 0) 
    { 
        printf("No");
        return 0;
    }
    sum /= 4;
    qsort(l, n, sizeof(long int), cmp);
    if(dfs(sum,0,0,0,n))
        printf("Yes");
    else
        printf("No");
    return 0;
}
