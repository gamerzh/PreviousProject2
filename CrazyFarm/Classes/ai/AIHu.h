#ifndef _AIHU_H_
#define _AIHU_H_
#include "cocos2d.h"
#include "PlayerWork.h"
#include "AI.h"

using namespace cocos2d;

class AIHu : public AI {

public:
    PlayerWork nextStep(int currentCoins);
    
    
private:
    float angle = 0;
};

#endif