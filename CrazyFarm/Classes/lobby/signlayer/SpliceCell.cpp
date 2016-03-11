#include "SpliceCell.h"
SpliceCell* SpliceCell::create(int curIndex)
{
	SpliceCell* bRet = new SpliceCell();
	if (bRet&&bRet->init(curIndex))
	{
		bRet->autorelease();
		return bRet;
	}
	else
	{
		delete bRet;
		bRet = NULL;
		return NULL;
	}
}

bool SpliceCell::init(int curIndex)
{
	bool bRet = false;
	while (!bRet)
	{
		auto clipper = ClippingNode::create();
		clipper->setContentSize(Size(89, 130));
		clipper->setAnchorPoint(Point::ZERO);
		clipper->setPosition(0,0);
		addChild(clipper);

		content1 = Sprite::create("signRewards.png");
		content1->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		clipper->addChild(content1);
		content1->setPosition(clipper->getContentSize().width / 2, 0/*clipper->getContentSize().height / 2+83*2.5*/);


		content2 = Sprite::create("signRewards.png");
		content2->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		clipper->addChild(content2);
		content2->setPosition(clipper->getContentSize().width / 2, 498/*clipper->getContentSize().height / 2+498+83*2.5*/);



		auto stencil = DrawNode::create();
		Vec2 rectangle[4];
		rectangle[0] = Vec2(0, 0);
		rectangle[1] = Vec2(clipper->getContentSize().width, 0);
		rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
		rectangle[3] = Vec2(0, clipper->getContentSize().height);

		Color4F white(1, 1, 1, 1);
		stencil->drawPolygon(rectangle, 4, white, 1, white);
		clipper->setStencil(stencil);


		clipper->setStencil(stencil);

		
		bRet = true;
	}
	return bRet;
}

void SpliceCell::update(float delta)
{
	
	nTumbleTime += delta;
	if (nTumbleTime<4)
	{
		speed += delta * 10;
	}
	else
	{
		speed -= delta * 10;
	}
	if (speed<=5)
	{
		speed = 5;
	}
	content1->setPositionY(content1->getPositionY() - speed);
	content2->setPositionY(content2->getPositionY() - speed);
	if (content1->getPositionY() + 498 <= 0)
	{
		content1->setPositionY(content2->getPositionY() + 498);
	}

	if (content2->getPositionY() + 498<=0)
	{
		content2->setPositionY(content1->getPositionY() + 498);
	}
	
}