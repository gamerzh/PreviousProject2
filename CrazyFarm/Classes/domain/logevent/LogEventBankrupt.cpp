#include "LogEventBankrupt.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventBankrupt* LogEventBankrupt::_instance = NULL;

LogEventBankrupt::LogEventBankrupt(){
    
}

void LogEventBankrupt::init(int roomid){
	m_roomid = roomid;
	m_type = -1;
	m_num = -1;

}

LogEventBankrupt* LogEventBankrupt::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventBankrupt();
    }
    return _instance;
}



std::string LogEventBankrupt::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	
	document.AddMember("room_id",m_roomid, allocator);
	document.AddMember("type", m_type, allocator);
	document.AddMember("nums", m_num, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventBankrupt::sendDataToServer(int type,int num)
{
	m_type = type;
	m_num = num;
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(),4);
}