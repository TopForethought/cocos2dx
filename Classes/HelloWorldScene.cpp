#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
  
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
   /* auto rootNode = CSLoader::createNode("MainScene.csb");
	
    addChild(rootNode);*/

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//  1.文字菜单*****************************************************************
	/*MenuItemFont::setFontName("Times New Rowman");
	MenuItemFont::setFontSize(80);

	MenuItem *item1 = MenuItemFont::create("Start",
		[=](Ref * pSend) {log("Start"); }
	);
	MenuItem *item2 = MenuItemFont::create("Quit",
		[=](Ref * pSend) {log("Quit"); }
	);
	auto menu = Menu::create(item1, item2, NULL);
	menu->alignItemsVertically();
	addChild(menu);*/
	//2. checkbox 类型菜单(开关)
	//auto lightOn = MenuItemImage::create("OnA.png", "OnA.png");
	//auto lightOff = MenuItemImage::create("signalLight.png", "signalLight.png");
	//auto onOffMenu = MenuItemToggle::createWithCallback([=](Ref * pSend) {
	//	auto item = (MenuItemToggle*)pSend;
	//	int index = item->getSelectedIndex();
	//	if (1 == index) {
	//		log("Light on");
	//	}
	//	else {
	//		log("Light off");
	//	}
	//	//log("index:%d" , index);
	//},lightOff,lightOn,NULL);
	//auto menu = Menu::create(onOffMenu, NULL);
	//menu->setPosition(Point(200, 200));
	//addChild(menu, 2);


	// 3, 图片菜单*****************************************************************//
	/*auto  mi1 = MenuItemImage::create("img1n.png", "img1s.png", "img1d.png",
		[=](Ref * pSend){
		log("IMG1 ok!");
	});
	mi1->setPosition(0, 100);
	auto  mi2 = MenuItemImage::create("img2n.png", "img2s.png", "img2d.png",
		[=](Ref * pSend) {
		log("IMG2 ok!");
	});

	mi2->setPosition(0, 200);
	auto menu = Menu::create(mi1, mi2, NULL);
	addChild(menu, 2);*/
	// 4 sprite 菜单,可以设置动画  *****************************************************************
	//auto plane1N = Sprite::create("planen1.png");
	//auto plane1S = Sprite::create("planeS1.png");
	//auto plane1D = Sprite::create("planed1.png");
	//auto plane2N = Sprite::create("planen2.png");
	//auto plane2S = Sprite::create("planeS2.png");
	//auto plane2D = Sprite::create("planed2.png");

	//auto item1=MenuItemSprite::create(plane1N, plane1S, plane1D,
	//	[=](Ref * pSend) {
	//	log("sp ok");
	//});
	//
	//auto menu = Menu::create(item1, NULL);
	//addChild(menu);
	//// 加上动画
	//Vector<SpriteFrame *>framesN(2);
	//framesN.pushBack(Sprite::create("planen1.png")->getSpriteFrame());
	//framesN.pushBack(Sprite::create("planen2.png")->getSpriteFrame());
	//Vector<SpriteFrame *>framesS(2);
	//framesS.pushBack(Sprite::create("planeS1.png")->getSpriteFrame());
	//framesS.pushBack(Sprite::create("planeS2.png")->getSpriteFrame());
	//
	//plane1N->runAction(RepeatForever::create(
	//	Animate::create(Animation::createWithSpriteFrames(framesN, 0.07))));

	//plane1S->runAction(RepeatForever::create(
	//	Animate::create(Animation::createWithSpriteFrames(framesS, 0.07))));


	// 裁剪节点类
	// 弹孔效果
	//auto clip = ClippingNode::create();// 裁剪节点
	//auto plate = Sprite::create("holes/ABCD.png");
	//auto hole = Sprite::create("holes/Hole.png");
	//auto point = Sprite::create("holes/Point.png");
	//clip->setPosition(visibleSize / 2);
	//clip->addChild(plate);
	//clip->addChild(hole);

	//clip->setStencil(point);//按照point的模样抠图
	//clip->setAlphaThreshold(0.5);
	//clip->setInverted(true);
	//addChild(clip);


	// 瞄准镜
	// 开 :使用大图
	auto smallPic = Sprite::create("aim/forest512.jpg");
	
	//back->setPosition(visibleSize / 2);
	//addChild(back);
	// 截取小图
	auto clipSmall = ClippingNode::create();
	
	clipSmall->setPosition(visibleSize / 2);
	auto aimArea = Sprite::create("aim/sniperscopeA.png");
	clipSmall->addChild(smallPic);
	clipSmall->setStencil(aimArea);
	clipSmall->setAlphaThreshold(0.5);
	clipSmall->setInverted(true);

	addChild(clipSmall);


	// 截取大图
	auto  biPic = Sprite::create("aim/forest2048.jpg");
	auto clipBi = ClippingNode::create();

	clipBi->setPosition(visibleSize / 2);
	auto aimAreaBi = Sprite::create("aim/aimAreaA.png");
	clipBi->addChild(biPic);
	clipBi->setStencil(aimAreaBi);
	clipBi->setAlphaThreshold(0.5);
	clipBi->setInverted(false);
	addChild(clipBi);
	// 瞄准镜实现逻辑:  光标在小图上移动,将光标当前位置的小图截取使用大图截取的遮盖

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch * touch, Event *event) {

		return true;
	};
	listener->onTouchMoved = [=](Touch * touch,Event *event) {
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		Point touchLocation = touch->getLocation();
		Point locationNode = target->getContentSize();
		log("touchDelata:%f,%f",touch->getDelta().x,touch->getDelta().y);
		aimArea->setPosition(aimArea->getPosition()+touch->getDelta());
		biPic->setPosition(biPic->getPosition() - touch->getDelta() * 3);
		aimAreaBi->setPosition(aimAreaBi->getPosition() + touch->getDelta());
		
		//aimAreaBi->setPosition(1,1);
		
		return true;


	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, smallPic);
    return true;
}
