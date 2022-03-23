#include "MState.h"

#ifndef TIC_TAC_TOE_STATE_H_
#define TIC_TAC_TOE_STATE_H_

enum TicTacToeSquare
{
    EMPTY,
    X,
    O
};

struct TicTacToeData {
    TicTacToeSquare playerTurn;
    TicTacToeSquare board[3][3];
};

class TicTacToeState: public MState
{
public:
    TicTacToeState();
    TicTacToeState(TicTacToeData* data);
    ~TicTacToeState();
    std::vector<void*> nextMoves();
    std::vector<MState*> nextStates();
    float getScore();
    bool isTie();
    
};

std::vector<void*> TicTacToeState::nextMoves()
{
    TicTacToeData* data = (TicTacToeData*) getGameData();
    std::vector<void*> moves;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (data->board[x][y] == EMPTY) {
                int* move = (int*) malloc(sizeof(int)*2);
                move[0] = x; move[1] = y;
                moves.push_back(move);
            }
        }
    }
    return moves;
}

std::vector<MState*> TicTacToeState::nextStates()
{
    TicTacToeData* data = (TicTacToeData*) getGameData();
    std::vector<MState*> states;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (data->board[x][y] == EMPTY) {
                TicTacToeData* newData = (TicTacToeData*) malloc(sizeof(TicTacToeData));
                memcpy(newData, data, sizeof(TicTacToeData));
                newData->board[x][y] = newData->playerTurn;
                newData->playerTurn = newData->playerTurn == X ? O : X;
                states.push_back(new TicTacToeState(newData));
            }
        }
    }
    return states;
}

float TicTacToeState::getScore()
{
    TicTacToeData* data = (TicTacToeData*) getGameData();    
    TicTacToeSquare playerTurn = data->playerTurn;
    TicTacToeSquare board[3][3];
    memcpy(board, data->board, sizeof(data->board));
    for (int x = 0; x < 3; x++) {
        if (board[x][0] == board[x][1] && board[x][1] == board[x][2]) {
            if (board[x][0] == X) return 1;
            if (board[x][0] == O) return -1;
        }
    }
    for (int y = 0; y < 3; y++) {
        if (board[0][y] == board[1][y] && board[1][y] == board[2][y]) {
            if (board[0][y] == X) return 1;
            if (board[0][y] == O) return -1;
        }            
    }    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == X) return 1;
        if (board[0][0] == O) return -1;
    }        
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == X) return 1;
        if (board[0][2] == O) return -1;
    }        
    return 0;
}

bool TicTacToeState::isTie()
{
    TicTacToeData* data = (TicTacToeData*) getGameData();
    TicTacToeSquare board[3][3];
    memcpy(board, data->board, sizeof(data->board));
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (board[x][y] == EMPTY) return false;
        }
    }
    return true;
}

TicTacToeState::TicTacToeState() : MState(2, 0, malloc(sizeof(TicTacToeData)))
{
    TicTacToeData* data = (TicTacToeData*) getGameData();
    data->playerTurn = X;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            data->board[x][y] = EMPTY;
        }
    }    
}

TicTacToeState::TicTacToeState(TicTacToeData* data) : MState(2, 0, data)
{
}

TicTacToeState::~TicTacToeState()
{
}

inline std::ostream & operator<<(std::ostream &o, TicTacToeSquare const &square) {
    switch(square) {
        case EMPTY:
            o << " ";
            return o;         
        case X:
            o << "X";
            return o;
        case O:
            o << "O";
            return o;
        default:
            return o;
    }
}

inline std::ostream & operator<<(std::ostream &o, TicTacToeState &state) {
    TicTacToeData* data = (TicTacToeData*) state.getGameData();
    TicTacToeSquare board[3][3];
    memcpy(board, data->board, sizeof(data->board));
    o << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
    o << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
    o << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;
    o << "turn: " << data->playerTurn << " score: " << state.getScore();
    return o;
}


#endif