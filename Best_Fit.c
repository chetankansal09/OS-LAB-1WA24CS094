#include <stdio.h>

int main() {
    int b[20], p[20], b_idx[20], frag[20], nb, np, i, j;
    int allocated[20] = {0};

    printf("Enter nb and np: ");
    scanf("%d %d", &nb, &np);

    printf("Enter block sizes: ");
    for (i = 0; i < nb; i++) scanf("%d", &b[i]);

    printf("Enter process sizes: ");
    for (i = 0; i < np; i++) scanf("%d", &p[i]);

    for (i = 0; i < np; i++) {
        int best_idx = -1;
        for (j = 0; j < nb; j++) {
            if (!allocated[j] && b[j] >= p[i]) {
                // Key change: find the smallest suitable block
                if (best_idx == -1 || b[j] < b[best_idx])
                    best_idx = j;
            }
        }
        if ((b_idx[i] = best_idx + 1) > 0) {
            allocated[best_idx] = 1;
            frag[i] = b[best_idx] - p[i];
        }
    }

    printf("\nP_Size\tBlock\tFragment\n");
    for (i = 0; i < np; i++)
        if (b_idx[i]) printf("%d\t%d\t%d\n", p[i], b_idx[i], frag[i]);
        else printf("%d\tN/A\tN/A\n", p[i]);

    return 0;
}