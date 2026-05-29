#include <stdio.h>

int main() {
    int pages[] = {4, 1, 2, 4, 5}, frames = 3, n = 5;
    int temp[] = {-1, -1, -1}, recent[3], faults = 0;

    for(int i = 0; i < n; i++) {
        int hit = -1;
        for(int j = 0; j < frames; j++) {
            if(temp[j] == pages[i]) hit = j;
        }

        if(hit != -1) {
            recent[hit] = i;
        } else {
            int pos = (i < frames) ? i : 0;
            if(i >= frames) {
                for(int j = 1; j < frames; j++) {
                    if(recent[j] < recent[pos]) pos = j;
                }
            }
            temp[pos] = pages[i];
            recent[pos] = i;
            faults++;
        }
        printf("Page %d: [ %d %d %d ]\n", pages[i], temp[0], temp[1], temp[2]);
    }
    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}