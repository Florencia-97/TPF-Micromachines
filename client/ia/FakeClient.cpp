#include "FakeClient.h"
#include "../../config/constants.h"

FakeClient::FakeClient(SafeQueue<InfoBlock> &kq, std::queue<InfoBlock> &pos):
    luaWrapper(), mapsLayer() {
    this->keyboardQueue = &kq;
    this->posQueue = &pos;
}

void FakeClient::setRace(std::string raceName){
    mapsLayer.load("maps/" + raceName + ".yaml");
}

void FakeClient::_firstMove(){
    InfoBlock ib;
    ib[ACTION_TYPE] = UP;
    this->keyboardQueue->push(ib);
}

std::string FakeClient::_getId(){
    while (posQueue->empty()) continue;
    InfoBlock ib = posQueue->front();
    posQueue->pop();
    int my_car_id = ib.exists(MY_ID) ? ib.get<int>(MY_ID) : 0;
    return std::to_string(my_car_id);
}

void FakeClient::_run() {
    InfoBlock* gameState;
    this->_firstMove();
    int lastMove = 0;
    std::string id = _getId();
    while (this->isAlive()){
        InfoBlock ib;
        if ( !posQueue->empty()){
            while (posQueue->size()>1){
                posQueue->pop(); gameState = &posQueue->front();
            }
            gameState = &posQueue->front();
            int x = gameState->exists("x" + id) ? gameState->get<int>("x" + id) : 0;
            x = (int) floor(x/TILE_SIZE);
            int y = gameState->exists("y" + id) ? gameState->get<int>("y" + id) : 0;
            y = (int) floor(y/TILE_SIZE);
            int r = gameState->exists("r" + id) ? gameState->get<int>("r" + id) : 0;
            InfoBlock ib;
            if (_move(ib, x, y, r, lastMove)) this->keyboardQueue->push(ib);
        }
        this->sleep(0.05);
    }
}

bool FakeClient::_move(InfoBlock& ib, int x, int y, int r, int& lastMove) {
    std::string des = luaWrapper.getDesition(mapsLayer.road, x +1, y+ 1, r, lastMove);
    if (des == "") return false;
    std::stringstream ss(des);
    std::string token;
    // Getting Action Type
    std::getline(ss, token, '-');
    std::string actionType = token ;
    // Getting Event type
    std::getline(ss, token);
    std::string eventType = token;
    char et;

    // Getting action type and event type
    if (eventType == "UP") et = UP;
    else if (eventType == "DOWN") et = DOWN;
    else if (eventType == "LEFT") et = LEFT;
    else et = RIGHT;
    if (actionType == ACTION_TYPE && et == RIGHT) lastMove = 1;
    else if (actionType == ACTION_TYPE_DOWN && et == RIGHT) lastMove = 2;
    else if (actionType == ACTION_TYPE && et == LEFT) lastMove = 3;
    else if (actionType == ACTION_TYPE_DOWN && et == LEFT) lastMove = 4;
    ib[actionType] = et;
    return true;
}