#ifndef _COMMON_UTILS_H_
#define _COMMON_UTILS_H_
#include "Singleton.h"
#include "cocos2d.h"
#include "CommonEnum.h"
#include <thread>
#include <mutex>
#include <functional>
#include <map>
#include <initializer_list>

using namespace cocos2d;

class CommonUtils :public Singleton<CommonUtils>
{
public:
	std::map<ObjectType,ValueMap> _config;

	//readonly
	map<string, ObjectType> string_to_type = {
		{ "ship", ship },
		{ "bullet", bullet },
		{ "stone_bullet", stone_bullet }
	};

	bool A_is_belong_to_B(string A, string B);

	float transformHeadingToRotation(const Vec2& heading);

	void loadConfigAsync(function<void()> callback);

	Value getConfigByKey(ObjectType type,const std::string& key);

	string type_to_string(const ObjectType& typeStr)const;

	template<class T>
	T multiMin(T arg, ...)
	{
		va_list argArr;
		T temp;
		T minArg = arg;

		va_start(argArr, arg);
		while (temp)
		{
			temp = va_arg(argArr, T);

			if (minArg > temp)
			{
				minArg = temp;
			}
		}
		va_end(argArr);

		return minArg;
	}

	template<class T>
	T multiMax(T arg, ...)
	{
		va_list argArr;
		T temp;
		T maxArg = arg;

		va_start(argArr, arg);
		while (temp)
		{
			temp = va_arg(argArr, T);

			if (maxArg < temp)
			{
				maxArg = temp;
			}
		}
		va_end(argArr);

		return maxArg;
	}
private:
	mutex _mut;

//public:
//	vector<float> testNumArr;
};

#define CU CommonUtils::instance()

#endif // ! _COMMON_UTILS_H_
