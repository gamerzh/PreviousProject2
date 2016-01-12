#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class PayCell : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PayCell);
	  void setValue(int goodId);
	  void setDiamondValue(int goodId);
	  void setVipValue();
	  void IsBeToued();
private:
	CC_SYNTHESIZE(int, m_nGoodId, goodID);
	int m_PayType;
	Sprite* paySprite;
	Sprite* propNum;
	Sprite* giftNum;

};
