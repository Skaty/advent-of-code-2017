#include <stdio.h>
#include <stdlib.h>

int calc_around(int** squares, int x, int y, int target) {
    const int x_diff[] = {0, 1, 1, 0, -1, -1, 1, -1};
    const int y_diff[] = {1, 0, 1, -1, 0, -1, -1, 1};
    int i, total = 0;

    for (i = 0; i < 8; i++) {
        int new_x = x + x_diff[i];
        int new_y = y + y_diff[i];

        if (new_x >= 0 && new_x < 101 && new_y >= 0 && new_y < 101) {
            if (x == 51 && y == 49) {
            }
            if (squares[new_y][new_x] != -1) {
                total += squares[new_y][new_x];
            }
        }
    }

    if (total >= target) {
        printf("Target found: %d\n", total);
        exit(0);
    }

    return total;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return -1;
    }

    int puzzle_input = atoi(argv[1]);
    int i;

    int** squares = (int**)malloc(sizeof(int*) * 101);

    for (i = 0; i < 101; i++) {
        squares[i] = (int*)malloc(sizeof(int) * 101);
        int j;
        for (j = 0; j < 101; j++) {
            squares[i][j] = -1;
        }
    }

    int side = 3, remaining = 1, cur_side = 0;
    const int x_diff[] = {0, -1, 0, 1};
    const int y_diff[] = {-1, 0, 1, 0};
    squares[50][50] = 1;
    int cur_x = 50, cur_y = 50;

    while (cur_x < 101) {
        // before cur square
        cur_x++;
        squares[cur_y][cur_x] = calc_around(squares, cur_x, cur_y, puzzle_input);
        while (cur_side < 4) {
            while (remaining > 0) {
                cur_x += x_diff[cur_side];
                cur_y += y_diff[cur_side];
                squares[cur_y][cur_x] = calc_around(squares, cur_x, cur_y, puzzle_input);
                remaining--;
            }
            remaining = side - 1;
            cur_side++;
        }
        remaining = side;
        side += 2;
        cur_side = 0;
    }


    for (i = 0; i < 100; i++) {
        free(squares[i]);
    }

    free(squares);
}