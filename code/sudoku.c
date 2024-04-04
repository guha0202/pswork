#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sudoku[9][9];

int is_valid(char sudoku[9][9], int row, int col, char num) {
    // 检查行中是否有重复数字
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == num) {
            return 0;
        }
    }

    // 检查列中是否有重复数字
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col] == num) {
            return 0;
        }
    }

    // 检查3 x 3宫中是否有重复数字
    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
    for (int i = start_row; i < start_row + 3; i++) {
        for (int j = start_col; j < start_col + 3; j++) {
            if (sudoku[i][j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

// 使用回溯法解答数独
int solve_sudoku(char sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == '*') {
                for (char num = '1'; num <= '9'; num++) {
                    if (is_valid(sudoku, i, j, num)) {
                        sudoku[i][j] = num;
                        if (solve_sudoku(sudoku)) {
                            return 1;
                        }
                        sudoku[i][j] = '*';
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
	for(int i = 0;i < 9;i++)
	{
		for(int j = 0;j < 9;j++)
		{
			scanf("%c", &sudoku[i][j]);
            if(j!=8)getchar();
		}
        if(i!=8)getchar();
	}
	
	solve_sudoku(sudoku);
	
	for(int i = 0;i < 9;i++)
	{
		for(int j = 0;j < 9;j++)
		{
			printf("%c ", sudoku[i][j]);
		}
		if(i != 8)
			printf("\n");
	}
}
