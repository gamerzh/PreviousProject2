#include "TurnTableDialog.h"
#include "domain/turntable/CTurntable.h"
#include "domain/bag/BagManager.h"
#include "domain/bonuspool/BonusPoolManager.h"
#include "utill/AnimationUtil.h"
#include "core/showFishLayer.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "utill/Chinese.h"
#include "domain/game/GameManage.h"
#include "server/Server.h"
#include "domain/logevent/LogEventTurnTable.h"
USING_NS_CC_EXT;
bool TurnTableDialog::init()
{
	Layer::init();
	bool bRet = false;
	do
	{ 


		auto bg = Sprite::create("turntableBgFrame.png");
		bg->setPosition(480, 270);
		addChild(bg, -1);

		auto caidainode = Sprite::create();
		caidainode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniCaidai")));
		caidainode->setPosition(480, 486);
		addChild(caidainode,1);

		auto size = Director::getInstance()->getVisibleSize();
		table = CTurntable::create();
		table->setPosition(size.width/2,size.height*0.58);
		addChild(table);

		auto title = Sprite::create("turntableTitle.png");
		title->setPosition(size.width / 2, 510);
		addChild(title);

		

		createBottomFrame(BonusPoolManager::getInstance()->allowBonusPool());

		auto nowBounsStr = String::createWithFormat("%ld", BonusPoolManager::getInstance()->getBounsCoins())->getCString();
		auto nowBounsLabel = LabelAtlas::create(nowBounsStr, "bounspoolnum.png", 15, 24, '0');
		nowBounsLabel->setPosition(480, 300);
		nowBounsLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(nowBounsLabel); 
		

		auto close = MenuItemImage::create("smallX_1.png", "smallX_2.png", CC_CALLBACK_1(TurnTableDialog::closeButtonCallBack, this));
		close->setPosition(638, 465);
		auto menu = Menu::create(close, nullptr);
		menu->setPosition(Point::ZERO);
		menu->setName("close");
		addChild(menu);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(TurnTableDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		bg->setVisible(false);
		setScale(0);
		runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), CallFunc::create([=]{bg->setVisible(true); }), nullptr));


		auto aniNode = Sprite::create();
		aniNode->setPosition(290, 160);
		addChild(aniNode, 5);
		aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0.1f));

		aniNode = Sprite::create();
		aniNode->setPosition(650,160);
		addChild(aniNode, 5);
		aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0.2f));


		bRet = true;
	} while (0);


	return bRet;
}
void TurnTableDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}
void TurnTableDialog::choujiangButtonCallBack(Ref*psend)
{
	auto bonus = BonusPoolManager::getInstance()->getNextBonuspool();
	int nextCoin;
	if (bonus)
	{
		nextCoin = bonus->start_coins;
	}
	else
	{
		nextCoin = -1;
	}
	if (nextCoin!=-1)
	{
		auto str = String::createWithFormat(ChineseWord("choujiangSure").c_str(), nextCoin-BonusPoolManager::getInstance()->getBounsCoins());
		auto toast = TwiceSureDialog::createDialog(str->getCString(), CC_CALLBACK_1(TurnTableDialog::beginChoujiangButtonCallBack, this));
		toast->setPosition(0, 0);
		addChild(toast, 20,"toast");
	}
	else
	{
		beginChoujiangButtonCallBack(nullptr);
	}
	
	
}
void TurnTableDialog::BeginTurnTable(int itemID, int num)
{

	table->menuButtonCallback(itemID,num);


	auto ac = ProgressTo::create(0.5f, 0);
	bar->runAction(ac);

	labelNowCoin->setString("0");

	((Menu*)getChildByName("close"))->setEnabled(false);
	((Menu*)(getChildByName("bottomframe")->getChildByName("choujiang")))->setEnabled(false);
}

void TurnTableDialog::beginChoujiangButtonCallBack(Ref*psend)
{
	Server::getInstance()->sendBounsPool();
	auto node = getChildByName("toast");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}
void TurnTableDialog::showGoldFishButtonCallBack(Ref*psend)
{
	/*auto layer = showFishLayer::create();
	layer->setPosition(Point::ZERO);
	getParent()->addChild(layer, 20);*/
	Pay::getInstance()->Overbooking(14, 24, getParent());

}

void TurnTableDialog::onGetRewards(BonuspoolRewardItem reward)
{
	GameManage::getInstance()->getGameLayer()->onGetReward(reward.item_id, reward.num);
	removeFromParentAndCleanup(1);
}

void TurnTableDialog::createBottomFrame(bool isFinish)
{
	auto sp = Sprite::create("nowBounsPool.png");
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	sp->setPosition(960 / 2, 35);
	addChild(sp,0,"bottomframe");

	auto tiptxt = Sprite::create("TXTbounsTip.png");
	tiptxt->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	tiptxt->setPosition(960 / 2, 6);
	tiptxt->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.8f), FadeOut::create(0.8f), nullptr)));
	addChild(tiptxt);



	auto barframe = Sprite::create("bounsbarframe.png");
	barframe->setPosition(181, 33);
	sp->addChild(barframe);


	bar = LoadingBar::create("turnTableExeBar.png");
	bar->setPosition(Vec2(5, barframe->getContentSize().height / 2));
	bar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	barframe->addChild(bar);
	if (isFinish)
	{
		//继续获取更多话费
		auto txt = Sprite::create("TXTJixu.png");
		txt->setPosition(169, 69);
		sp->addChild(txt);
		auto smallcoin = Sprite::create("smallCoin.png");
		smallcoin->setPosition(54, 34);
		sp->addChild(smallcoin);
		//经验条
		auto bonus = BonusPoolManager::getInstance()->getNextBonuspool();
		int nextCoin;
		if (bonus)
		{
			nextCoin = bonus->start_coins;
		}
		else
		{
			nextCoin = -1;
		}
	
		auto nowCoin = BonusPoolManager::getInstance()->getBounsCoins();

		auto nowCoinStr = String::createWithFormat("%ld", nowCoin)->getCString();
		labelNowCoin = LabelAtlas::create(nowCoinStr, "nowPoolNum.png", 13, 21, '0');
		labelNowCoin->setScale(0.9);
		labelNowCoin->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		labelNowCoin->setPosition(barframe->getContentSize().width / 2 - 5, barframe->getContentSize().height / 2);
		barframe->addChild(labelNowCoin, 0, "nowCoin");
		// “/”符号
		auto label = LabelAtlas::create(":", "nextPoolNum.png", 11, 19, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setPosition(barframe->getContentSize() / 2);
		barframe->addChild(label);

		
		if (nextCoin == -1)
		{
			auto max = Sprite::create("MAX.png");
			max->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			max->setPosition(label->getPositionX() + label->getContentSize().width / 2, label->getPositionY());
			barframe->addChild(max);
			max->setScale(0.9);
			bar->setPercent(100);
		}
		else
		{
			auto nextlabel = LabelAtlas::create(Value(nextCoin).asString(), "nextPoolNum.png", 11, 19, '0');
			nextlabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			nextlabel->setPosition(label->getPositionX() + label->getContentSize().width / 2, label->getPositionY());
			barframe->addChild(nextlabel);
			auto scale = (float)nowCoin / (float)nextCoin*100;
			bar->setPercent(scale);
			if (scale == 0)
			{
				bar->setVisible(false);
			}
		}
		//按钮
		auto bt = MenuItemImage::create("btn_choujiang_1.png", "btn_choujiang_2.png", CC_CALLBACK_1(TurnTableDialog::choujiangButtonCallBack, this));
		bt->setPosition(382, 45);
		auto menu = Menu::create(bt, nullptr);
		menu->setPosition(Point::ZERO);
		menu->setName("choujiang");
		sp->addChild(menu);
	}
	else
	{
		//再杀几条黄金鱼
		auto txt = Sprite::create("TXTzshjy.png");
		txt->setPosition(169, 69);
		sp->addChild(txt);
		
		auto goldfishneed = LabelAtlas::create(Value(BonusPoolManager::getInstance()->getFishNeedCatchToChoujiang()).asString(), "nowPoolNum.png", 13, 21, '0');
		goldfishneed->setScale(1.5);
		goldfishneed->setAnchorPoint(Point::ANCHOR_MIDDLE);
		goldfishneed->setPosition(54, 13);
		txt->addChild(goldfishneed);

		//经验条
		auto bonus = BonusPoolManager::getInstance();
		auto nowfish = bonus->getBounsFishCounts();
		auto allowdfish = bonus->getAllowCatchFishCounts();


		float ScaleX = (float)nowfish / (float)allowdfish * 100;
		bar->setPercent(ScaleX);
		if (ScaleX==0)
		{
			bar->setVisible(false);
		}
		auto label = LabelAtlas::create(Value(nowfish).asString(), "nowPoolNum.png", 13, 21, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		label->setPosition(barframe->getContentSize().width / 2 - 10, barframe->getContentSize().height / 2);
		barframe->addChild(label);
		auto str = String::createWithFormat(":%d", allowdfish);
		label = LabelAtlas::create(str->getCString(), "nextPoolNum.png", 11, 19, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setPosition(barframe->getContentSize() / 2);
		barframe->addChild(label);


		//按钮
		auto bt = MenuItemImage::create("btn_showgoldFish_1.png", "btn_showgoldFish_2.png", CC_CALLBACK_1(TurnTableDialog::showGoldFishButtonCallBack, this));
		bt->setPosition(382, 45);
		auto menu = Menu::create(bt, nullptr);
		menu->setPosition(Point::ZERO);
		sp->addChild(menu);
	}
}