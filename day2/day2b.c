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

/**
 * Returns result if current number is divisible by any number in
 * nums.
 */
void parse_check(int* num_out, char* buffer, int* nums, int nums_size, int size) {
    buffer[size] = '\0';
    int i;
    int cur_num = atoi(buffer);
    nums[nums_size] = cur_num;
    for (i = 0; i < nums_size; i++) {
        if (cur_num % nums[i] == 0) {
            *num_out = cur_num / nums[i];
        } else if (nums[i] % cur_num == 0) {
            *num_out = nums[i] / cur_num;
        }
    }
}


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    int i = 0, num_count = 0, out_num = 0, nums[50];
    char c, buffer[10];
    long checksum = 0;

    FILE *fp = fopen(argv[1], "r");

    while (!feof(fp)) {
        c = fgetc(fp);
        if (c == '\t') {
            parse_check(&out_num, buffer, nums, num_count, i);
            num_count++;
            i = 0;
        } else if (c == '\n') {
            parse_check(&out_num, buffer, nums, num_count, i);
            checksum += out_num;
            num_count = 0;
            i = 0;
        } else {
            buffer[i] = c;
            i++;
        }
    }

    printf("Checksum: %ld\n", checksum);

    fclose(fp);
}