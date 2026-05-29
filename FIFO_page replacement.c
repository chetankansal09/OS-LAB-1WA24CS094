#include <stdio.h>

int main() {
    int pages[] = {4, 1, 2, 4, 5}, frames = 3;
    int n = sizeof(pages)/sizeof(pages[0]), temp[frames], faults = 0, pos = 0;

    for(int i = 0; i < frames; i++) temp[i] = -1; 

    for(int i = 0; i < n; i++) {
        int hit = 0;
        for(int j = 0; j < frames; j++) {
            if(temp[j] == pages[i]) hit = 1; 
        }

        if(!hit) {
            temp[pos] = pages[i];      
            pos = (pos + 1) % frames; 
            faults++;
        }
        
        printf("Page %d: [ %d %d %d ]\n", pages[i], temp[0], temp[1], temp[2]);
    }
    printf("\nTotal Page Faults: %d\n", faults);
    return 0;
}