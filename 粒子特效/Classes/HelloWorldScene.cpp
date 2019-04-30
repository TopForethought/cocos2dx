#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
PhysicsWorld * world;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
   // auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	world = scene->getPhysicsWorld();
	scene->getPhysicsWorld()->setGravity(Vec2(0,-980));
	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    
	//"Rain960x640.jpg"
	auto bgNode = Sprite::create("Rain960x640.jpg");
	bgNode->setAnchorPoint(Vec2(0, 0));
	
    addChild(bgNode);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 下雨特效
	ParticleRain * rain = ParticleRain::create();
	rain->setGravity(Vec2(0,-500));// 粒子重力方向,这和场景的重力是独立的,互不影响
	//->setRadialAccel(100);// 径向加速度
	rain->setPosVar(Vec2(1000, 0));// 发射点坐标可变相对位置
	//rain->setAutoRemoveOnFinish(true);
	rain->setEmissionRate(1000); // 一次发射的粒子数
	rain->setTotalParticles(10000);//总共可用粒子数
	rain->setDuration(-1);// -1 表示特效一直有,其他正数表示特效持续时间
	//rain->setScale(1.5);
	rain->setLife(3);//粒子生命周期
	rain->setLifeVar(3);// 在周期的基础上+-3  也就是最终粒子的生命周期是 0-6秒的
	//rain->setAngle(-30);
	addChild(rain);

	////下雪特效

	//ParticleSnow * snow = ParticleSnow::create();
	////addChild(snow);
	//snow->setGravity(Vec2(-20, -100));
	//snow->setEmissionRate(200);
	//snow->setTotalParticles(1000);
	//snow->setPosVar(Vec2(1500, 0));
	/*snow->setLife(5);
	snow->setLifeVar(3);*/


	 //1 蜡烛 *******************************************
	//auto candle = Sprite::create("CandleHolder.png");
	//candle->setAnchorPoint(Vec2(0.5, 0));
	//candle->setPosition(visibleSize.width/2,0);
	//addChild(candle);
	//// 火焰特效 
	//ParticleFire * fire = ParticleFire::create();
	//fire->setPosVar(Vec2(10,0));// 设置粒子发射点位置范围,(0,0)表示就一个点,如果是(20,0)
	//// 则表示 x是在 (-20,20)区间,y 都为0的位置 (这是相对位置)

	//fire->setSpeed(40);

	//fire->setLife(3);
	//fire->setEmissionRate(50);
	//fire->setLifeVar(3);
	//fire->setAngleVar(10);
	//fire->setPosition(visibleSize / 2+Size(-40,140));
	//addChild(fire);


	//// 2 飞机尾焰************************

	//auto rocket = Sprite::create("Rocket.png");
	//rocket->setPosition(visibleSize.width/2,10);
	//addChild(rocket);
	//PhysicsBody * rocketBody = PhysicsBody::createBox(rocket->getContentSize());
	//rocket->setPhysicsBody(rocketBody);

	//// 
	//ParticleSystemQuad * sq = ParticleSystemQuad::create("particle_texture.plist");

	//sq->setPosition(rocket->getPosition()+Size(0,-60));
	//PhysicsBody * sqBody = PhysicsBody::createBox(sq->getContentSize());
 //    sq->setPhysicsBody(sqBody);
	// rocketBody->setCategoryBitmask(0);
 //    //rocketBody->setVelocity(Vec2(0, 100));
	// 
	//// sqBody->setVelocity(Vec2(0, 100));// 不设置速度,依靠反向重力加速
	// sq->setTotalParticles(1000);//总共粒子数1000,是循环使用的
	// sq->setEmissionRate(100);//粒子发射率,比如每秒放出100个
	// sq->setPosVar(Vec2(0, 0));
	// sq->setAngleVar(0);
	//// sq->setAngle(-60);
	// addChild(sq);
	//
	// // 将粒子与火箭绑定
	// PhysicsJoint *joint = PhysicsJointDistance::construct(rocketBody, sqBody, Vec2(0.5, 0), Vec2(0.5, 1));
	// world->addJoint(joint);

    return true;
}
