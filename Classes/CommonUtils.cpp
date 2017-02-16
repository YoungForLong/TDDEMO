#include "CommonUtils.h"
#include "tinyxml2\tinyxml2.h"

bool CommonUtils::A_is_belong_to_B(string A, string B)
{
	return false;
}

float CommonUtils::transformHeadingToRotation(const Vec2 & heading)
{
	return 90 - heading.getAngle() * 180 / PI;
}

void CommonUtils::loadConfigAsync(function<void()> callback)
{
	thread loadAsync = thread([this,&callback]() {
		_mut.lock();
		//加载文件目录
		auto filevmap = FileUtils::getInstance()->getValueMapFromFile("gameData.plist");
		
		//加载每个文件
		for (auto iter = filevmap.begin(); iter != filevmap.end(); ++iter)
		{
			string eachfile = iter->second.asString();

			string typeName = "";
			for (int i = 0; i < eachfile.size()-6; ++i)
			{
				typeName += eachfile[i];
			}

			auto fileMap = FileUtils::getInstance()->getValueMapFromFile(eachfile + ".plist");

			_config.insert(make_pair(string_to_type[typeName], fileMap));
		}

		_mut.unlock();

		callback();
	});

	loadAsync.join();
}

Value CommonUtils::getConfigByKey(ObjectType type,const std::string & key)
{
	auto thisTypeConfig = _config[type];
	
	return thisTypeConfig[key];
}

string CommonUtils::type_to_string(const ObjectType & typeStr) const
{
	for (auto iter = string_to_type.begin(); iter != string_to_type.end(); ++iter)
	{
		if (iter->second == typeStr)
		{
			return iter->first;
		}
	}

	return "nullstr";
}
