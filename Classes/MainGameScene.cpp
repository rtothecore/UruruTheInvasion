#include "MainGameScene.h"
#include "UtilFunc.h"
#include "Resource.h"
#include "Alien.h"


//------------------------------------------------------------------
//
// MainGameScene
//
//------------------------------------------------------------------
bool MainGameScene::init()
{
	MainGameLayer *mainGameLayer = MainGameLayer::create();
    addChild(mainGameLayer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer
//
//------------------------------------------------------------------
bool MainGameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	addBackground();

    return true;
}

void MainGameLayer::onEnterTransitionDidFinish()
{
	addAliens(0);
	schedule( schedule_selector(MainGameLayer::addAliens), 4 );
}

void MainGameLayer::addBackground()
{
	Sprite* sprt = Sprite::create(s_Bg);
	sprt->setPosition(Point(UtilFunc::getWinSize().width / 2, UtilFunc::getWinSize().height / 2));
	this->addChild(sprt, 0);
}

void MainGameLayer::addAliens(float dt)
{
	for(int i=0; i<20; i++)
	{
		AlienLayer* alienL = AlienLayer::create();
		addChild(alienL);
	}
}