#include <stdio.h>

#define MAX 10

// Function prototypes
void displayMatrix(int matrix[MAX][MAX], int row, int col);
void transposeMatrix(int matrix[MAX][MAX], int r, int c);

int main() {
    int matrix[MAX][MAX], row, col;

    printf("Enter rows and columns for the matrix: ");
    scanf("%d %d", &row, &col);

    printf("\nEnter elements of the matrix:\n");
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("Enter element a%d%d: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\n--- Original Matrix ---\n");
    displayMatrix(matrix, row, col);

    printf("\n--- Transposed Matrix ---\n");
    transposeMatrix(matrix, row, col);

    return 0;
}

void displayMatrix(int matrix[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void transposeMatrix(int matrix[MAX][MAX], int r, int c) {
    int transpose[MAX][MAX];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }
    // Note: Dimensions flip to c x r for the transpose
    displayMatrix(transpose, c, r);
}