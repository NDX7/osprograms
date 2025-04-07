#include <stdio.h>

int i, j, n, p[50], f;

int lru();

int main() {
    int pf;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    
    pf = lru();
    
    printf("\n\nPage faults: %d\n", pf);
    return 0;
}

int lru() {
    int q[20], c = 0, k = 0, c1, r, t, b[20], c2[20];
    printf("\nLeast Recently Used\n");
    
    // Initialize the frame array
    for (i = 0; i < f; i++)
        q[i] = -1;

    // Process the reference string
    for (i = 0; i < n; i++) {
        c1 = 0;
        for (j = 0; j < f; j++) {
            if (p[i] == q[j]) {
                c1++;
                break; // Page is already in the frame
            }
        }
        
        // If the page is not found in the frame
        if (c1 == 0) {
            c++; // Increment page fault count
            if (k < f) {
                // If there is space in the frame
                q[k] = p[i];
                k++;
            } else {
                // Find the least recently used page
                int lru_index = 0;
                for (r = 0; r < f; r++) {
                    c2[r] = 0;
                    for (j = i - 1; j >= 0; j--) {
                        if (q[r] != p[j]) {
                            c2[r]++;
                        } else {
                            break; // Found the page
                        }
                    }
                }
                
                // Find the page with the maximum count in c2
                for (r = 0; r < f; r++) {
                    if (c2[r] > c2[lru_index]) {
                        lru_index = r;
                    }
                }
                
                // Replace the least recently used page
                q[lru_index] = p[i];
            }
        }

        // Print the current state of the frames
        printf("\n");
        for (j = 0; j < f; j++) {
            if (q[j] == -1)
                printf("-\t");
            else
                printf("%d\t", q[j]);
        }
    }
    return c; // Return the number of page faults
}
