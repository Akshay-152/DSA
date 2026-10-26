
#include <stdio.h>

#define ROW 5
#define COL 5

struct Cell {
    int row, col;
};

void findDistance(int maze[ROW][COL],
                  int distance[ROW][COL]) {
    struct Cell queue[ROW * COL];
    int front = 0, rear = 0;
    int i, j, r, c, nr, nc;

    int rowMove[] = {-1, 1, 0, 0};
    int colMove[] = {0, 0, -1, 1};

    // Initialize distances and enqueue landmines
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            distance[i][j] = -1;

            if (maze[i][j] == 1) {
                distance[i][j] = 0;
                queue[rear].row = i;
                queue[rear].col = j;
                rear++;
            }
        }
    }

    // Breadth-First Search (BFS)
    while (front < rear) {
        r = queue[front].row;
        c = queue[front].col;
        front++;

        for (i = 0; i < 4; i++) {
            nr = r + rowMove[i];
            nc = c + colMove[i];

            if (nr >= 0 && nr < ROW &&
                nc >= 0 && nc < COL &&
                distance[nr][nc] == -1) {

                distance[nr][nc] = distance[r][c] + 1;

                queue[rear].row = nr;
                queue[rear].col = nc;
                rear++;
            }
        }
    }
}

void display(int matrix[ROW][COL]) {
    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++)
            printf("%3d", matrix[i][j]);
        printf("\n");
    }
}

int main() {
    int maze[ROW][COL] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    int distance[ROW][COL];

    printf("Input Maze:\n");
    display(maze);

    findDistance(maze, distance);

    printf("\nShortest Distance from Landmine:\n");
    display(distance);

    return 0;
}
