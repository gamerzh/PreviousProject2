#pragma once
#include "cocos2d.h"
#include "PlayerWork.h"
#include "domain/ai/AI.h"
#include "fish/FishManage.h"

using namespace cocos2d;
//选取最近的鱼打
class AIJun : public AI {

public:
	virtual PlayerWork nextStep(int currentCoins, Point currentPostion, int AiDoCounts, bool isUsingSkillLockOrLight = false, float bulletWidth = 0);
    
    
private:
    float angle = 0;
    bool lastFire = false;
    int count = 0;
    int nextCountReset = 60;
    int baseFireLevel = 40;
    int fireLevel =40 /*baseFireLevel*/;
};

