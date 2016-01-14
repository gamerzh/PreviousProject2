#include "showTurretLayer.h"
#include "widget/MyTableView.h"
#include "showTurretCell.h"
#include "config/ConfigVipTurrent.h"
#include "config/ConfigTurrent.h"
#include "lobby/shop/payLayer.h"
void showTurretView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size showTurretView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(194, 260);
}
cocos2d::extension::TableViewCell* showTurretView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	showTurretCell *cell = (showTurretCell*)table->dequeueCell();
	if (!cell) {
		cell = showTurretCell::create();
		cell->setPosition(0, 0);
	}
	else
	{

	}
	if (nViewTp == 1)
	{
		cell->setVippaoValue(ConfigVipTurrent::getInstance()->getUnUpgradeTurrents().at(idx).vip_turrent_id);
	}
	else if (nViewTp == 2)
	{
		cell->setMultipleValue(ConfigTurrent::getInstance()->getUnUpgradeTurrents().at(idx).turrentId);
	}
	return cell;
}
ssize_t showTurretView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	if (nViewTp==1)
	{
		return ConfigVipTurrent::getInstance()->getUnUpgradeTurrents().size();
	}
	else if (nViewTp==2)
	{
		return ConfigTurrent::getInstance()->getUnUpgradeTurrents().size();
	}
}




















showTurretLayer* showTurretLayer::create(int type)
{
	showTurretLayer *pRet = new showTurretLayer();
	if (pRet && pRet->init(type))
	{
		
			pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool showTurretLayer::init(int type)
{
	bool bRet = false;
	do 
	{
		m_type = type;
		tableviewDelegate = new showTurretView();
		tableviewDelegate->setviewTp(type);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);
		std::string path;
		if (type ==1)
		{
			path = "equalPao.png";
		}
		else
		{
			path = "lockPao.png";
		}
		auto bg = Sprite::create(path.c_str());
		bg->setPosition(visibleSize / 2);
		addChild(bg);

		
		//tableview
		MyTableView* tableView = MyTableView::create(tableviewDelegate, Size(810,260)
			);
		tableView->setDirection(ScrollView::Direction::HORIZONTAL);
		tableView->setPosition(70,120);
		tableView->setDelegate(tableviewDelegate);
		addChild(tableView);
		tableView->reloadData();



		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(showTurretLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(showTurretLayer::closeButtonCallBack, this));
		close->setPosition(800, 480);
		auto menu = Menu::create(close, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);


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

void showTurretLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void showTurretLayer::chankanCallBack(Ref*pesend)
{

}