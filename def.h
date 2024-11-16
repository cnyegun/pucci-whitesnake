#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ===================
// DATA DEFINITIONS:
// Direction is one of:
//  - UP
//  - RIGHT
//  - DOWN
//  - LEFT
// interp. direction of the snake movement
typedef enum Direction {
	UP, RIGHT, DOWN, LEFT,
} Direction;
// SnakeSegment is:
//  - pos x, y
//  - next SnakeSegment
// interp. a linked list of SnakeSegment represent the snake body, x and y is the SnakeSegment position on the grid
typedef struct SnakeSegment {
	int x, y;
	struct SnakeSegment* next;
} SnakeSegment;
// Cell is one of:
//  - EMPTY
//  - FOOD
// interp. a cell from the game board 
typedef enum Cell {
	EMPTY,
	FOOD,
} Cell;
// ===================
// CONSTANT DEFINITIONS:
// Game board WIDTH * LENGTH
Cell GAME_BOARD[20][20] = {EMPTY};
// ===================
// FUNCTION DEFINITION
// Add a body segment to Snake (literally linked)
void growSnake(SnakeSegment** head, int pos_x, int pos_y) {
    SnakeSegment* newSnake = malloc(sizeof(SnakeSegment)); 
    if (newSnake == NULL) {
		printf("Memory allocation failed\n");
        return;
    }
    newSnake->x = pos_x;
    newSnake->y = pos_y;
    newSnake->next = *head;  
    *head = newSnake;        
}
// Display the snake to sdtout (test)
void displaySnake(SnakeSegment* head) {
	if (head == NULL) {
		return;
	}
	while (head != NULL) {
		printf("{%d,%d}", head->x,head->y);
		head = head->next;
	}
	printf("\n");
}
// Delete snake tail
void removeTail(SnakeSegment** head) {
	SnakeSegment* temp = (*head);
	// EDGE CASE: (1) Snake is empty
	if (temp == NULL) {
		return;
	}
	// EDGE CASE: (2) Single segment
	if (temp->next == NULL) {
		free(temp);
		*head = NULL;
		return;
	}
	while (temp != NULL) {
		if (temp->next->next == NULL) {
			free(temp->next);
			temp->next = NULL;
			return;
		}
		temp = temp->next;
	}
}