#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
#define PHYSICS_MATERIAL1  PhysicsMaterial(1,1,0)
#define PHYSICS_MATERIAL2  PhysicsMaterial(1,0,0)
PhysicsWorld * world;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	// 创建带物理特性的世界
	auto  scene = Scene::createWithPhysics();
	world = scene->getPhysicsWorld();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -980));
	//scene->getPhysicsWorld()->setAutoStep(false);
	//PhysicsWorld::DEBUGDRAW_JOINT
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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


	


	//1, 重力 小球下落不断反弹********************

        auto rootNode = CSLoader::createNode("MainScene.csb");
		Sprite * edgeBox = dynamic_cast<Sprite*>(rootNode->getChildByName("Default"));

		auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICS_MATERIAL1,3);
		edgeBody->setDynamic(false);
		edgeBox->setPhysicsBody(edgeBody);
		addChild(rootNode);

	      //   使用关节 实现绳子效果

		Sprite * nodes[10];
		PhysicsBody * bodys[10];
		PhysicsJointDistance * pjd[10];

		// 1. 固定第一个节点 

		nodes[0] = Sprite::create();
		Vec2 point(visibleSize.width / 2, 9* visibleSize.height /10);
		nodes[0]->setPosition(point);
		addChild(nodes[0]);
		bodys[0] = PhysicsBody::createCircle(20, PHYSICS_MATERIAL1);
		bodys[0]->setCategoryBitmask(0);
		bodys[0]->setDynamic(false);
		nodes[0]->setPhysicsBody(bodys[0]);
		
		for (int i = 1; i < 10; i++) {
			nodes[i] = Sprite::create("rope05HA.png");
			nodes[i]->setPosition(point.x+40*i,point.y);
			addChild(nodes[i]);
			bodys[i]= PhysicsBody::createCircle(20, PHYSICS_MATERIAL1);
			bodys[i]->setCategoryBitmask(0);
			nodes[i]->setPhysicsBody(bodys[i]);
			pjd[i - 1] = PhysicsJointDistance::construct(bodys[i - 1], bodys[i], Vec2(30,0), Vec2(-30, 0));
			world->addJoint(pjd[i - 1]);// 将关节加入世界
		}




		return true;
}
