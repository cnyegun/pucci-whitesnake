#include "def.h"

int main(void) {
    // Initialize game property
    Direction direction = RIGHT; 
    SnakeSegment* head = {NULL};
    Apple apple = {rand() % (20 + 1), rand() % (20 + 1)};
    int score = 0;

    growSnake(&head, 1, 4);
    growSnake(&head, 2, 4);

    // Initialize game window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pucci Whitesnake");
    SetTargetFPS(10);

    // Main game loop
    while (!WindowShouldClose()) {
        // Game state update 
        advanceSnake(&head, direction, &apple, &score);
        changeDirection(&direction);
        displayApple(apple);
        //TODO: handle collison with itself and the wall
        //TODO: start game and game over

        BeginDrawing();
            ClearBackground(BLACK);
            drawSnake(head);
            DrawText(TextFormat("Score: %d", score), 20, 750, 35, GREEN);
        EndDrawing();
    }

    CloseWindow();

    // Free memory
    while (head != NULL) {
        removeTail(&head);
    }
    return 0;
}