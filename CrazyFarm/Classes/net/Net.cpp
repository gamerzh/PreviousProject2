#include "net/Net.h"
#include "utill/FunUtil.h"
bool Net::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Net::initNetByType(int ui_type, int net_type){
	
	initWithFile(getFrameNameByType(ui_type,net_type));
	schedule(schedule_selector(Net::destroySelf),0,0,1);
}

std::string Net::getFrameNameByType(int ui_type, int net_type){
	auto str = String::createWithFormat("gamelayer/bulletAndNet/net_%d_%d.png", ui_type, net_type);
	return str->getCString();
}


void Net::destroySelf(float dt){
	this->removeFromParent();
}

void Net::checkCatchFish(Bullet*bullet){
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	Vector<Fish*> fishNeedRemove;
	for (Fish* fish : allFish){
		if (collision(this,fish)){
			//���в����ж�
			//TODO ���Ӳ������
			int k = rand() % 100 + 1;
			if (k>(100-fish->getGrabProbability()*100))
			{
				fishNeedRemove.pushBack(fish);
			//ui�Ƴ�
				fish->removeFromParent();
			}
			
		}
	}
	bullet->getCoinForFish(fishNeedRemove);
	for (Fish* fish : fishNeedRemove){
		FishManage::getInstance()->removeFish(fish);
	}
}