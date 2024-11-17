#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

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
// GameState is one of:
//  - MAIN_MENU
//  - GAMEPLAY
//  - DEAD_SCREEN
// interp. depend on this gamestate, draw accordingly
typedef enum GameState {
	MAIN_MENU, GAMEPLAY, DEAD_SCREEN,
} GameState;
// SnakeSegment is:
//  - pos x, y
//  - next SnakeSegment
// interp. a linked list of SnakeSegment represent the snake body, x and y is the SnakeSegment position on the grid
typedef struct SnakeSegment {
	int x, y;
	struct SnakeSegment* next;
} SnakeSegment;
// Apple is:
//  - pos x, y
// interp. a Apple with its x and y position
typedef struct Apple {
	int x, y;
} Apple;
// ===================
// CONSTANT DEFINITIONS:
const int DRAW_MULTIPLIER = 20;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
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
void printSnake(SnakeSegment* head) {
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

// Draw the snake on the Window
void drawSnake(SnakeSegment* head) {
	if (head == NULL) {
		return;
	}
	while (head != NULL) {
		DrawRectangle(
			head->x * DRAW_MULTIPLIER,
			head->y * DRAW_MULTIPLIER,
			DRAW_MULTIPLIER,
			DRAW_MULTIPLIER,
			RAYWHITE
		);
		head = head->next;
	}
} 

// Make the snake move based on the Direction
void advanceSnake(SnakeSegment** head, Direction direction, Apple* apple, int* score) {
	switch (direction) {
	case UP:
		growSnake(head, (*head)->x, (*head)->y - 1);
		if ((*head)->y == apple->y && (*head)->x == apple->x) {
    		apple->x = rand() % 20; 
			apple->y = rand() % 20;
			*score += 1;
			return;
		}
		break;
	case RIGHT:
		growSnake(head, (*head)->x + 1, (*head)->y);
		if ((*head)->y == apple->y && (*head)->x == apple->x) {
    		apple->x = rand() % 20; 
			apple->y = rand() % 20;
			*score += 1;
			return;
		}
		break;
	case DOWN:
		growSnake(head, (*head)->x, (*head)->y + 1);
		if ((*head)->y == apple->y && (*head)->x == apple->x) {
    		apple->x = rand() % 20; 
			apple->y = rand() % 20;
			*score += 1;
			return;
		}
		break;
	case LEFT:
		growSnake(head, (*head)->x - 1, (*head)->y);
		if ((*head)->y == apple->y && (*head)->x == apple->x) {
    		apple->x = rand() % 20; 
			apple->y = rand() % 20;
			*score += 1;
			return;
		}
		break;
	default:
		break;
	}

	removeTail(head);
}

// Change direction of &direction if the right key is pressed
void changeDirection(Direction* direction) {
	if (IsKeyDown(KEY_UP) && *direction != DOWN) *direction = UP;
	else if (IsKeyDown(KEY_RIGHT) && *direction != LEFT) *direction = RIGHT;
	else if (IsKeyDown(KEY_DOWN) && *direction != UP) *direction = DOWN; 
	else if (IsKeyDown(KEY_LEFT) && *direction != RIGHT) *direction = LEFT; 
	else return;
}

void displayApple(Apple apple) {
	DrawRectangle(
		apple.x * DRAW_MULTIPLIER,
		apple.y * DRAW_MULTIPLIER,
		DRAW_MULTIPLIER,
		DRAW_MULTIPLIER,
		RED
		);
}

// Display "You Died" in the middle of the screen 
void displayYouDied() {
	int textWidth = MeasureText("YOU DIED", 50);
	DrawText("YOU DIED", (SCREEN_WIDTH/2) - (textWidth/2), (SCREEN_HEIGHT/2) - 50, 50, RED);
}

// *head GameState -> GameState 
// return if the *head is collide with the wall OR collide with itself
GameState CollideHandler(SnakeSegment* head, GameState gamestate) {
	// Wall collide handler
	if ((head->x < 0) ||
		(head->y < 0) ||
		(head->x >= (SCREEN_WIDTH/DRAW_MULTIPLIER)) ||
		(head->y >= SCREEN_HEIGHT/DRAW_MULTIPLIER)) {
		return DEAD_SCREEN;
	}
	int head_x = head->x;
	int head_y = head->y;
	head = head->next;

	while (head != NULL) {
		if (head->x == head_x && head->y == head_y) {
			return DEAD_SCREEN;
		}
		head = head->next;
	}
	return GAMEPLAY;
}
