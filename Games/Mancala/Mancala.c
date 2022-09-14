/**
 * Basic Mancala driver
 *
 * Author: Caleb Jacobs
 * Date last modified: 03/18/2021
 */

#include <stdio.h>
#include <stdlib.h>

#define S_LEN 6 // Size of one game board side

// Helper methods for running the game
int *initBoard();

int  makeMove(int *board, int player, int cup);
int  getPlayerIdx(int cup, int player);
void nextIdx(int *idx, int player);
int  getSide(int idx);
int  getEnemyIdx(int idx);

int  gameState(int *board);
void printBoard(int *board, int player);

/**
 * Driver for Mancala game and game board
 */
int main() {
    system("clear");

    int *board = initBoard();   // Initial game board
    int player = 1;             // Initial player

    // Begin playing the game
    while (gameState(board)) {
        int cup;
        int state = 1;
        while (state) {
            printBoard(board, player);                  // Display current board

            printf("Player %d, move cup: ", player);    // Prompt for playrs move
            scanf("%d", &cup);                          // Get players move

            state = makeMove(board, player, cup);       // Make players move
        }

        if (player == 1) {
            player = 2;
        } else {
            player = 1;
        }
    }

    printBoard(board, 0);

    free(board);
    return 0;
}

/**
 * Initialize game board array
 */
int *initBoard() {
    int *board = calloc(2 * (S_LEN + 1), sizeof(int));

    for (int i = 0; i < S_LEN; i++) {
        board[i] = 4;
        board[i + S_LEN + 1] = 4;
    }

    return board;
}

/**
 * Get player index
 */
int getPlayerIdx(int cup, int player) {
    return (player - 1) * (S_LEN + 1) + cup - 1;

}

/**
 * Get index of next cup to drop in
 */
void nextIdx(int *idx, int player) {
    (*idx)++;
    int forbidden;
    if (player == 1) {
        forbidden = getPlayerIdx(S_LEN + 1, 2);
    } else {
        forbidden = getPlayerIdx(S_LEN + 1, 1);
    }

    // Move index if index is enemy score area
    if (*idx == forbidden) {
        (*idx)++;
    }

    // Wrap index around if it is out of bounds
    if (*idx >= 2*(S_LEN + 1)) {
        (*idx) %= 2*(S_LEN + 1);
    }
}

/**
 * Get the side that the index is on
 */
int getSide(int idx) {
    if (0 <= idx && idx < S_LEN) {
        return 1;
    } else {
        return 2;
    }
}

/**
 * Get corresponding enemies index
 */
int getEnemyIdx(int idx) {
    return idx + 2*(S_LEN - idx);
}

/**
 * Make move on the board
 */
int makeMove(int *board, int player, int cup) {
    if (cup <= 0 || cup >= S_LEN + 1) {
        printf("Invalid move, try again!\n");
        return 1;
    }

    // Get index of cup in the array
    int idx = getPlayerIdx(cup, player);

    int hand = board[idx];  // Pickup the cup
    board[idx] = 0;         // Make sure the cup is empty

    // Players cup was empty
    if (hand == 0) {
        printf("Cup was empty, try again!\n");
        return 1;
    }

    // Distribute the hand among the board
    while (hand != 0) {
        nextIdx(&idx, player);
        board[idx]++;
        hand--;
    }

    // Take enemies cup if needed
    if (board[idx] == 1 && getSide(idx) == player) {
        int enemyIdx = getEnemyIdx(idx);
        board[getPlayerIdx(S_LEN + 1, player)] += board[enemyIdx];
        board[enemyIdx] = 0;
    }

    // Decide if player gets to go again
    if (idx == getPlayerIdx(S_LEN + 1, player)) {
        return 1;   // Return 1 if player plays again
    } else {
        return 0;   // Return 0 if player's turn is over
    }
}

/**
 * Check game state and finish the game if need be
 */
int gameState(int *board) {
    // Check player 1s side
    int sum = 0;
    for (int i = 0; i < S_LEN; i++) {
        sum += board[i];    // Add board entry
    }
    if (sum == 0) {
        printBoard(board, 0);   // Print current board before cleaning up

        // Clean player 2s side
        for (int i = 0; i < S_LEN; i++) {
            sum += board[S_LEN + 1 + i];
            board[S_LEN + 1 + i] = 0;
        }

        board[2 * S_LEN + 1] += sum;    // Add player 2s points up

        return 0;
    }

    // Check player 2s side
    sum = 0;
    for (int i = 0; i < S_LEN; i++) {
        sum += board[S_LEN + 1 + i];
    }
    if (sum == 0) {
        printBoard(board, 0);   // Print current board before cleaning up

        // Clean player 1s side
        for (int i = 0; i < S_LEN; i++) {
            sum += board[i];
            board[i] = 0;
        }

        board[S_LEN] += sum;    // Add player 1s points up

        return 0;
    }

    return 1;
}

// /**
//  * Print current game board
//  */
// void printBoard(int *board, int player) {
//     printf("\n   |");
// 
//     // Print player 2 in top row
//     for (int i = S_LEN - 1; i >= 0; i--) {
//         printf("%2d|", board[i + S_LEN + 1]);
//     }
// 
//     if (player == 2) {
//         printf("   <--");
//     }
// 
//     printf("\n|%-2d|", board[2 * S_LEN + 1]);
// 
//     for (int i = 1; i < S_LEN; i++) {
//         printf("--|");
//     }
// 
//     printf("--|%2d|\n   |", board[S_LEN]);
// 
//     for (int i = 0; i < S_LEN; i++) {
//         printf("%2d|", board[i]);
//     }
// 
//     if (player == 1) {
//         printf("   <--");
//     }
// 
//     printf("\n\n");
// }

/**
 * Print current game board
 */
void printBoard(int *board, int player) {
    printf("\n  ");

    // Print player 2 in top row
    for (int i = S_LEN - 1; i >= 0; i--) {
        printf("%2d ", board[i + S_LEN + 1]);
    }

    if (player == 2) {
        printf("   <--");
    }

    printf("\n%2d ", board[2 * S_LEN + 1]);

    for (int i = 1; i < S_LEN; i++) {
        printf("   ");
    }

    printf("  %-2d\n  ", board[S_LEN]);

    for (int i = 0; i < S_LEN; i++) {
        printf("%2d ", board[i]);
    }

    if (player == 1) {
        printf("   <--");
    }

    printf("\n\n");
}
