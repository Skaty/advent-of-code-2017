#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

void parse_check(char* buffer, int* cur_min, int* cur_max, int size) {
    buffer[size] = '\0';
    int cur_num = atoi(buffer);
    *cur_min = min(*cur_min, cur_num);
    *cur_max = max(*cur_max, cur_num);
}


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    int i = 0, cur_row = 0, cur_min = INT_MAX, cur_max = INT_MIN;
    char c, buffer[10];
    long partials[20], checksum = 0;

    FILE *fp = fopen(argv[1], "r");

    while (!feof(fp)) {
        c = fgetc(fp);
        if (c == '\t') {
            parse_check(buffer, &cur_min, &cur_max, i);
            i = 0;
        } else if (c == '\n') {
            parse_check(buffer, &cur_min, &cur_max, i);
            partials[cur_row] = cur_max - cur_min;
            cur_min = INT_MAX;
            cur_max = INT_MIN;
            cur_row++;
            i = 0;
        } else {
            buffer[i] = c;
            i++;
        }
    }

    for (i = 0; i < cur_row; i++) {
        checksum += partials[i];
    }

    printf("Checksum: %ld\n", checksum);

    fclose(fp);
}