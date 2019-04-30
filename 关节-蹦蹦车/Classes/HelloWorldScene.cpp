#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
#define PHYSICS_MATERIAL1  PhysicsMaterial(1,1,0.2)
#define PHYSICS_MATERIAL2  PhysicsMaterial(1,0,0.2)
PhysicsWorld * world;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	// 创建带物理特性的世界
	auto  scene = Scene::createWithPhysics();
	world = scene->getPhysicsWorld();
	scene->getPhysicsWorld()->setGravity(Vec2(-400,-980));
	//scene->getPhysicsWorld()->setAutoStep(false);
	//PhysicsWorld::DEBUGDRAW_JOINT
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
  
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
   /* auto rootNode = CSLoader::createNode("MainScene.csb");
	
    addChild(rootNode);*/

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	


	//1, 场景边框,方便调试时观察

        auto rootNode = CSLoader::createNode("MainScene.csb");
		Sprite * edgeBox = dynamic_cast<Sprite*>(rootNode->getChildByName("Default"));

		auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICS_MATERIAL1,3);
		edgeBody->setDynamic(false);
		edgeBox->setPhysicsBody(edgeBody);
		addChild(rootNode);

		// 测试小车悬挂系统

		auto car = rootNode->getChildByName("car");
		auto wheelA = rootNode->getChildByName("wheelA");
		auto wheelB = rootNode->getChildByName("wheelB");
		auto blueBox = rootNode->getChildByName("blueBox");

		auto carBody = PhysicsBody::createBox(car->getContentSize());
		//car->setAnchorPoint(Vec2(0, 0));
		car->setPhysicsBody(carBody);
		auto wheelABody = PhysicsBody::createCircle(wheelA->getContentSize().width/4, PHYSICS_MATERIAL2);
		wheelA->setPhysicsBody(wheelABody);
		auto wheelBBody = PhysicsBody::createCircle(wheelA->getContentSize().width/4, PHYSICS_MATERIAL2);
		wheelB->setPhysicsBody(wheelBBody);
		auto blueBody = PhysicsBody::createBox(blueBox->getContentSize());
		blueBody->setDynamic(false);
		blueBox->setPhysicsBody(blueBody);

		// 设置关节
		// 车轮只能上下弹动 ,车轮与车不碰撞
		// 使用小球撞击来检测车轮弹动范围
		auto redBall = rootNode->getChildByName("redBall");
		PhysicsBody * ballBody = PhysicsBody::createCircle(20, PHYSICS_MATERIAL1);
		redBall->setPhysicsBody(ballBody);
		//ballBody->setVelocity(Vec2(0, 100));
		//carBody->setDynamic(false);
		// 处理轮子A
		PhysicsJoint * pj1 = PhysicsJointRotarySpring::construct(carBody, wheelABody,1000, 500);
		world->addJoint(pj1);
		PhysicsJoint * pj11 = PhysicsJointGroove::construct(carBody, wheelABody
			, Vec2(-80,-110) ,Vec2(-80,-90), Vec2(0.5,0.5));
		world->addJoint(pj11);
		// 处理轮子B
		PhysicsJoint * pj2 = PhysicsJointRotarySpring::construct(carBody, wheelBBody, 1000,500);
		world->addJoint(pj2);
         // 槽关节,限制轮子上下弹动区间是在某条线段上
		// 车身,轮子,线段起点,终点,轮子锚点
		PhysicsJoint * pj22 = PhysicsJointGroove::construct(carBody, wheelBBody
			, Vec2(80, -110), Vec2(80, -90), Vec2(0.5, 0.5));
		world->addJoint(pj22);
		// A B 相对角速度保持一致
		PhysicsJoint * pj3 = PhysicsJointGear::construct(wheelABody, wheelBBody, 0, 1);
		world->addJoint(pj3);
		// 绕自己中心旋转
		carBody->setCategoryBitmask(0);

	
		// 车向前行驶(只需要通过调节重力即可,重力有分力向左即可)
		
		// 固定球
		ballBody->setDynamic(false);
	

		return true;
}
