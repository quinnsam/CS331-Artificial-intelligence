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

int MinimaxPlayer::utility(OthelloBoard* b){
    // To be filled in
    return b->count_score(b->get_p1_symbol()) - b->count_score(b->get_p2_symbol());
}

vector<OthelloBoard*> MinimaxPlayer::successor(OthelloBoard* b, char symb){
    vector<OthelloBoard*> v;
    // Create successors
    int s = 0; // Successor counter
    OthelloBoard *n = new OthelloBoard(*b); // New board to add moves too
    // Coloums
    for (int i = 0; i < 4; i++) {
        //Rows
        for (int j = 0; j < 4; j++) {
            if (b->is_legal_move(i,j,symb)) {
                // Create new board with legal moves
                v.push_back(new OthelloBoard(*b));
                v.back()->play_move(i,j,symb);
                v.back()->set_row(j);
                v.back()->set_col(i);
                s++;
            }
        }
    }
    cout << "Successors created: " << s << endl;
    return v;


}

void MinimaxPlayer::minimaxDecision(OthelloBoard* b, int& col, int& row){
    // To be filled in
    if (b->get_p1_symbol() == symbol) {
        cout << "Max: " << maxValue(b, col, row) << endl;
    } else {
        cout << " Min: " << minValue(b, col, row) << endl;
    }
    cout << "Col=" << col << " Row=" << row << endl;
}

int MinimaxPlayer::maxValue(OthelloBoard* b, int& col, int& row) {
    int max = INT_MIN;
    int max_col = 0;
    int max_row = 0;
    
    vector<OthelloBoard*> succ = successor(b, 'X');
    
    // Test if Terminal or not
    if (succ.size() == 0) {
        return utility(b);
    }
    for(int i = 0; i < succ.size(); i++) {
        cout << "Board: " << succ[i]->count_score('X')  << endl;
        if (max < maxValue(succ[i], col, row)) {
            max = maxValue(succ[i], col, row);
            max_col = succ[i]->get_col();
            max_row = succ[i]->get_row();
        }

    }

    col = max_col;
    row = max_row;
    return max;


}

int MinimaxPlayer::minValue(OthelloBoard* b, int& col, int& row) {
    int min = INT_MAX;
    int min_col = 0;
    int min_row = 0;
    
    vector<OthelloBoard*> succ = successor(b, 'O');
    
    // Test if Terminal or not
    if (succ.size() == 0) {
        return utility(b);
    }
    for(int i = 0; i < succ.size(); i++) {
        cout << "Board: " << succ[i]->count_score('O')  << endl;
        if (min > minValue(succ[i], col, row)) {
            min = minValue(succ[i], col, row);
            min_col = succ[i]->get_col();
            min_row = succ[i]->get_row();
        }
    }

    col = min_col;
    row = min_row;
    return min;
}


void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you
    minimaxDecision(b, col, row);
    //col = 2;
    //row = 3;

}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
    return result;
}
