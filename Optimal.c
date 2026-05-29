#include <stdio.h>

int main() {
    int pages[] = {4, 1, 2, 4, 5}, frames = 3, n = 5;
    int temp[] = {-1, -1, -1}, faults = 0;

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == pages[i]) hit = 1;
        }

        if (!hit) {
            int pos = -1, farthest = i;
            for (int j = 0; j < frames; j++) {
                if (temp[j] == -1) { pos = j; break; }
                int k;
                for (k = i + 1; k < n; k++) {
                    if (temp[j] == pages[k]) break;
                }
                if (k > farthest) { farthest = k; pos = j; }
            }
            temp[pos] = pages[i];
            faults++;
        }
        printf("Page %d: [ %d %d %d ]\n", pages[i], temp[0], temp[1], temp[2]);
    }
    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}