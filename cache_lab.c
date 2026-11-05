#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Cache Behavior Lab
 * 
 * This program demonstrates how memory access patterns affect performance.
 * You will implement two functions that perform identical computation
 * (summing all elements in a matrix) but traverse the data differently.
 */

// Global matrix and size for current test
int** matrix = NULL;
int current_size = 0;

/*
 * Allocates a square matrix of the given size.
 * Returns 1 on success, 0 on failure.
 */
int allocate_matrix(int size) {
    matrix = (int**)malloc(size * sizeof(int*));
    if (matrix == NULL) return 0;
    
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
        if (matrix[i] == NULL) return 0;
        
        // Initialize with values
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (i + j) % 100;
        }
    }
    current_size = size;
    return 1;
}

/*
 * Frees the matrix memory.
 */
void free_matrix() {
    if (matrix == NULL) return;
    
    for (int i = 0; i < current_size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
    current_size = 0;
}

/*
 * Traverses the matrix in ROW-MAJOR order.
 * Visits every element in row 0, then row 1, then row 2, etc.
 * Returns the sum of all elements.
 * 
 * TODO: Implement this function.
 * Hint: The outer loop should iterate over rows, the inner loop over columns.
 */
long long traverse_row_major() {
    long long sum = 0;
    
    // ============================================
    // TODO: Implement row-major traversal
    // Visit elements in order: [0][0], [0][1], [0][2], ... [1][0], [1][1], ...
    // ============================================
    for (int i = 0; i < current_size; i++) {
        for (int j = 0; j < current_size; j++) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

/*
 * Traverses the matrix in COLUMN-MAJOR order.
 * Visits every element in column 0, then column 1, then column 2, etc.
 * Returns the sum of all elements.
 * 
 * TODO: Implement this function.
 * Hint: The outer loop should iterate over columns, the inner loop over rows.
 */
long long traverse_column_major() {
    long long sum = 0;
    
    // ============================================
    // TODO: Implement column-major traversal
    // Visit elements in order: [0][0], [1][0], [2][0], ... [0][1], [1][1], ...
    // ============================================
    for (int j = 0; j < current_size; j++) {
        for (int i = 0; i < current_size; i++) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

/*
 * Measures execution time of a traversal function in milliseconds.
 */
double measure_time(long long (*traverse_func)(), long long* result) {
    clock_t start = clock();
    *result = traverse_func();
    clock_t end = clock();
    
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}

/*
 * Runs performance test for a given matrix size.
 */
void run_test(int size) {
    printf("\n--- Matrix Size: %d x %d ---\n", size, size);
    
    if (!allocate_matrix(size)) {
        printf("Failed to allocate matrix of size %d\n", size);
        return;
    }
    
    long long row_sum, col_sum;
    
    double row_time = measure_time(traverse_row_major, &row_sum);
    double col_time = measure_time(traverse_column_major, &col_sum);
    
    printf("Row-major:    %.2f ms (sum: %lld)\n", row_time, row_sum);
    printf("Column-major: %.2f ms (sum: %lld)\n", col_time, col_sum);
    
    if (row_time > 0) {
        printf("Ratio (col/row): %.2fx\n", col_time / row_time);
    }
    
    // Verify both methods produce the same result
    if (row_sum != col_sum) {
        printf("WARNING: Sums don't match! Check your implementations.\n");
    }
    
    free_matrix();
}

int main() {
    printf("Cache Behavior Lab\n");
    printf("==================\n");
    printf("Comparing row-major vs column-major matrix traversal\n");
    
    // Test with increasing matrix sizes
    int sizes[] = {1000, 2000, 4000, 8000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        run_test(sizes[i]);
    }
    
    printf("\n==================\n");
    printf("Tests complete.\n");
    
    return 0;
}