#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    int i, size, half_size, sum = 0, sum_halfway = 0;

    FILE *f_numbers = fopen(argv[1], "r");
    fseek(f_numbers, 0, SEEK_END);
    size = ftell(f_numbers);
    half_size = size / 2;
    fseek(f_numbers, 0, SEEK_SET);

    char* raw_numbers = (char*)malloc(sizeof(char) * (size + 1));

    printf("Size: %d\n", size);
    fgets(raw_numbers, size + 1, f_numbers);

    for (i = 0; i < size; i++) {
        int next_i = (i + 1) % size;
        int halfway_i = (i + half_size) % size;
        if (raw_numbers[i] == raw_numbers[next_i]) {
            sum += raw_numbers[i] - '0';
        }

        if (raw_numbers[i] == raw_numbers[halfway_i]) {
            sum_halfway += raw_numbers[i] - '0';
        }
    }

    printf("Sum (next): %d\n", sum);
    printf("Sum (halfway): %d\n", sum_halfway);

    fclose(f_numbers);
    free(raw_numbers);
}