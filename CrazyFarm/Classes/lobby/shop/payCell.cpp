#include "payCell.h"
#include "User.h"
bool PayCell::init(){
	if (!Sprite::initWithFile("payframe.png")){
		return false;
	}
	auto size = getContentSize();
	paySprite = Sprite::create();
	paySprite->setPosition(size.width *0.21, size.height / 2);
	addChild(paySprite);

	propNum = Sprite::create();
	propNum->setPosition(size.width*0.68, size.height*0.76);
	addChild(propNum);

	giftNum = Sprite::create();
	giftNum->setPosition(size.width*0.68, size.height*0.30);
	addChild(giftNum);

	return true;
}

void PayCell::setValue(int goodId)
{
	setgoodID(goodId);
	m_PayType == 1;
	auto spPath = String::createWithFormat("coin_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
}


void PayCell::setDiamondValue(int goodId)
{
	setgoodID(goodId);
	m_PayType == 2;
	auto spPath = String::createWithFormat("diamond_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
}

void PayCell::setVipValue()
{
	m_PayType == 3;
	paySprite->setTexture("payVip.png");
	propNum->setTexture("payVipNum.png");
	giftNum->setTexture("payVipGift.png");
}

int coingood[5] = { 4,9, 19, 29, 54 };
int diamondGood[5] = { 180, 418, 650, 1348, 4768 };
void PayCell::IsBeToued()
{
	switch (m_PayType)
	{
	case 1:
		User::getInstance()->addCoins(coingood[m_nGoodId + 1]);
		break;
	case 2:
		User::getInstance()->addCoins(diamondGood[m_nGoodId + 1]);
		break;
	case 3:
		break;
	default:
		break;
	}
}