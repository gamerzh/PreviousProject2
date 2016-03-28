#include "MsgOnAdd.h"

void Msg_onAdd::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	rapidjson::Value& userinfo = doc["user_info"];
	username = userinfo["username"].GetString();
	coins = userinfo["coins"].GetUint();
	diamonds = userinfo["diamonds"].GetUint();
	turrent_level = userinfo["turrent_level"].GetInt();
	vip_level = userinfo["vip_level"].GetInt();
	box_level = userinfo["box_level"].GetInt();
	roomPos = userinfo["pos"].GetInt();

}