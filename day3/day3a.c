#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return -1;
    }

    int puzzle_input = atoi(argv[1]);

    // Find out side length from
    // "nearest (ceiling) bottom-right corner"
    int side = 1, bottom_right = 1;

    while (bottom_right < puzzle_input) {
        side += 2;
        bottom_right += (side - 1) * 4;
    }

    int nearest_corner = bottom_right;

    // find a corner that is slightly above
    // our current position
    while (puzzle_input < (nearest_corner - (side - 1))) {
        nearest_corner -= side - 1;
    }

    // find the "midpoint" (easily)
    int side_midpoint = nearest_corner - (side/2);
    int distance = (puzzle_input - side_midpoint) + (side / 2);

    printf("Midpoint: %d\nNearest corner: %d\nDistance (to center): %d\n", side_midpoint, nearest_corner, distance);
}