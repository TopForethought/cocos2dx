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
// 5,风车转动,随机施加阻力,这里没有使用随机数,主要是在定时器中决定是否给风车事假角速度阻力

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
