#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // this library doesnt exist on linux

char column[43];

char playerTokenPlacement[43]; // save the placement of the player's token

void board();
void checkwin();

const int numberOfslotsInOneRow = 7;
const int yes = 1;
const int no  = 0;
const int firstSlot = 1;
const int lastSlot = 42;

int shouldGameContinue = yes;
int player = 1;
int isDraw = no;

int main() {
    const int firstSlotRow = firstSlot;

    for(int i = 0; i < 43; i++) {
        column[i] = 'O';
        playerTokenPlacement[i] = 'O';
    }

    board();
    while(shouldGameContinue == yes) {
        int choice;
        int infiniteLoop = yes;
        int playersTurn = ((player % 2) == 0) ? 2 : 1;

        while(infiniteLoop == yes) {
            int shouldSkip = no;  
            printf("\nplayer %d enter a number: ", playersTurn);
            choice = getche() - 48;

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
                        if(column[slotRow + (7 * 0)] != 'O') { // if the first slot is full it means that the whole column is full
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
                                playerTokenPlacement[slot] = ((player % 2) == 0) ? '2' : '1';
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
        printf("\nPlayer %d is the winner !\n", ((player % 2) != 0) ? 2 : 1);
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
        if((token >= 1 && token <= 4) || (token >= 8 && token <= 11) || (token >= 15 && token <= 18) ||
           (token >= 22 && token <= 32) || (token >= 36 && token <= 39)) {
            if((playerTokenPlacement[token + 0] == checkAnswer && playerTokenPlacement[token + 1] == checkAnswer  && 
                playerTokenPlacement[token + 2] == checkAnswer && playerTokenPlacement[token + 3] == checkAnswer)) {
                    shouldGameContinue = no;
                    return;
            }
        } // skip these numbers 
    }

    for(token = firstSlot; token <= 18; token++) { // diagonal left
        if((token >= 1 && token <= 4) || (token >= 8 && token <= 11) || (token >= 15 && token <= 18)) {
            if((playerTokenPlacement[token + (8 * 0)] == checkAnswer && playerTokenPlacement[token + (8 * 1)] == checkAnswer  && 
                playerTokenPlacement[token + (8 * 2)] == checkAnswer && playerTokenPlacement[token + (8 * 3)] == checkAnswer)) {
                    shouldGameContinue = no;
                    return;
            }
        } // skip these numbers 
    }

    for(token = 4; token <= 21; token++) { // diagonal right
        if((token >= 4 && token <= 7) || (token >= 11 && token <= 14) || (token >= 18 && token <= 21)) {
            if((playerTokenPlacement[token + (6 * 0)] == checkAnswer && playerTokenPlacement[token + (6 * 1)] == checkAnswer  && 
                playerTokenPlacement[token + (6 * 2)] == checkAnswer && playerTokenPlacement[token + (6 * 3)] == checkAnswer)) {
                    shouldGameContinue = no;
                    return;
            }
        } // skip these numbers 
    }

    int topSlots = 0;
    for(token = firstSlot; token <= numberOfslotsInOneRow; token++) {
        if(column[token] != 'O') topSlots++;
        if(topSlots == numberOfslotsInOneRow) {  
            isDraw = yes;
            shouldGameContinue = no;
            return;
        }
    }
}
