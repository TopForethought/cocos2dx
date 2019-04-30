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
	// ������Ч
	ParticleRain * rain = ParticleRain::create();
	rain->setGravity(Vec2(0,-500));// ������������,��ͳ����������Ƕ�����,����Ӱ��
	//->setRadialAccel(100);// ������ٶ�
	rain->setPosVar(Vec2(1000, 0));// ���������ɱ����λ��
	//rain->setAutoRemoveOnFinish(true);
	rain->setEmissionRate(1000); // һ�η����������
	rain->setTotalParticles(10000);//�ܹ�����������
	rain->setDuration(-1);// -1 ��ʾ��Чһֱ��,����������ʾ��Ч����ʱ��
	//rain->setScale(1.5);
	rain->setLife(3);//������������
	rain->setLifeVar(3);// �����ڵĻ�����+-3  Ҳ�����������ӵ����������� 0-6���
	//rain->setAngle(-30);
	addChild(rain);

	////��ѩ��Ч

	//ParticleSnow * snow = ParticleSnow::create();
	////addChild(snow);
	//snow->setGravity(Vec2(-20, -100));
	//snow->setEmissionRate(200);
	//snow->setTotalParticles(1000);
	//snow->setPosVar(Vec2(1500, 0));
	/*snow->setLife(5);
	snow->setLifeVar(3);*/


	 //1 ���� *******************************************
	//auto candle = Sprite::create("CandleHolder.png");
	//candle->setAnchorPoint(Vec2(0.5, 0));
	//candle->setPosition(visibleSize.width/2,0);
	//addChild(candle);
	//// ������Ч 
	//ParticleFire * fire = ParticleFire::create();
	//fire->setPosVar(Vec2(10,0));// �������ӷ����λ�÷�Χ,(0,0)��ʾ��һ����,�����(20,0)
	//// ���ʾ x���� (-20,20)����,y ��Ϊ0��λ�� (�������λ��)

	//fire->setSpeed(40);

	//fire->setLife(3);
	//fire->setEmissionRate(50);
	//fire->setLifeVar(3);
	//fire->setAngleVar(10);
	//fire->setPosition(visibleSize / 2+Size(-40,140));
	//addChild(fire);


	//// 2 �ɻ�β��************************

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
	//// sqBody->setVelocity(Vec2(0, 100));// �������ٶ�,����������������
	// sq->setTotalParticles(1000);//�ܹ�������1000,��ѭ��ʹ�õ�
	// sq->setEmissionRate(100);//���ӷ�����,����ÿ��ų�100��
	// sq->setPosVar(Vec2(0, 0));
	// sq->setAngleVar(0);
	//// sq->setAngle(-60);
	// addChild(sq);
	//
	// // ������������
	// PhysicsJoint *joint = PhysicsJointDistance::construct(rocketBody, sqBody, Vec2(0.5, 0), Vec2(0.5, 1));
	// world->addJoint(joint);

    return true;
}
