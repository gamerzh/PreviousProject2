#include "MissionLayer.h"
#include "MissionManager.h"
#include "utill/Chinese.h"
#include "domain/user/User.h"




Scene* MissionLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = MissionLayer::create();

	scene->addChild(layer);

	return scene;
}

bool MissionLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		_MissionViewDelegate = new MissionView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("missionFrame.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg,0,"bg");



		//tableview
		tableView = MyTableView::create(_MissionViewDelegate, Size(894, 383));
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setPosition(35,26);
		tableView->setDelegate(_MissionViewDelegate);
		bg->addChild(tableView);
		tableView->reloadData();

	
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(MissionLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(MissionLayer::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize());
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);

		auto sp1 = Sprite::create("tab_1.png");
		auto txt1 = Sprite::create("dayMission_1.png");
		txt1->setPosition(sp1->getContentSize() / 2);
		sp1->addChild(txt1);
		auto sp2 = Sprite::create("tab_2.png");
		auto txt2 = Sprite::create("dayMission_2.png");
		txt2->setPosition(sp2->getContentSize() / 2);
		sp2->addChild(txt2);

		auto coinButton = MenuItemSprite::create(sp1,sp2, CC_CALLBACK_1(MissionLayer::changeTypeCallBack, this));
		coinButton->setName("mission");
		coinButton->setPosition(109+22, 439);
		coinButton->setEnabled(false);


		sp1 = Sprite::create("tab_1.png");
		txt1 = Sprite::create("achieveMission_1.png");
		txt1->setPosition(sp1->getContentSize() / 2);
		sp1->addChild(txt1);
		 sp2 = Sprite::create("tab_2.png");
		txt2 = Sprite::create("achieveMission_2.png");
		txt2->setPosition(sp2->getContentSize() / 2);
		sp2->addChild(txt2);

		auto expButton = MenuItemSprite::create(sp1,sp2, CC_CALLBACK_1(MissionLayer::changeTypeCallBack, this));
		expButton->setName("achieve");
		expButton->setPosition(298+22, 439);
		auto menu = Menu::create(close, coinButton, expButton,nullptr);
		menu->setPosition(Point::ZERO);
		bg->addChild(menu);
		coinButton->selected();


	//����ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			removeFromParentAndCleanup(1);
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	

	return bRet;
}

void MissionLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void MissionLayer::changeTypeCallBack(Ref*psend)
{
	auto bt = (MenuItemImage*)(psend);
	auto btName = bt->getName();
	if (btName == "mission")
	{
		bt->setEnabled(false);
		bt->selected();
		auto otherBt = (MenuItemImage*)bt->getParent()->getChildByName("achieve");
		otherBt->unselected();
		otherBt->setEnabled(true);
		changeToMissionlist();
	}
	else
	{
		bt->setEnabled(false);
		bt->selected();
		auto otherBt = (MenuItemImage*)bt->getParent()->getChildByName("mission");
		otherBt->unselected();
		otherBt->setEnabled(true);
		changeToAchievelist();
	}
}
void MissionLayer::changeToMissionlist()
{
	tableView->removeFromParentAndCleanup(1);
	_MissionViewDelegate = new MissionView();
	tableView = MyTableView::create(_MissionViewDelegate, Size(894, 383));
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(35, 26);
	tableView->setDelegate(_MissionViewDelegate);
	getChildByName("bg")->addChild(tableView);
	tableView->reloadData();

	
	
}

void MissionLayer::changeToAchievelist()
{
	tableView->removeFromParentAndCleanup(1);
	_achieveViewDelegate = new AchieveView();
	tableView = MyTableView::create(_achieveViewDelegate, Size(894, 383));
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(35, 26);
	tableView->setDelegate(_achieveViewDelegate);
	getChildByName("bg")->addChild(tableView);
	tableView->reloadData();
}