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
	// �������������Ե�����
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


	


	//1, �����߿�,�������ʱ�۲�

        auto rootNode = CSLoader::createNode("MainScene.csb");
		Sprite * edgeBox = dynamic_cast<Sprite*>(rootNode->getChildByName("Default"));

		auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICS_MATERIAL1,3);
		edgeBody->setDynamic(false);
		edgeBox->setPhysicsBody(edgeBody);
		addChild(rootNode);

		// ����С������ϵͳ

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

		// ���ùؽ�
		// ����ֻ�����µ��� ,�����복����ײ
		// ʹ��С��ײ������⳵�ֵ�����Χ
		auto redBall = rootNode->getChildByName("redBall");
		PhysicsBody * ballBody = PhysicsBody::createCircle(20, PHYSICS_MATERIAL1);
		redBall->setPhysicsBody(ballBody);
		//ballBody->setVelocity(Vec2(0, 100));
		//carBody->setDynamic(false);
		// ��������A
		PhysicsJoint * pj1 = PhysicsJointRotarySpring::construct(carBody, wheelABody,1000, 500);
		world->addJoint(pj1);
		PhysicsJoint * pj11 = PhysicsJointGroove::construct(carBody, wheelABody
			, Vec2(-80,-110) ,Vec2(-80,-90), Vec2(0.5,0.5));
		world->addJoint(pj11);
		// ��������B
		PhysicsJoint * pj2 = PhysicsJointRotarySpring::construct(carBody, wheelBBody, 1000,500);
		world->addJoint(pj2);
         // �۹ؽ�,�����������µ�����������ĳ���߶���
		// ����,����,�߶����,�յ�,����ê��
		PhysicsJoint * pj22 = PhysicsJointGroove::construct(carBody, wheelBBody
			, Vec2(80, -110), Vec2(80, -90), Vec2(0.5, 0.5));
		world->addJoint(pj22);
		// A B ��Խ��ٶȱ���һ��
		PhysicsJoint * pj3 = PhysicsJointGear::construct(wheelABody, wheelBBody, 0, 1);
		world->addJoint(pj3);
		// ���Լ�������ת
		carBody->setCategoryBitmask(0);

	
		// ����ǰ��ʻ(ֻ��Ҫͨ��������������,�����з������󼴿�)
		
		// �̶���
		ballBody->setDynamic(false);
	

		return true;
}
