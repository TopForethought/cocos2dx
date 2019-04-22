#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
#define PHYSICS_MATERIAL1  PhysicsMaterial(1,1,0)
#define PHYSICS_MATERIAL2  PhysicsMaterial(1,0.9,0)
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	// 创建带物理特性的世界
	auto  scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
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


	// 瞄准镜 ************************************************************8
	// 开 :使用大图
	//auto smallPic = Sprite::create("aim/forest512.jpg");
	
	//back->setPosition(visibleSize / 2);
	//addChild(back);
	// 截取小图
	//auto clipSmall = ClippingNode::create();
	//
	//clipSmall->setPosition(visibleSize / 2);
	//auto aimArea = Sprite::create("aim/sniperscopeA.png");
	//clipSmall->addChild(smallPic);
	//clipSmall->setStencil(aimArea);
	//clipSmall->setAlphaThreshold(0.5);
	//clipSmall->setInverted(true);

	//addChild(clipSmall);


	//// 截取大图
	//auto  biPic = Sprite::create("aim/forest2048.jpg");
	//auto clipBi = ClippingNode::create();

	//clipBi->setPosition(visibleSize / 2);
	//auto aimAreaBi = Sprite::create("aim/aimAreaA.png");
	//clipBi->addChild(biPic);
	//clipBi->setStencil(aimAreaBi);
	//clipBi->setAlphaThreshold(0.5);
	//clipBi->setInverted(false);
	//addChild(clipBi);
	//// 瞄准镜实现逻辑:  光标在小图上移动,将光标当前位置的小图截取使用大图截取的遮盖

	//auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	//listener->onTouchBegan = [=](Touch * touch, Event *event) {

	//	return true;
	//};
	//listener->onTouchMoved = [=](Touch * touch,Event *event) {
	//	auto target = static_cast<Sprite *>(event->getCurrentTarget());
	//	Point touchLocation = touch->getLocation();
	//	Point locationNode = target->getContentSize();
	//	log("touchDelata:%f,%f",touch->getDelta().x,touch->getDelta().y);
	//	aimArea->setPosition(aimArea->getPosition()+touch->getDelta());
	//	biPic->setPosition(biPic->getPosition() - touch->getDelta() * 3);
	//	aimAreaBi->setPosition(aimAreaBi->getPosition() + touch->getDelta());
	//	
	//	//aimAreaBi->setPosition(1,1);
	//	
	//	return true;


	//};
	//Director::getInstance()->getEventDispatcher()->
	//	addEventListenerWithSceneGraphPriority(listener, smallPic);


	//1, 重力 小球下落不断反弹********************

        auto rootNode = CSLoader::createNode("MainScene.csb");
		Sprite * edgeBox = dynamic_cast<Sprite*>(rootNode->getChildByName("Default"));

		auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICS_MATERIAL1,3);
		edgeBody->setDynamic(false);
		edgeBox->setPhysicsBody(edgeBody);
		addChild(rootNode);
		auto redBall = rootNode->getChildByName("redBall");
		auto ballBody = PhysicsBody::createCircle(20, PHYSICS_MATERIAL2);
		ballBody->setDynamic(true);// 设置不固定
		redBall->setPhysicsBody(ballBody);
// 2,小球斜抛
		/*ballBody->setVelocity(Vec2(-1000, 1000));
		ballBody->setVelocityLimit(600);*/
// 3,小鸟飞行,空格向上飞,扑动翅膀,松开下落  *******************
		//auto bird = Sprite::create("myBird.png",Rect(0, 0, 130, 100));
		//bird->setPosition(origin.x+bird->getContentSize().width,origin.y+540);
		//auto birdBody = PhysicsBody::createEdgeBox(bird->getContentSize(), PHYSICS_MATERIAL2,3);
		//birdBody->setDynamic(true);
		//bird->setPhysicsBody(birdBody);
		//auto toRight = MoveBy::create(1, Vec2(100, 0));
		//bird->runAction(RepeatForever::create(toRight));

		//addChild(bird);
		//// 飞行动画
		//Vector<SpriteFrame *> frames(2);
		//frames.pushBack(Sprite::create("myBird.png", Rect(0, 0, 130, 100))->getSpriteFrame());
		//frames.pushBack(Sprite::create("myBird.png", Rect(130, 0, 130, 100))->getSpriteFrame());
		//Animate* animate = Animate::create(Animation::createWithSpriteFrames(frames,0.2f));
		////bird->runAction(RepeatForever::create(animate));

		//auto * listener = EventListenerKeyboard::create();
		//listener->onKeyPressed=[=](EventKeyboard::KeyCode code, Event* event){
		//
		//	if (code == EventKeyboard::KeyCode::KEY_SPACE) {
		//		Animate* animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.2f));
		//		bird->runAction(Repeat::create( animate,2));
		//		birdBody->applyForce(Vec2(0, 4000));
		//		birdBody->setVelocity(Vec2(0, 0));
		//		bird->setPosition(bird->getPosition() + Vec2(0, 20));
		//	}
		//	return true;
		//
		//};
		//listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {

		//	if (code == EventKeyboard::KeyCode::KEY_SPACE) {
		//		//Animate* animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.2f));
		//		//bird->runAction(Repeat::create(animate, 4));
		//		birdBody->setVelocity(Vec2(0, 0));
		//	}
		//	return true;
		//};
		//Director::getInstance()->getEventDispatcher()->
		//	addEventListenerWithSceneGraphPriority(listener, this);

		//4 ,台球,红球位于中央,摩擦系数10000
		// 给求一个速度让球运动
	//	ballBody->setVelocity(Vec2(200, 0));
// 5,风车转动,随机施加阻力

	Sprite * phnwheel=	dynamic_cast<Sprite *>(rootNode->getChildByName("pinwheel"));
	//phnwheel->runAction(RepeatForever::create(RotateBy::create(3, 360)));
	pinwheelBody = PhysicsBody::createBox(phnwheel->getContentSize(), PHYSICS_MATERIAL2,Vec2(0,0));
	pinwheelBody->setAngularVelocityLimit(6);
	pinwheelBody->setDynamic(true);
	phnwheel->setPhysicsBody(pinwheelBody);

	schedule(schedule_selector(HelloWorld::myCallback), 2.0f);
		return true;
}
void HelloWorld::myCallback(float dt) {
	
	//this.pinwheelBody->setPhysicsBody(-10);
//	pinwheelBody->setAngularDamping(2);
	m_lTimer++;
	if (m_lTimer > m_maxTime) {
		m_maxTime = 1;
	}
	//给速度
	if (m_lTimer % 17 == 0) {
		pinwheelBody->setAngularVelocity(-6);
		pinwheelBody->setAngularDamping(0);
		log("hello  speed");
	}
	////给阻力
	if (m_lTimer % 13 == 0) {
		pinwheelBody->setAngularDamping(0.5);
		log("damping");
	}

	log("hello %f",time);
}