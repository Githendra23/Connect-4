#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // this library doesnt exist on linux

char column[43] = {'o', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                   'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                   'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'};

char playerTokenPlacement[43] = {'o', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                                 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
                                 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}; // save the placement of the player's token

void board();
void checkwin();

const int numberOfslotsInOneRow = 7;
const int yes = 1;   // making the code readable
const int no  = 0;   // making the code readable
const int firstSlot = 1;
const int lastSlot = 42;

int shouldGameContinue = yes;
int player = 1;
int isDraw = no;

int main() {
    const int firstSlotRow = firstSlot;

    board();
    while(shouldGameContinue == yes) {
        int choice;
        int infiniteLoop = yes;
        int playersTurn = ((player % 2) == 0) ? 2 : 1;

        while(infiniteLoop == yes) {
            int shouldSkip = no;  
            printf("\nplayer %d enter a number: ", playersTurn);
            scanf("%d", &choice);

/* ---------- verifying player's answer ---------- */
            for(int slotRow = firstSlotRow; slotRow <= numberOfslotsInOneRow + 1; slotRow++) {
                if(slotRow == numberOfslotsInOneRow + 1) {
                    board();
                    printf("\nType a number between 1 and 7\n");
                    shouldSkip = yes;
                    break;
                }
                else {
                    if(choice == slotRow) {
                        if(column[slotRow + (7 * 0)] != 'O' && column[slotRow + (7 * 1)] != 'O' && column[slotRow + (7 * 2)] != 'O' && column[slotRow + (7 * 3)] != 'O' &&
                           column[slotRow + (7 * 4)] != 'O' && column[slotRow + (7 * 5)] != 'O' && column[slotRow + (7 * 6)] != 'O') { // if a column is all filled
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
                for(int i = firstSlotRow; i <= numberOfslotsInOneRow; i++) {
                    if(choice == i) {
                        int slot = i + 35; // bottom slot

                        for(int j = 1; j <= 6; j++) {
                            if(column[slot] == 'O') {
                                column[slot] = '0';

                                if(playersTurn == 1) playerTokenPlacement[slot] = '1';
                                else playerTokenPlacement[slot] = '2';

                                infiniteLoop = no;
                                break;
                            }
                            else {
                                slot -= numberOfslotsInOneRow; // going from the bottom slot to the top in the same column
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
    if(isDraw == yes) {
        printf("\nIt's a draw !\n");
    }
    else {
        printf("\nPlayer %d is the winner !\n", ((player % 2) != 0) ? 2 : 1); // != because of line 86
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

void checkwin() {
    int checkAnswer = ((player % 2) == 0) ? '2' : '1';
    int token;

    for(token = firstSlot; token <= 21; token++) { // vertical
        if((playerTokenPlacement[token + (7 * 0)] == checkAnswer && playerTokenPlacement[token + (7 * 1)] == checkAnswer  && 
            playerTokenPlacement[token + (7 * 2)] == checkAnswer && playerTokenPlacement[token + (7 * 3)] == checkAnswer)) {
                shouldGameContinue = no;
                return;
        }
    }

    for(token = firstSlot; token <= 39; token++) { // horizontal
        if((token >= 5 && token <= 8) || (token >= 12 && token <= 14) || (token >= 19 && token <= 21) ||
           (token >= 26 && token <= 28) || (token >= 33 && token <= 34)) {} // skip these numbers 
        else {
            if((playerTokenPlacement[token + 0] == checkAnswer && playerTokenPlacement[token + 1] == checkAnswer  && 
                playerTokenPlacement[token + 2] == checkAnswer && playerTokenPlacement[token + 3] == checkAnswer)) {
                shouldGameContinue = no;
                return;
            }
        }
    }

    for(token = firstSlot; token <= 18; token++) { // diagonal left
        if(token == 2 || (token >= 5 && token <= 7) || token == 10 || (token >= 12 && token <= 14)) {} // skip these numbers 
        else {
            if((playerTokenPlacement[token + (8 * 0)] == checkAnswer && playerTokenPlacement[token + (8 * 1)] == checkAnswer  && 
                playerTokenPlacement[token + (8 * 2)] == checkAnswer && playerTokenPlacement[token + (8 * 3)] == checkAnswer)) {
                    shouldGameContinue = no;
                    return;
            }
        }
    }

    for(token = 4; token <= 21; token++) { // diagonal right
        if((token >= 8 && token <= 10) || (token >= 15 && token <= 17)) {} // skip these numbers 
        else {
            if((playerTokenPlacement[token + (6 * 0)] == checkAnswer && playerTokenPlacement[token + (6 * 1)] == checkAnswer  && 
                playerTokenPlacement[token + (6 * 2)] == checkAnswer && playerTokenPlacement[token + (6 * 3)] == checkAnswer)) {
                    shouldGameContinue = no;
                    return;
            }
        }
    }

    int count = 0;
    for(token = firstSlot; token <= lastSlot; token++) {
        if(column[token] != 'O') count++;
        if(count >= lastSlot) {
            
            isDraw = yes;
            shouldGameContinue = no;
            return;
        }
    }
}