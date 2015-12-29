#ifndef _AI_H_
#define _AI_H_
#include "cocos2d.h"
#include "PlayerWork.h"

using namespace cocos2d;

class AI {

public:
    
    virtual PlayerWork nextStep(int currentCoins) = 0;
    
    CC_SYNTHESIZE(int, maxTurrentLevel, MaxTurrentLevel);
    CC_SYNTHESIZE(int, reqSteps, ReqSteps);
    
private:
    
};

#endif
