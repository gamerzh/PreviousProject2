#include "config/ConfigBankrupt.h"

ConfigBankrupt* ConfigBankrupt::_instance = NULL;

ConfigBankrupt::ConfigBankrupt(){
}

ConfigBankrupt* ConfigBankrupt::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigBankrupt();
	}
	return _instance;
}

bool ConfigBankrupt::LoadConfig() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_bankrupt.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigBankrupt get json data err!");
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
            
			Bankrupt bankrupt;
			bankrupt.coins	= val["coins"].GetInt();
            bankrupt.wait_time	= val["wait_time"].GetInt();
           
            bankrupts.push_back(bankrupt);
		}
		
		return true;
	}
    return true;
}

std::vector<Bankrupt> ConfigBankrupt::getBankrupts() {
    return bankrupts;
}


