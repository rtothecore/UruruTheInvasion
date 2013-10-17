#include "AppDelegate.h"
#include "AppMacros.h"
#include "MainGameScene.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* director = Director::getInstance();
    EGLView* glView = EGLView::getInstance();

    director->setOpenGLView(glView);
    
    Size size = director->getWinSize();

	setDesignResolution();

    // Set the design resolution
	glView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	Scene *scene = MainTitleScene::create();
//#else
//    Scene *scene = HelloWorld::scene();
//#endif
	//Scene *scene = MainGameLayer::scene();	// TEST

	Scene *scene = TransitionFade::create(0.5, MainGameScene::create());
	Director::getInstance()->pushScene(scene);

    // run
    //director->runWithScene(scene);

    return true;
}

void AppDelegate::setDesignResolution()
{
	Director* director = Director::getInstance();
	EGLView* glView = EGLView::getInstance();

	Size frameSize = glView->getFrameSize();  
	vector<string> searchPath;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if (frameSize.height > small5Resource.size.height)
	{
		log("ipadhd resource selected");

		designResolutionSize = largeResource.size;
		searchPath.push_back(largeResource.directory);
		director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
	else if (frameSize.height > mediumResource.size.height)
	{
		log("iphone5 resource selected");

		designResolutionSize = small5Resource.size;
		searchPath.push_back(small5Resource.directory);
		director->setContentScaleFactor(MIN(small5Resource.size.height/designResolutionSize.height, small5Resource.size.width/designResolutionSize.width));
	}
	else if (frameSize.height > smallResource.size.height)
	{
		log("ipad resource selected");

		designResolutionSize = mediumResource.size;
		searchPath.push_back(mediumResource.directory);
		director->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
	}
	else if (frameSize.height > small3Resource.size.height)
	{
		log("iphone resource selected");

		designResolutionSize = smallResource.size;
		searchPath.push_back(smallResource.directory);
		director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
	}
	else
	{
		log("iphone3 resource selected");

		designResolutionSize = small3Resource.size;
		searchPath.push_back(small3Resource.directory);
		director->setContentScaleFactor(MIN(small3Resource.size.height/designResolutionSize.height, small3Resource.size.width/designResolutionSize.width));
	}
#else
	log("android resource selected");

	designResolutionSize = androidResource.size;
	searchPath.push_back(androidResource.directory);
	director->setContentScaleFactor(MIN(androidResource.size.height/designResolutionSize.height, androidResource.size.width/designResolutionSize.width));
#endif

	// set searching path
	FileUtils::getInstance()->setSearchPaths(searchPath);
}

// ORIGINAL
//bool AppDelegate::applicationDidFinishLaunching() {
//    // initialize director
//    Director* director = Director::getInstance();
//    EGLView* eglView = EGLView::getInstance();
//
//    director->setOpenGLView(eglView);
//	
//    // turn on display FPS
//    director->setDisplayStats(true);
//
//    // set FPS. the default value is 1.0/60 if you don't call this
//    director->setAnimationInterval(1.0 / 60);
//
//    // create a scene. it's an autorelease object
//    Scene *scene = HelloWorld::scene();
//
//    // run
//    director->runWithScene(scene);
//
//    return true;
//}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
