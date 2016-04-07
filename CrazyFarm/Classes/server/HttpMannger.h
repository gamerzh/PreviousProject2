#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
#include "HttpMsgDefine.h"
#include "widget/LoadingCircle.h"
using namespace cocos2d;
#define URL_HEAD "http://106.75.135.78:1701" ///外网
//#define URL_HEAD "http://172.23.1.40:1701"
#define URL_BASECONFIG  "/config/get/base"
#define URL_REGISTER  "/user/hello"
#define URL_LOGIN  "/user/login"
#define URL_PAY  "/mo/order/booking"
#define URL_CANCELORDER "/mo/order/cancel"
#define URL_SYNCINFO  "/player/info/sync/fortuneInfo"
#define URL_SETNAME  "/user/nickname"
#define URL_FEEDBACK "/help/feedback"
#define URL_LOGEVENTFISH "/statistics/data"
#define URL_DEMANDENTRY "/mr/order/result"
#define URL_BROKE "/bankrupt/broke"
#define URL_REBRITH "/bankrupt/rebirth"
#define URL_PLAYERINFO "/player/info/get"
#define URL_ITEMINFO "/player/info/bag/get"
#define URL_BUYITEM "/player/info/bag/buy"
#define URL_BIND "/user/nickname/bind/"
#define URL_BYNICKNAME "/user/nickname/login"
#define URL_REGISTERFORWARDLY "/user/register"
#define URL_CDKEY "/cdkey/get"
#define URL_OPENBOX "/bag/chest/get"
#define URL_GETMISSIONLIST "/gametask/everyday"
#define URL_GETMISSIONREWARD "/gametask/everyday/getreward"
#define URL_GETACHIEVELIST "/gametask/achievement"
#define URL_GETACHIEVEREWARD "/gametask/achievement/getreward"
#define URL_GETNACTIVEINFO "/activity/config"
#define URL_GETNOBILITYINFO "/nobility/surplus"
#define URL_GETNOBILITYREWARD "/nobility/today/reward"
struct setNameRequest
{
	const char* nickname;
	int gender;
};
enum HTTP_TYPE
{
	Req_Register,
	Req_Login,
	Req_LoginByName,
	Req_BeforePay,
	Req_AfterPay,
	Req_SyncInfo,
	Req_SetName,
	Req_BindName,
	Req_FeedBack,
	Req_DemandEntry,
	Req_CancelOrder,
	Req_GetUserInfo,
	Req_GetItemInfo,
	Req_BuyItem

};
class HttpMannger {

public:
	static HttpMannger* getInstance();
	
	void HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, const char* hd_type, const char* hd_factory);//注册请求
	void onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestRegisterForwardly(const char*nickname, const char* password, int gender,std::string channelId, const char* imei, const char* hd_type, const char* hd_factory);//注册请求
	void onHttpRequestCompletedForRegisterForwardly(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestLogInInfo(std::string channelId, std::string username, const char* imei, const char* hd_type, const char* hd_factory);//登录请求
	void onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestLogInByName(const char*nickname, const char* password);//账号登录
	void onHttpRequestCompletedForLogInByName(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestSyncInfo(std::string sessionid, int coin, int diamond, int exp,int maxTurretLevel,int PayRMB,int nobillityCount);//上传同步信息
	void onHttpRequestCompletedForSyncInfo(HttpClient *sender, HttpResponse *response);



	void HttpToPostRequestBindName(const  char* nickname, int gender,const char* password);//绑定账号
	void onHttpRequestCompletedForBindName(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestFeedback(const  char* feedback);//用户反馈	
	void onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response);

//----------------------------------------PAY BEGIN--------------------------------------------------
	void HttpToPostRequestBeforePay(int paythirdtype,std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, std::string pay_point_desc, int price, int result = 0, const char* orderid = "0", int paytype = 0);//下单
	void onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestAfterPay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int price, int result, const char* orderid, int paytype = 1);//上传购买信息
	void onHttpRequestCompletedForAfterPay(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestDemandEntry(std::string prepayid, int reqNum);//用户支付完后查询订单	
	void onHttpRequestCompletedForDemandEntry(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestCancelOrder(std::string orderid);//关闭订单订单	
	void onHttpRequestCompletedForCancelOrder(HttpClient *sender, HttpResponse *response);
//----------------------------------------PAY END--------------------------------------------------




	void HttpToPostRequestToGetUserInfo(); //获取用户信息
	void onHttpRequestCompletedForGetUserInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetItemInfo(bool isOpenBag); //获取用户背包道具数量
	void onHttpRequestCompletedForGetItemInfo(HttpClient *sender, HttpResponse *response);
	
	void HttpToPostRequestToBuyItem(int itemid); //背包购买道具
	void onHttpRequestCompletedForBuyItem(HttpClient *sender, HttpResponse *response);

	//数据埋点
	void HttpToPostRequestLogEvent(std::string jsonString,int type); //type: 1鱼群2破产3美人鱼4界面跳转5赠送6技能使用7炮台升级	
	void onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestCDKey(std::string cdkey); //兑换码
	void onHttpRequestCompletedForCDKey(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestOpenBox(int itemid); //开宝箱
	void onHttpRequestCompletedForOpenBox(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetMissionList(); //获取任务列表
	void onHttpRequestCompletedForGetMissionList(HttpClient *sender, HttpResponse *response);
	
	void HttpToPostRequestGetMissionReward(int missionId); //领取任务奖励
	void onHttpRequestCompletedForGetMissionReward(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetNobilityInfo(); //获取用户贵族天数
	void onHttpRequestCompletedForGetNobilityInfo(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetNobilityReward(); //领取贵族奖励
	void onHttpRequestCompletedForGetNobilityReward(HttpClient *sender, HttpResponse *response);


	void HttpToPostRequestToGetActiveInfo(); //获取活动信息
	void onHttpRequestCompletedForGetActiveInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetUrlImg(std::string url); //获取网络图片
	void onHttpRequestCompletedForGetUrlImg(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestToGetAchieveInfo(); //获取成就列表
	void onHttpRequestCompletedForToGetAchieveInfo(HttpClient *sender, HttpResponse *response);

	void HttpToPostRequestGetAchieveReward(int missionId); //领取任务奖励
	void onHttpRequestCompletedForGetAchieveReward(HttpClient *sender, HttpResponse *response);
private:
	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


