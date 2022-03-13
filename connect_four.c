#include <stdio.h>

char column[43] = {'o', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                   'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                   'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'};

char playerTokenPlacement[43] = {'o', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                       'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}; // save the placement of the player's token

void board();
int checkwin();

const int numberOfslotsInOneRow = 7;
const int yes = 1;   // making the code readable
const int no  = 0;   // making the code readable
const int firstSlot = 1;
const int lastSlot = 42;

int shouldGameContinue = yes;
int player = 1;

int main() {
    const int firstSlotRow = 1;

    board();
    while(shouldGameContinue == yes) {
        int choice;
        int infiniteLoop = yes;
        int playersTurn = ((player % 2) == 0) ? 2 : 1;

        while(infiniteLoop == yes) {
            int shouldSkip = no;  
            printf("\nplayer %d enter a number: ", playersTurn);
            scanf("%d", &choice);
            getchar();

/* ---------- verifying player's answer ---------- */
            for(int x = firstSlotRow; x <= numberOfslotsInOneRow + 1; x++) {
                if(x == 8) {
                    board();
                    printf("\nType a number between 1 and 7\n");
                    shouldSkip = yes;
                    break;
                }
                else {
                    if(choice == x) {
                        if(column[x + (7 * 0)] != 'O' && column[x + (7 * 1)] != 'O' && column[x + (7 * 2)] != 'O' && column[x + (7 * 3)] != 'O' &&
                           column[x + (7 * 4)] != 'O' && column[x + (7 * 5)] != 'O' && column[x + (7 * 6)] != 'O') { // if a column is all filled
                            board();
                            printf("\nthose slots are full, pick another slot\n");
                            shouldSkip = yes;
                            break;
                        }
                        else break;
                    }
                }
            }

/* ---------- logic of the game ---------- */
            if(shouldSkip == no) {
                for(int x = firstSlotRow; x <= numberOfslotsInOneRow; x++) {
                    if(choice == x) {
                        int slot = x + 35; // bottom slot

                        for(int y = 1; y <= 6; y++) {
                            if(column[slot] == 'O') {
                                column[slot] = '0';

                                if(playersTurn == 1) playerTokenPlacement[slot] = '1';
                                else playerTokenPlacement[slot] = '2';

                                infiniteLoop = no;
                                break;
                            }
                            else {
                                slot -= numberOfslotsInOneRow; // going from bottom slot to top in the same column
                            }
                        } 
                    }
                }
                board();
                checkwin();
                player++;
            }
        }
    }
    printf("\nPress Any Key to Exit...\n");  
    getch();
}

void board() {
    system("cls"); // clear terminal
    printf("\n\n                     Connect 4\n\n");
    printf("\033[0mplayer 1: \033[1;31m0                             \033[0mplayer 2: \033[0;34m0\n\n");
    printf("             \033[0;33m1   2   3   4   5   6   7\n");
    printf("           ");

    for(int slot = firstSlot; slot <= lastSlot; slot++) {
        printf("\033[0m|");
        if(playerTokenPlacement[slot] == '1') printf(" \033[1;31m%c ",column[slot]);
        else if(playerTokenPlacement[slot] == '2') printf(" \033[0;34m%c ",column[slot]);  
        else printf(" \033[0m%c ",column[slot]);

        if((slot % numberOfslotsInOneRow) == 0) {
            printf("\033[0m|\n");
            printf("           ");
        }
    }
}

int checkwin() {
    int playersTurn = ((player % 2) == 0) ? 2 : 1;
    int token;

    for(token = 1; token <= 21; token++) { // vertical
        if((playerTokenPlacement[token + (7 * 0)] == '1' && playerTokenPlacement[token + (7 * 1)] == '1'  && 
            playerTokenPlacement[token + (7 * 2)] == '1' && playerTokenPlacement[token + (7 * 3)] == '1') ||
           (playerTokenPlacement[token + (7 * 0)] == '2' && playerTokenPlacement[token + (7 * 1)] == '2'  && 
            playerTokenPlacement[token + (7 * 2)] == '2' && playerTokenPlacement[token + (7 * 3)] == '2')) {
                printf("\nPlayer %d is the winner !\n", playersTurn);
                shouldGameContinue = no;
                break;
        }
    }

    for(token = 1; token <= 39; token++) { // horizontal
        if((token >= 5 && token <= 8) || (token >= 12 && token <= 14) || (token >= 19 && token <= 21) ||
           (token >= 26 && token <= 28) || (token >= 33 && token <= 34)) {}
        else {
            if((playerTokenPlacement[token + 0] == '1' && playerTokenPlacement[token + 1] == '1'  && 
                playerTokenPlacement[token + 2] == '1' && playerTokenPlacement[token + 3] == '1') ||
               (playerTokenPlacement[token + 0] == '2' && playerTokenPlacement[token + 1] == '2'  && 
                playerTokenPlacement[token + 2] == '2' && playerTokenPlacement[token + 3] == '2')) {
                printf("\nPlayer %d is the winner !\n", playersTurn);
                shouldGameContinue = no;
                break;
            }
        }
    }

    for(token = 1; token <= 18; token++) { // diagonal left
        if(token == 2 || (token >= 5 && token <= 7) || token == 10 || (token >= 12 && token <= 14)) {}
        else {
            if((playerTokenPlacement[token + (8 * 0)] == '1' && playerTokenPlacement[token + (8 * 1)] == '1'  && 
                playerTokenPlacement[token + (8 * 2)] == '1' && playerTokenPlacement[token + (8 * 3)] == '1') ||
               (playerTokenPlacement[token + (8 * 0)] == '2' && playerTokenPlacement[token + (8 * 1)] == '2'  && 
                playerTokenPlacement[token + (8 * 2)] == '2' && playerTokenPlacement[token + (8 * 3)] == '2')) {
                    printf("\nPlayer %d is the winner !\n", playersTurn);
                    shouldGameContinue = no;
                    break;
            }
        }
    }

    for(token = 4; token <= 21; token++) { // diagonal right
        if((token >= 8 && token <= 10) || (token >= 15 && token <= 17)) {}
        else {
            if((playerTokenPlacement[token + (6 * 0)] == '1' && playerTokenPlacement[token + (6 * 1)] == '1'  && 
                playerTokenPlacement[token + (6 * 2)] == '1' && playerTokenPlacement[token + (6 * 3)] == '1') ||
               (playerTokenPlacement[token + (6 * 0)] == '2' && playerTokenPlacement[token + (6 * 1)] == '2'  && 
                playerTokenPlacement[token + (6 * 2)] == '2' && playerTokenPlacement[token + (6 * 3)] == '2')) {
                    printf("\nPlayer %d is the winner !\n", playersTurn);
                    shouldGameContinue = no;
                    break;
            }
        }
    }

    int count = 0;
    for(token = firstSlot; token <= lastSlot; token++) {
        if(column[token] != 'O') count++;
        if(count >= lastSlot) {
            printf("\nIt's a draw !\n");
            shouldGameContinue = no;
        }
    }
}