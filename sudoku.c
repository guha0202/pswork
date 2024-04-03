/**
 * Name: main.c
 * Description: Sudoku puzzle solver using threads. (pthread library)
 * Date: November 19th, 2014.
 * 
 * ==============================================================================
 * 
 * Copyright (C) 2014  Carlos Perea
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * Structure that holds the parameters passed to a thread.
 * This specifies where the thread should start verifying.
 */
typedef struct 
{
    // The starting row.
    int row;
    // The starting column.
    int col;
    // The pointer to the board.
    int (* board)[9];
} parameters;

// Prototype for the walk_rows function.
void * walk_row(void * params);

// Prototype for the walk_cols function.
void * walk_col(void * params);

// Prototype for 3x3 square function.
void * check_square(void * params);

/***************
 * ENTRY POINT
 **************/
int main(void) 
{
    // ====== Create the board =======
    int board[9][9] = {  
            {6, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 4, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
        };
    
    // ====== Create the parameters for the 3x3 threads ======
    
    // First 3x3
    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1->row = 0;
    param1->col = 0;
    param1->board = board;
    
    // Second 3x3
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2->row = 0;
    param2->col = 3;
    param2->board = board;
    
    // Third 3x3
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3->row = 0;
    param3->col = 6;
    param3->board = board;
    
    // Fourth 3x3
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4->row = 3;
    param4->col = 0;
    param4->board = board;
    
    // Fifth 3x3
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5->row = 3;
    param5->col = 3;
    param5->board = board;
    
    // Sixth 3x3
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6->row = 3;
    param6->col = 6;
    param6->board = board;
    
    // Seventh 3x3
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7->row = 6;
    param7->col = 0;
    param7->board = board;
    
    // Eighth 3x3
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->row = 6;
    param8->col = 3;
    param8->board = board;
    
    // Ninth 3x3
    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->row = 6;
    param9->col = 6;
    param9->board = board;
    // ====== Create the parameter for the columns check =======
    
    //col1
    parameters * param10 = (parameters *) malloc(sizeof(parameters));
    param10->row = 0;
    param10->col = 0;
    param10->board = board;

    //col2
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param11->row = 0;
    param11->col = 1;
    param11->board = board;

    //col3
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param12->row = 0;
    param12->col = 2;
    param12->board = board;
    
    //col4
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param13->row = 0;
    param13->col = 3;
    param13->board = board;
    
    //col5
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param14->row = 0;
    param14->col = 4;
    param14->board = board;
    
    //col6
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param15->row = 0;
    param15->col = 5;
    param15->board = board;

    //col7
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param16->row = 0;
    param16->col = 6;
    param16->board = board;
    
    //col8
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param17->row = 0;
    param17->col = 7;
    param17->board = board;
    
    //col9
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param18->row = 0;
    param18->col = 8;
    param18->board = board;

    // ====== Create the parameter for the rows check =======
    
    //row1
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param19->row = 0;
    param19->col = 0;
    param19->board = board;
    
    //row2
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param20->row = 1;
    param20->col = 0;
    param20->board = board;
    
    //row3
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param21->row = 2;
    param21->col = 0;
    param21->board = board;
    
    //row4
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param22->row = 3;
    param22->col = 0;
    param22->board = board;
    
    //row5
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param23->row = 4;
    param23->col = 0;
    param23->board = board;
    
    //row6
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param24->row = 5;
    param24->col = 0;
    param24->board = board;
    
    //row7
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param25->row = 6;
    param25->col = 0;
    param25->board = board;
    
    //row8
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param26->row = 7;
    param26->col = 0;
    param26->board = board;
    
    //row9
    parameters * param11 = (parameters *) malloc(sizeof(parameters));
    param27->row = 8;
    param27->col = 0;
    param27->board = board;

    // ====== Create the threads ======
    pthread_t thread_row1, thread_row2, hread_row3, thread_row4, thread_row5, \
    thread_row6, thread_row7, thread_row8, thread_row9, thread_col1, thread_col2, \
    thread_col3, thread_col4, thread_col5, thread_col6, thread_col7, thread_col8, \
    thread_col9, thread1, thread2, thread3, thread4, thread5, thread6, thread7, \
    thread8, thread9;
    
    // ====== Create the return values for the threads ======
    void * row1;
    void * row2;
    void * row3;
    void * row4;
    void * row5;
    void * row6;
    void * row7;
    void * row8;
    void * row9;
    void * col1;
    void * col2;
    void * col3;
    void * col4;
    void * col5;
    void * col6;
    void * col7;
    void * col8;
    void * col9;
    void * square1;
    void * square2;
    void * square3;
    void * square4;
    void * square5;
    void * square6;
    void * square7;
    void * square8;
    void * square9;
    
    // ====== Initialize the threads ======

    pthread_create(&thread1, NULL, check_square, (void *) param1);
    pthread_create(&thread2, NULL, check_square, (void *) param2);
    pthread_create(&thread3, NULL, check_square, (void *) param3);
    pthread_create(&thread4, NULL, check_square, (void *) param4);
    pthread_create(&thread5, NULL, check_square, (void *) param5);
    pthread_create(&thread6, NULL, check_square, (void *) param6);
    pthread_create(&thread7, NULL, check_square, (void *) param7);
    pthread_create(&thread8, NULL, check_square, (void *) param8);
    pthread_create(&thread9, NULL, check_square, (void *) param9);
    pthread_create(&thread_col1, NULL, walk_cols, (void *) param10);
    pthread_create(&thread_col2, NULL, walk_cols, (void *) param11);
    pthread_create(&thread_col3, NULL, walk_cols, (void *) param12);
    pthread_create(&thread_col4, NULL, walk_cols, (void *) param13);
    pthread_create(&thread_col5, NULL, walk_cols, (void *) param14);
    pthread_create(&thread_col6, NULL, walk_cols, (void *) param15);
    pthread_create(&thread_col7, NULL, walk_cols, (void *) param16);
    pthread_create(&thread_col8, NULL, walk_cols, (void *) param17);
    pthread_create(&thread_col9, NULL, walk_cols, (void *) param18);
    pthread_create(&thread_row1, NULL, walk_rows, (void *) param19);
    pthread_create(&thread_row2, NULL, walk_rows, (void *) param20);
    pthread_create(&thread_row3, NULL, walk_rows, (void *) param21);
    pthread_create(&thread_row4, NULL, walk_rows, (void *) param22);
    pthread_create(&thread_row5, NULL, walk_rows, (void *) param23);
    pthread_create(&thread_row6, NULL, walk_rows, (void *) param24);
    pthread_create(&thread_row7, NULL, walk_rows, (void *) param25);
    pthread_create(&thread_row8, NULL, walk_rows, (void *) param26);
    pthread_create(&thread_row9, NULL, walk_rows, (void *) param27);
    
    // ======= Wait for all threads to finish their tasks =======
    pthread_join(thread_row1, &row1);
    pthread_join(thread_row2, &row2);
    pthread_join(thread_row3, &row3);
    pthread_join(thread_row4, &row4);
    pthread_join(thread_row5, &row5);
    pthread_join(thread_row6, &row6);
    pthread_join(thread_row7, &row7);
    pthread_join(thread_row8, &row8);
    pthread_join(thread_row9, &row9);
    pthread_join(thread_col1, &col1);
    pthread_join(thread_col2, &col2);
    pthread_join(thread_col3, &col3);
    pthread_join(thread_col4, &col4);
    pthread_join(thread_col5, &col5);
    pthread_join(thread_col6, &col6);
    pthread_join(thread_col7, &col7);
    pthread_join(thread_col8, &col8);
    pthread_join(thread_col9, &col9);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);
    
    // ====== Check whether the Sudoku Puzzle was solved ======
    if (    (int) row1 == 1 &&
            (int) row2 == 1 &&
            (int) row3 == 1 &&
            (int) row4 == 1 &&
            (int) row5 == 1 &&
            (int) row6 == 1 &&
            (int) row7 == 1 &&
            (int) row8 == 1 &&
            (int) row9 == 1 &&
            (int) col1 == 1 &&
            (int) col2 == 1 &&
            (int) col3 == 1 &&
            (int) col4 == 1 &&
            (int) col5 == 1 &&
            (int) col6 == 1 &&
            (int) col7 == 1 &&
            (int) col8 == 1 &&
            (int) col9 == 1 &&
            (int) square1 == 1 &&
            (int) square2 == 1 &&
            (int) square3 == 1 &&
            (int) square4 == 1 &&
            (int) square5 == 1 &&
            (int) square6 == 1 &&
            (int) square7 == 1 &&
            (int) square8 == 1 &&
            (int) square9 == 1 ) {
        printf("The Sudoku Puzzle is solved!\n");
    }
    else {
        printf("The Sudoku Puzzle is NOT solved.\n");
    }
    
    return 0;
}

/**
 * Checks each row if it contains all digits 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * walk_rows(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    for (int i = startCol; i < 9; ++i) {
        int row[10] = {0};
        int val = data->board[startRow][i];
        if (row[val] != 0)
            return (void *) 0;
        else
            row[val] = 1;
    }
    return (void *) 1;
}

/**
 * Checks each column if it contains all digits 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * walk_cols(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    for (int i = startRow; i < 9; ++i) 
    {
        int col[10] = {0};
        int val = data->board[i][StartCol];
        if (col[val] != 0)
            return (void *) 0;
        else
            col[val] = 1;
    }
    return (void *) 1;
}

/**
 * Checks if a square of size 3x3 contains all numbers from 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * check_square(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int saved[10] = {0};
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            int val = data->board[i][j];
            if (saved[val] != 0) {
                return (void *) 0;
            }
            else{
                saved[val] = 1;
            }
        }
    }
    return (void *) 1;
}