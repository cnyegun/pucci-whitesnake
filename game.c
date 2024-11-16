#include "def.h"
#include "raylib.h"

int main(void) {
    // Initialize game property
    Direction direction = RIGHT; 
    SnakeSegment* head = {NULL};
    growSnake(&head, 1, 4);
    growSnake(&head, 2, 4);
    growSnake(&head, 3, 4);
    displaySnake(head);
}