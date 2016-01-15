#include "moment/MomentEight.h"
#include "utill/FunUtil.h"

void MomentEight::init()
{
	fInterval = 1.0f;
	momentEightItemType1 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(1);
	momentEightItemType2 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(2);
	momentEightItemType3 = ConfigMomentEight::getInstance()->getMomentEightItemByTypeId(3);
	fTemp1 = getRandonNumByAtoB(momentEightItemType1.interval_time_start, momentEightItemType1.interval_time_end);
	fTemp2 = getRandonNumByAtoB(momentEightItemType2.interval_time_start, momentEightItemType2.interval_time_end);
	fTemp3 = getRandonNumByAtoB(momentEightItemType3.interval_time_start, momentEightItemType3.interval_time_end);
}

bool MomentEight::updata(float dt)
{
	nNowTime += dt;
	fTemp1 -= dt;
	fTemp2 -= dt;
	fTemp3 -= dt;
	if (nNowTime > momentEightItemType1.life_time)
	{
		return true;
	}
	if (fTemp1 <= 0)
	{
		fTemp1 = getRandonNumByAtoB(momentEightItemType1.interval_time_start, momentEightItemType1.interval_time_end);
		FishManage::getInstance()->createFishRand(getFishByRandVec(momentEightItemType1.momentEightItemPers));
	}
	if (fTemp2 <= 0)
	{
		fTemp2 = getRandonNumByAtoB(momentEightItemType2.interval_time_start, momentEightItemType2.interval_time_end);
		FishManage::getInstance()->createFishRand(getFishByRandVec(momentEightItemType2.momentEightItemPers));
	}
	if (fTemp3 <= 0)
	{
		fTemp3 = getRandonNumByAtoB(momentEightItemType3.interval_time_start, momentEightItemType3.interval_time_end);
		FishManage::getInstance()->createFishArrangeRand(getFishByRandVec(momentEightItemType3.momentEightItemPers));
	}
	return false;

}

int MomentEight::getFishByRandVec(std::vector<MomentEightItemPer> momentEightItemPers)
{
	std::vector<MomentEightItemPer> vec;
	vec.resize(momentEightItemPers.size());
	for (int i = 0; i < momentEightItemPers.size();i++)
	{
		vec.at(i).fish_id = momentEightItemPers[i].fish_id;
		if (i == 0)
		{
			vec.at(0).per = 0;
		}
		else
		{
			int lastPer = (i == 0 ? 0 : vec[i - 1].per);
			vec.at(i).per = lastPer + momentEightItemPers[i].per;
		}
		
	}
	int randNum = rand() % 100 + 1;
	for (auto ite = vec.rbegin(); ite != vec.rend();ite++)
	{
		if (randNum > ite->per)
		{
			return ite->fish_id;
		}
	}
	return -1;
}