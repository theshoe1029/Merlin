#include <vector>
#include <iostream>
#include <limits>

#include "MState.h"

#ifndef M_GAME_H_
#define M_GAME_H_

class MSolver
{
private:    
    MState* root;
    float solveStep(MState* root, int depth);
public:
    MSolver(MState* root);
    ~MSolver();
    void* findBestMove(int depth);
};

MSolver::MSolver(MState* root)
{    
    this->root = root;
}

MSolver::~MSolver()
{
    delete root;
}

void* MSolver::findBestMove(int depth)
{    
    std::vector<void*> nextMoves = root->nextMoves();
    std::vector<MState*> nextStates = root->nextStates(); 
    if (nextMoves.size() == 0) return 0;
    float bestScore = -std::numeric_limits<float>::max();
    void* bestMove = nextMoves[0];
    for (size_t i = 0; i < nextStates.size(); i++) {        
        float score = solveStep(nextStates[i], depth);
        if (score > bestScore) {
            bestScore = score;
            bestMove = nextMoves[i];
        }
    }
    return bestMove;
}

float MSolver::solveStep(MState* root, int depth)
{    
    if (depth == 0) {
        return root->getScore();
    } else {
        std::vector<MState*> nextStates = root->nextStates();        
        if (nextStates.size() == 0 || root->getScore() != 0) {
            return root->getScore();
        } else {
            int solutionSum = 0;
            for (size_t i = 0; i < nextStates.size(); i++) {
                solutionSum += solveStep(nextStates[i], depth-1);
            }
            return solutionSum;
        }
    }
}

#endif
