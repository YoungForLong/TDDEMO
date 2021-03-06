#include "AppDelegate.h"
#include "Test.h"
#include "GlobalTime.h"
#include "CommonUtils.h"
#include "WorldMap.h"

USING_NS_CC;

static cocos2d::Size tinyTestSize = cocos2d::Size(720, 400);
static cocos2d::Size halfTestSize = cocos2d::Size(1366, 768);
static cocos2d::Size designResolutionSize = cocos2d::Size(1366,768);


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    
#pragma region yyh
	//init time
	GT->init();
	//init data
	CU->loadConfigAsync([]() { 
		auto& config = CU->_config;

		for (auto typeIter = config.begin(); typeIter != config.end(); ++typeIter)
		{
			auto& eachConfig = typeIter->second;
			CCLOG("typename: %s", CU->type_to_string(typeIter->first).c_str());
			for (auto iter = eachConfig.begin(); iter != eachConfig.end(); ++iter)
			{
				CCLOG("%s: %s",iter->first.c_str(), iter->second.asString().c_str());
			}
		}
	
	});
	
	WorldMap::instance()->init();

#pragma endregion
	
	// initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("TDDEMO", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("TDDEMO");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);
    auto frameSize = glview->getFrameSize();

	if (Platform::OS_WINDOWS == getTargetPlatform())
	{
		glview->setFrameSize(designResolutionSize.width, designResolutionSize.height);
	}

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = TestLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
