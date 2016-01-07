#include "config/ConfigOnemoment.h"

ConfigOnemoment* ConfigOnemoment::_instance = NULL;

ConfigOnemoment::ConfigOnemoment(){
}

ConfigOnemoment* ConfigOnemoment::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigOnemoment();
	}
	return _instance;
}

std::list<OneMoment> ConfigOnemoment::LoadConfig(std::string filename) {
    
    std::list<OneMoment> oneMoments;
    
	bool bRet = false;
	while (!bRet) {

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
            
			OneMoment oneMoment;
			oneMoment.fishgroup_id	= val["fishgroup_id"].GetInt();
            oneMoment.start_time = val["start_time"].GetDouble();
            oneMoment.end_time = val["end_time"].GetDouble();
            oneMoment.start_position_x = val["start_position_x"].GetInt();
            oneMoment.start_position_y = val["start_position_y"].GetInt();
            oneMoment.end_position_x = val["end_position_x"].GetInt();
            oneMoment.end_position_y = val["end_position_y"].GetInt();
            oneMoment.move_type = val["move_type"].GetInt();

			oneMoments.push_back(oneMoment);
		}
		
		return oneMoments;
	}
    return oneMoments;
}

