#pragma once
#include "cocos2d.h"
#include "MomentIntervalCreate.h"
#include "fish/FishManage.h"
using namespace cocos2d;

struct MomentFiveData 
{
	int fishID;
	float startTime;
	Vec2 pos;
<<<<<<< HEAD
	MomentFiveData(int id, float time,Vec2 p){ fishID = id, time = startTime; pos=p;};
=======
    MomentFiveData(int id, float time,Vec2 p){ fishID = id, time = startTime; pos=p;};
>>>>>>> origin/master
};
class MomentFive : public Moment {

public:
	virtual void init();
	virtual bool updata(float dt);
private:
	float nNowTime = 0;
	std::vector<MomentFiveData> datas;
};
