#include <vector>

#ifndef M_STATE_H_
#define M_STATE_H_

class MState
{
private:
    int nPlayers;
    void** playerData;
    void* gameData;    
public:
    MState(int nPlayers, void** playerData, void* gameData);
    ~MState();
    int getNPlayers();
    void** getPlayerData();
    void* getGameData();
    virtual std::vector<void*> nextMoves() { std::vector<void*> moves; return moves; };
    virtual std::vector<MState*> nextStates() { std::vector<MState*> states; return states; };
    virtual float getScore() { return 0; };
};

MState::MState(int nPlayers, void** playerData, void* gameData)
{    
    this->nPlayers = nPlayers;
    this->playerData = playerData;
    this->gameData = gameData;    
}

MState::~MState()
{
    for (int i = 0; i < nPlayers; i++) {
        free(playerData[i]);
    }
    free(playerData);
    free(gameData);
}

int MState::getNPlayers()
{
    return this->nPlayers;
}

void** MState::getPlayerData()
{
    return this->playerData;
}

void* MState::getGameData()
{
    return this->gameData;
}

#endif