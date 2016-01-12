#include "config/ConfigNormalTurrent.h"

ConfigNormalTurrent* ConfigNormalTurrent::_instance = NULL;

ConfigNormalTurrent::ConfigNormalTurrent(){
}

ConfigNormalTurrent* ConfigNormalTurrent::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigNormalTurrent();
	}
	return _instance;
}

bool ConfigNormalTurrent::LoadConfig() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_normal_turrent.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];
            
			NormalTurrent normalTurrent;
			normalTurrent.normal_turrent_id	= val["normal_turrent_id"].GetInt();
            normalTurrent.turrent_ui_id	= val["turrent_ui_id"].GetInt();
            normalTurrent.unlock_turrent_level	= val["unlock_turrent_level"].GetInt();
            normalTurrent.net_per = val["net_per"].GetDouble();
            normalTurrent.catch_per = val["catch_per"].GetDouble();
            normalTurrent.ui_type = val["ui_type"].GetInt();
            normalTurrent.net_type = val["net_type"].GetInt();
            
            normalTurrents[i] = normalTurrent;
		}
		
		return true;
	}
    return true;
}


NormalTurrent ConfigNormalTurrent::getNormalTurrent(int maxTurrentLevel) {
    for(int i=normalTurrents.size() - 1; i>= 0;i--) {
        if(maxTurrentLevel >=  normalTurrents[i].unlock_turrent_level) {
            return normalTurrents[i];
        }
    }
    return normalTurrents[0];
}

