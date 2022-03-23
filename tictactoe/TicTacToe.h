#include <iostream>
#include <cstring>

#include "MState.h"
#include "MSolver.h"
#include "TicTacToeState.h"

#ifndef TIC_TAC_TOE_H_
#define TIC_TAC_TOE_H_

class TicTacToe
{
private:
    MState* root;    
public:
    TicTacToe();
    ~TicTacToe();
    void loop();
};

TicTacToe::TicTacToe()
{
    this->root = new TicTacToeState();
    srand(time(NULL));
    TicTacToeState* state = (TicTacToeState*) this->root;
    TicTacToeData* data = (TicTacToeData*) state->getGameData();
    data->playerTurn = rand() % 2 ? X : O;
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::loop()
{
    while(true) {
        TicTacToeState* state = (TicTacToeState*) this->root;
        TicTacToeData* data = (TicTacToeData*) state->getGameData();
        TicTacToeSquare playerTurn = data->playerTurn;
        std::cout << *state << std::endl;
        if (state->getScore() != 0) {
            TicTacToeSquare winner = playerTurn == X ? O : X;
            std::cout << "Game over " << winner << " wins" << std::endl;
            exit(1);
        } else if (state->isTie()) {
            std::cout << "Game over there is a tie" << std::endl;
            exit(1);
        } else {
            int x, y;
            if (playerTurn == X) {
                std::cout << "AI move" << std::endl;
                MSolver* solver = new MSolver(root);
                int* bestMove = (int*) solver->findBestMove(-1);
                x = bestMove[0];
                y = bestMove[1];
            } else {
                std::cout << "Player move" << std::endl;
                char line[3];
                std::cin.read(line, 3);
                x = atoi(&line[2]);
                y = atoi(&line[0]);
            }
            data->board[x][y] = data->playerTurn;             
            data->playerTurn = data->playerTurn == X ? O : X;
            fflush(stdin);       
        }         
    }
}

#endif