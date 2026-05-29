#include <stdio.h>

int main() {
    int b[20], p[20], b_idx[20], frag[20], nb, np, i, j;
    int allocated[20] = {0};

    printf("--- Memory Management: Worst-Fit Allocation ---\n");
    printf("Enter number of blocks (max 20): ");
    scanf("%d", &nb);
    printf("Enter number of processes (max 20): ");
    scanf("%d", &np);

    // Basic Input Validation
    if (nb > 20 || np > 20) {
        printf("Error: Maximum size exceeded.\n");
        return 1;
    }

    printf("Enter sizes of %d blocks: ", nb);
    for (i = 0; i < nb; i++) scanf("%d", &b[i]);

    printf("Enter sizes of %d processes: ", np);
    for (i = 0; i < np; i++) scanf("%d", &p[i]);

    // Allocation Logic
    for (i = 0; i < np; i++) {
        int best_idx = -1;
        for (j = 0; j < nb; j++) {
            // If block is not taken and is large enough
            if (!allocated[j] && b[j] >= p[i]) {
                // "Worst-Fit" logic: find the LARGEST possible block
                if (best_idx == -1 || b[j] > b[best_idx]) {
                    best_idx = j;
                }
            }
        }

        if (best_idx != -1) {
            allocated[best_idx] = 1; // Mark block as used
            b_idx[i] = best_idx + 1; // Store 1-based index for output
            frag[i] = b[best_idx] - p[i]; // Calculate leftover space
        } else {
            b_idx[i] = 0; // Flag for unallocated
        }
    }

    // Output Table
    printf("\nProcess\tP_Size\tBlock\tFragment\n");
    for (i = 0; i < np; i++) {
        printf("%d\t%d\t", i + 1, p[i]);
        if (b_idx[i] != 0) {
            printf("%d\t%d\n", b_idx[i], frag[i]);
        } else {
            printf("N/A\tN/A (Insufficient Memory)\n");
        }
    }

    return 0;
}