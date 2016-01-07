#include "utill/FunUtil.h"


bool collision(Sprite*spA, Sprite*spB)
{

	const float scaleMultiple = 0.7;
	auto rect1 = spA->getBoundingBox();
	rect1.setRect(rect1.getMinX() + rect1.size.width / 2 * (1 - scaleMultiple), rect1.getMinY() + rect1.size.height / 2 * (1 - scaleMultiple), rect1.size.width*scaleMultiple, rect1.size.height*scaleMultiple);
	auto rect2 = spB->getBoundingBox();
	rect2.setRect(rect2.getMinX() + rect2.size.width / 2 * (1 - scaleMultiple), rect2.getMinY() + rect2.size.height / 2 * (1 - scaleMultiple), rect2.size.width*scaleMultiple, rect2.size.height*scaleMultiple);

#if 0
	auto draw = DrawNode::create();
	addChild(draw, 10);
	draw->drawRect(rect1.origin, Vec2(rect1.getMaxX(), rect1.getMaxY()), Color4F::YELLOW);
	draw->drawRect(rect1.origin, Vec2(rect1.getMaxX(), rect1.getMaxY()), Color4F::RED);
#endif
	return rect1.intersectsRect(rect2);
}


swimDirection getDirectionByPosition(Vec2 pos)
{
	int x = pos.x;
	int y = pos.y;
	if (x<=0)
	{
		return RIGHT;
	}
	if (x>=960)
	{
		return LEFT;
	}
	if (y>=540)
	{
		return DOWN;
	}
	if (y <= 0)
	{
		return UP;
	}

}