#include "moment/MomentOne.h"


void MomentOne::init()
{
	m_oneMoment = ConfigOnemoment::getInstance()->LoadConfig("config/config_onemoment_1.json");

}

bool MomentOne::updata(float dt)
{
	nNowTime += dt;
	if (nNowTime>10)    //TODO : need update 60s by config
	{
		return true;
	}

	for (auto iter = m_oneMoment.begin(); iter != m_oneMoment.end();)
	{
		if (nNowTime>(iter->start_time))
		{
			auto k = *iter;
			
			FishManage::getInstance()->createFishByOneMonet(*iter);
			iter = m_oneMoment.erase(iter);
			
		}
		else
		{
			return false;
		}
	}

}