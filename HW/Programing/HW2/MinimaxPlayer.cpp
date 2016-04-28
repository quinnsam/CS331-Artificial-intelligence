/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"
#include <climits>
using std::vector;
using std::cout;
using std::endl;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::utility(){
    // To be filled in
}

OthelloBoard* MinimaxPlayer::successor(OthelloBoard* b){
    // Create successors
    int s = 0; // Successor counter
    OthelloBoard *n = new OthelloBoard(*b); // New board to add moves too
    //Rows
    for (int i = 0; i < 4; i++) {
        // Coloums
        for (int j = 0; j < 4; j++) {
            if (b->is_legal_move(i,j,symbol)) {
                // Create new board with legal moves
                n->play_move(i,j,symbol);
                s++;
            }
        }
    }
    cout << s + " Successors created" << endl;
    return n;


}

void MinimaxPlayer::minimaxDecision(OthelloBoard* b){
    // To be filled in
}

void MinimaxPlayer::maxValue(OthelloBoard* b) {
    int max = INT_MIN;
    int min_col = 0;
    int min_row = 0;


}

void MinimaxPlayer::minValue(OthelloBoard* b) {
    int min = INT_MAX;
    
    // Test if Terminal or not


    
}


void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you

}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
