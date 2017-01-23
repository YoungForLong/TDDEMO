#include "WaterEffect.h"

using namespace Effect;

WaterEffect::WaterEffect()
{
}


WaterEffect::~WaterEffect()
{
}


WaterEffect* WaterEffect::create(const char *pszFileName) {
	auto pRet = new (std::nothrow) WaterEffect();
	if (pRet && pRet->initWithFile(pszFileName)) {
		pRet->autorelease();
	}
	else {
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool WaterEffect::initWithTexture(Texture2D* texture, const Rect& rect) {
	Texture2D::TexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	texture->setTexParameters(&texParams);

	if (Sprite::initWithTexture(texture, rect)) {
		

#if CC_ENABLE_CACHE_TEXTURE_DATA  
		auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event) {
			setGLProgram(nullptr);
			initGLProgram();
		});

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif   
		initGLProgram();
		return true;
	}

	return false;
}

void WaterEffect::initGLProgram() {
	auto fragSource = (GLchar*)String::createWithContentsOfFile(
		FileUtils::getInstance()->fullPathForFilename("water_effect.fsh").c_str())->getCString();
	auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);

	auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
	setGLProgramState(glProgramState);

	auto normalMapTextrue = TextureCache::getInstance()->addImage("water_normal.jpg");
	Texture2D::TexParams texParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	normalMapTextrue->setTexParameters(&texParams);
	getGLProgramState()->setUniformTexture("u_normalMap", normalMapTextrue);

}
