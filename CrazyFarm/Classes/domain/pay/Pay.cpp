#include "domain/pay/Pay.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h".
#include "platform\android\jni\JniHelper.h"
#include "PayEventPointConfig.h"
#include "domain/user/DeviceInfo.h"
#include "server/HttpMannger.h"
#include "utill/JniFunUtill.h"
#define PAYPOSTREQUEST "http://114.119.39.150:1701/mo/order/booking"

Pay* Pay::_instance = NULL;

Pay::Pay(){
    this->init();
}

void Pay::init(){
}

Pay* Pay::getInstance(){
    if(_instance == NULL){
        _instance = new Pay();
    }
    return _instance;
}
void Pay::Overbooking(int paypoint, int eventPoint)
{
	int payeventVersion = PayEventPointConfig::getInstance()->getPayeventVersion();
	int payPointVersion = PayPointConfig::getInstance()->getVersion();
	auto payPointInfo = PayPointConfig::getInstance()->getPayPointInfoById(paypoint);
	auto channel_id = DeviceInfo::getChannel_id();
	auto sessionid = User::getInstance()->getSessionid();
	HttpMannger::getInstance()->HttpToPostRequestBeforePay(sessionid, payPointVersion * 1000 + payeventVersion, eventPoint, paypoint, channel_id);
}

void Pay::pay(payRequest*data, long int orderid)
{
	nowData = data;
	nowData->orderID = orderid;
	auto str = String::createWithFormat("%ld", orderid);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	payCallBack(0, "success");
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	return 1;
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniFunUtill::getInstance()->pay(PayPointConfig::getInstance()->getPayPointInfoById(nowData->pay_point_id).price, str->getCString());
#endif
}


void Pay::payCallBack(int code, const char* msg)
{
	if (code == 0)
	{
		auto info = PayPointConfig::getInstance()->getPayPointInfoById(nowData->pay_point_id);
		//道具处理
		for (auto var:info.items)
		{
			switch (var.ItemID)
			{
				case 1:
					User::getInstance()->addCoins(var.ItemNum);
					User::getInstance()->setHaveBycoin();
					break;
				case 2:
					User::getInstance()->addDiamonds(var.ItemNum);
					break;
				case 3:
					NobilityManager::getInstance()->addStepsDay(30);
					break;
			default:
				break;
			}
		}
		if (nowData->pay_point_id == 14)
		{
			User::getInstance()->setHaveFirstPay();
		}
		User::getInstance()->addChargeMoney(info.price / 100);
		//上传订单结果
		HttpMannger::getInstance()->HttpToPostRequestAfterPay(nowData->sessionid, nowData->pay_and_Event_version, nowData->pay_event_id, nowData->pay_point_id, nowData->channel_id, 0, nowData->orderID);

	}
}

PayPointInfo Pay::getInfoByPaypoint(int paypoint)
{
	return PayPointConfig::getInstance()->getPayPointInfoById(paypoint);
}