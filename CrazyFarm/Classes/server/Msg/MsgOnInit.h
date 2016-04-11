#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
#include "domain/room/RoomManager.h"
using namespace cocos2d;

class  Msg_onInit :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
	int roomPos;//����λ��
	std::vector<RoomPlayer*> roomplayers;
	
	std::vector<MsgFishesInfo> _FishesInfos;
	unsigned long initCreateTime;
	float _catchper;


	float bullet_speed;
	float bullet_interval;
};

