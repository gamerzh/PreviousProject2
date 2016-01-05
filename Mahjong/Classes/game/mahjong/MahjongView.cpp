#include "game/mahjong/MahjongView.h"

bool MahjongView::init(){
	if (!Layer::init())
	{
		return false;
	}
	//
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* view_bg = Sprite::create("gamemj/mjzhuobu.jpg");
	view_bg->setScale(0.5);
	view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(view_bg);

	drawPlayerSelf();
	//设置点击事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(MahjongView::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MahjongView::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MahjongView::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO 展示退出界面
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

//绘制自己
void MahjongView::drawPlayerSelf(){
	//头像的绘制
	//HeadPortrait* head = new HeadPortrait();
	//drawHeadPortrait(head);
	//牌的绘制

	ValueVector pai;
	for (int t = 0; t < 14; t++){
		pai.push_back(Value(t));
	}
	for (int i = 0; i < pai.size(); i++){
		Jong* Jong = Jong::create();
		Jong->setScale(0.5);
		Jong->setPosition(ccp(120 + 56 * i, JONG_POS_Y));
		Jong->showJong(0, pai.at(i).asInt());
		this->addChild(Jong);
		selfJongs.pushBack(Jong);
	}
}

//绘制左手边的玩家
void MahjongView::drawPlayerLeft(){

}


//绘制右手边的玩家
void MahjongView::drawPlayerRight(){


}


//绘制对面的玩家
void MahjongView::drawPlayerOpposite(){


}


//绘制玩家的头像
void MahjongView::drawHeadPortrait(HeadPortrait* headPortrait){
	//绘制背景
	Sprite* head_bg = Sprite::create("headportrait/touxiangheidi.png");
	head_bg->setScale(0.5);
	head_bg->setPosition(ccp(100, 150));
	this->addChild(head_bg);
}



bool MahjongView::onTouchBegan(Touch *touch, Event  *event){
	//被选中的牌跟随手指移动
	CCLOG("current pos === %f,%f", touch->getLocation().x, touch->getLocation().y);
	virtualJong = nullptr;
	for (int i = 0; i < selfJongs.size(); i++)
	{
		//TODO
		CCLOG("JongBoundingBox x1 === %f", selfJongs.at(i)->getJongBoundingBox().getMinX());
		CCLOG("JongBoundingBox x2 === %f", selfJongs.at(i)->getJongBoundingBox().getMaxX());
		//CCLOG("JongBoundingBox y1 === %f", selfJongs.at(i)->getJongBoundingBox().getMinY());
		//CCLOG("JongBoundingBox y2 === %f", selfJongs.at(i)->getJongBoundingBox().getMaxY());
		if (selfJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
			CCLOG("find the jong");
			selectJong = selfJongs.at(i);
			return true;
		}
	}
	selectJong = nullptr;
	return true;
}


void MahjongView::onTouchMoved(Touch *touch, Event  *event){
	//判断手指在移动的过程中是否选中牌
	if (nullptr == virtualJong){
		for (int i = 0; i < selfJongs.size(); i++)
		{
			if (selfJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())){
				selectJong = selfJongs.at(i);
				virtualJong = nullptr;
				resetJongPos();
				break;
			}
			selectJong = nullptr;
		
		}
		//选中的牌跟随手指移动
		if (nullptr != selectJong){
			//手指移动的距离转化为牌的纵坐标的移动值
			if (touch->getLocation().y - touch->getPreviousLocation().y > 0){

				selectJong->setPosition(ccp(selectJong->getPositionX(), selectJong->getPositionY() +
					distance(touch->getLocation(), touch->getPreviousLocation())));
			}

			if (selectJong->getPositionY() > JONG_SEL_POS_Y){
				selectJong->setPosition(ccp(selectJong->getPositionX(), JONG_SEL_POS_Y));
				//判断当前是否轮到自己出牌
				if (true){
					if (virtualJong == nullptr){
						virtualJong = Jong::create();
						virtualJong->setScale(0.5);
						virtualJong->setPosition(selectJong->getPosition());
						virtualJong->showJong(0, selectJong->getJongType());
						//设置子节点的透明度随父节点变化
						virtualJong->setOpacity(100);
						virtualJong->setCascadeColorEnabled(true);
						virtualJong->setCascadeOpacityEnabled(true);
						this->addChild(virtualJong);
					}
					virtualJong->setPosition(touch->getLocation());
				}
				else{
					resetAllJong();
				}
			}
		}
		else{
			//TODO 可以考虑加入延迟
			resetAllJong();
		}
	
	}
	else{
		if (virtualJong->getPositionY() > JONG_SEL_POS_Y){
			virtualJong->setPosition(touch->getLocation());
		}
		else{
			virtualJong->removeFromParentAndCleanup(true);
			virtualJong = nullptr;
		}
	}	
}



void MahjongView::onTouchEnded(Touch *touch, Event  *event){
	//高度检查,超出高度后当弃选
	resetAllJong();
	if (nullptr != virtualJong){
		virtualJong->removeFromParentAndCleanup(true);
	}
}

void MahjongView::resetAllJong(){
	for (int i = 0; i < selfJongs.size(); i++)
	{
		selfJongs.at(i)->setPosition(ccp(selfJongs.at(i)->getPositionX(), JONG_POS_Y));
	}
}

void MahjongView::resetJongPos(){
	if (nullptr != selectJong){
		for (int i = 0; i < selfJongs.size(); i++)
		{
			if (selfJongs.at(i) != selectJong){
				selfJongs.at(i)->setPosition(ccp(selfJongs.at(i)->getPositionX(), JONG_POS_Y));
			}
		}
	}
}

float MahjongView::distance(Point pos1,Point pos2){
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}