#include "payLayer.h"
#include "config/ConfigItem.h"
#include "domain/bag/BagManager.h"
#include "domain/user/User.h"
#include "widget/MyTableView.h"
#include "utill/Chinese.h"
#include "lobby/viplayer/VipLayer.h"
enum 
{
	kDesignTagCell1,
	kDesignTagCell2,

};


void payTableViewCell::setCoinValue(int idx)
{
	if (idx == 0)
	{
		auto node = (PayCell*)getChildByTag(kDesignTagCell1);
		node->setVipValue();
	}
	else
	{
		auto node = (PayCell*)getChildByTag(kDesignTagCell1);
		node->setValue(idx * 2 + 0);
	}
	

	auto node = (PayCell*)getChildByTag(kDesignTagCell2);
	node->setValue(idx * 2 + 1);
}
void payTableViewCell::setDiamondValue(int idx)
{
	if (idx == 0)
	{
		auto node = (PayCell*)getChildByTag(kDesignTagCell1);
		node->setVipValue();
	}
	else
	{
		auto node = (PayCell*)getChildByTag(kDesignTagCell1);
		node->setDiamondValue(idx * 2 + 0);
	}


	auto node = (PayCell*)getChildByTag(kDesignTagCell2);
	node->setDiamondValue(idx * 2 + 1);
}

bool payTableViewCell::init()
{
	bool ret = false;
	do
	{

		float startX = 35;
		float offsetX = 290;
		float offsetY = -10;
		cell0 = PayCell::create();
		cell0->setAnchorPoint(Point::ZERO);
		cell0->setPosition(ccp(startX, offsetY));
		addChild(cell0, 0, kDesignTagCell1);
		startX += offsetX;

		cell1 = PayCell::create();
		cell1->setAnchorPoint(Point::ZERO);
		cell1->setPosition(ccp(startX, offsetY));
		addChild(cell1, 1,kDesignTagCell2);
		startX += offsetX;

		ret = true;
	} while (0);
	return ret;
}



void payView::tableCellTouched(TableView* table, TableViewCell* cell){
	MyTableView * myTableView = (MyTableView*)table;
	Point lastEnd = myTableView->getLastEnd();
	PayCell * selectedCell = NULL;
	PayCell * cell0 = (PayCell*)cell->getChildByTag(kDesignTagCell1);
	PayCell * cell1 = (PayCell*)cell->getChildByTag(kDesignTagCell2);
	CCPoint end = cell->convertToNodeSpace(lastEnd);
	CCRect bb1 = cell0->boundingBox();
	CCRect bb2 = cell1->boundingBox();
	if (bb1.containsPoint(end))
	{
		selectedCell = cell0;
	}
	else if (bb2.containsPoint(end))
	{
		selectedCell = cell1;
	}
	if (selectedCell!=NULL)
	{
		selectedCell->IsBeToued();
	}

}
Size payView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(278, 86);
}
cocos2d::extension::TableViewCell* payView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	payTableViewCell *cell = (payTableViewCell*)table->dequeueCell();
	if (!cell) {
		cell = payTableViewCell::create();
	}
	else
	{

	}
	if (m_shopType == 1)
	{
		cell->setCoinValue(idx);
	}
	else
	{
		cell->setDiamondValue(idx);
	}
	
	return cell;
}
ssize_t payView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	if (m_shopType==1)
	{
		return 4;
	}
	else
	{
		return 3;
	}
}


payLayer * payLayer::createLayer(int payType)
{
	payLayer *ret = new  payLayer();
	if (ret && ret->init(payType))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}



bool payLayer::init(int payType)
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer,-1);
		tableviewDelegate = new payView();
		tableviewDelegate->setShopType(payType);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("paybg.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg);
	
		auto bottomframe = Sprite::create("bottomFrame.png");
		bottomframe->setPosition(visibleSize.width / 2, visibleSize.height*0.38);
		addChild(bottomframe);
	
		auto topFrame = Sprite::create("TopFrame.png");
		topFrame->setPosition(visibleSize.width / 2, visibleSize.height*0.73);
		addChild(topFrame);


		if (payType == 1)
		{
			auto title = Sprite::create("coinShop.png");
			title->setPosition(visibleSize.width / 2, visibleSize.height*0.88);
			addChild(title);

		}
		else
		{
			auto title = Sprite::create("diamondShop.png");
			title->setPosition(visibleSize.width / 2, visibleSize.height*0.88);
			addChild(title);
		}

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(payLayer::closeButtonCallBack, this));
		close->setPosition(800,480);






		//背包
		MyTableView* tableView = MyTableView::create(tableviewDelegate, bottomframe->getContentSize());
		tableView->setAnchorPoint(Point::ZERO);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setPosition(0,0);
		tableView->setDelegate(tableviewDelegate);
		bottomframe->addChild(tableView);
		tableView->reloadData();

		auto nowChargeMoney = User::getInstance()->getChargeMoney();
	
		

		////再充值XX元成为VIP
		auto nowVip = User::getInstance()->getVipLevel();
		
		auto vipConfig = ConfigVipLevel::getInstance();
		auto nextVip =  vipConfig->getVipLevel(nowVip + 1);
		auto topTip = Sprite::create("TopTip.png");
		topTip->setPosition(topFrame->getContentSize() / 2);
		topFrame->addChild(topTip);
		auto size = topTip->getContentSize();
		auto tipfish = Sprite::create("TipFish.png");
		tipfish->setPosition(0, size.height*0.5);
		topTip->addChild(tipfish);

		auto chinaword = ChineseWord("payVIPdes");
		auto strdec = String::createWithFormat(chinaword.c_str(), nextVip.charge_money - nowChargeMoney, nextVip.vip_level);
		 ttf = LabelTTF::create(strdec->getCString(), "Airal", 30);
		 ttf->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		ttf->setPosition(size.width*0.1, size.height / 2);
		topTip->addChild(ttf);
		//首次充值
		if (nowChargeMoney ==0 &&payType ==1)
		{
			ttf->setString(ChineseWord("payCoinFirst").c_str());
			auto ttf1 = LabelAtlas::create("100", "payNum.png", 16, 24, '0');
			ttf1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			ttf1->setPosition(ttf->getPosition().x + ttf->getContentSize().width, ttf->getPositionY());
			topTip->addChild(ttf1,0,"100");

			auto sp = Sprite::create("coin.png");
			sp->setPosition(ttf1->getPosition().x + ttf1->getContentSize().width, ttf1->getPositionY());
			sp->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			topTip->addChild(sp, 0, "coin");

		}


		auto bt = MenuItemImage::create("VIP.png", "VIP.png", CC_CALLBACK_1(payLayer::showVipCallback, this));
		bt->setPosition(726, visibleSize.height*0.73);
		auto menu = Menu::create(bt,close, nullptr);
		menu->setPosition(0, 0);
		addChild(menu);
		//屏蔽向下触摸
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(payLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
		

	//添加系统返回键监听
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
	scheduleUpdate();
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	setName("paylayer");

	return bRet;
}

void payLayer::update(float delta)
{
	auto nowChargeMoney = User::getInstance()->getChargeMoney();
	if (nowChargeMoney<=0)
	{
		return;
	}
	auto nowVip = User::getInstance()->getVipLevel();
	
	auto vipConfig = ConfigVipLevel::getInstance();
	auto nextVip = vipConfig->getVipLevel(nowVip + 1);

	auto chinaword = ChineseWord("payVIPdes");
	auto strdec = String::createWithFormat(chinaword.c_str(), nextVip.charge_money - nowChargeMoney, nextVip.vip_level);
	ttf->setString(strdec->getCString());
	
}
void payLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void payLayer::showVipCallback(Ref*psend)
{
	auto layer = VIPLayer::create();
	layer->setPosition(0, 0);
	addChild(layer,10);
}