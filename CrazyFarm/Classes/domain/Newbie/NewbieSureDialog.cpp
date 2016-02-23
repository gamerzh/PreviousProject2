#include "NewbieSureDialog.h"
#include "lobby/LobbyScene.h"

bool NewbieSureDialog::init()
{
	auto bg = Sprite::create("TwiceSureDialog.png");
	bg->setPosition(480, 270);
	addChild(bg, -1);

	auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(NewbieSureDialog::closeButtonCallBack, this));
	close->setPosition(bg->getContentSize());


	auto sure = MenuItemImage::create("begingamebt.png", "begingamebt.png");
	sure->setPosition(bg->getContentSize().width / 2, 40);
	sure->setCallback(CC_CALLBACK_1(NewbieSureDialog::sureButtonCallBack, this));
	
	auto menu = Menu::create(close, sure, nullptr);
	menu->setPosition(bg->getPosition() - bg->getContentSize() / 2);
	addChild(menu);


	auto sp = Sprite::create("NewBieTxt1.png");
	sp->setPosition(bg->getContentSize().width / 2, 99);
	bg->addChild(sp);

	sp = Sprite::create("NewBieTxt2.png");
	sp->setPosition(bg->getContentSize().width / 2, 203);
	bg->addChild(sp);

	sp = Sprite::create("NewBieTxt3.png");
	sp->setPosition(bg->getContentSize().width / 2, 153);
	bg->addChild(sp);

	

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(NewbieSureDialog::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	//����ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			/*removeFromParentAndCleanup(1);*/
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	/////////��������
	setScale(0);
	runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
	return true;
}

void NewbieSureDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void NewbieSureDialog::sureButtonCallBack(Ref*psend)
{
	((LobbyScene*)getParent())->quickBeginCallback(nullptr);
	removeFromParentAndCleanup(1);
}