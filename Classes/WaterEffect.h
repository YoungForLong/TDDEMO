#pragma once
#include "cocos2d.h"

USING_NS_CC;

namespace Effect {

	class WaterEffect :public Sprite
	{
	public:
		WaterEffect();
		~WaterEffect();
	public:
		static WaterEffect* create(const std::string& pszFileName);
	public:
		bool initWithTexture(Texture2D* texture, const Rect& rect) override;
		void initGLProgram();
	};

}
