#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
#define PHYSICS_MATERIAL1  PhysicsMaterial(1,1,0)
#define PHYSICS_MATERIAL2  PhysicsMaterial(1,0,0)
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	// �������������Ե�����
	auto  scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setAutoStep(false);
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


	


	//1, ���� С�����䲻�Ϸ���********************

        auto rootNode = CSLoader::createNode("MainScene.csb");
		Sprite * edgeBox = dynamic_cast<Sprite*>(rootNode->getChildByName("Default"));

		auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICS_MATERIAL1,3);
		edgeBody->setDynamic(false);
		edgeBox->setPhysicsBody(edgeBody);
		addChild(rootNode);

		//auto redBall = rootNode->getChildByName("redBall");
		//auto ballBody = PhysicsBody::createCircle(20, PHYSICS_MATERIAL2);
		//ballBody->setDynamic(true);// ���ò��̶�
		//redBall->setPhysicsBody(ballBody);



		////// 1 �����ײ
		//Sprite * blueBox = (Sprite * )rootNode->getChildByName("greenBox");
		//auto blueBody = PhysicsBody::createBox(blueBox->getContentSize(), PHYSICS_MATERIAL2);
		//blueBody->setDynamic(true);
		//blueBox->setPhysicsBody(blueBody);
		//Sprite * redBox = (Sprite *)rootNode->getChildByName("redBox");
		//auto redBody = PhysicsBody::createBox(redBox->getContentSize(), PHYSICS_MATERIAL2);
	 //      redBody->setDynamic(false);
		//redBox->setPhysicsBody(redBody);
		////��������  A�������ײ������B������������λ��,��������0,˵���ᷢ����ײ

		//ballBody->setCategoryBitmask(1);
		//ballBody->setCollisionBitmask(1);
		//
		//redBody->setCategoryBitmask(2);
		//redBody->setCollisionBitmask(2);
		//blueBody->setCategoryBitmask(3);
		//blueBody->setCollisionBitmask(3);

		////2  ��ײ�¼���Ӧ,��ɫ��װ�Ϻ�ɫ����ʱ,��ɫ������ʧ
		//redBall->setTag(66);
		//ballBody->setContactTestBitmask(2);//�Ӵ��������,�����B�ķ������� λ�ڲ�Ϊ0,��ʾ�����Ӵ��¼�
		//redBox->setTag(67);
		//redBody->setContactTestBitmask(0x3);
	
		//EventListenerPhysicsContact * hitListener = EventListenerPhysicsContact::create();
		//// onContactBegin �տ�ʼ�Ӵ�,�������true,��ײ�ᱻ��������
		//// pre-solve:�յ�����¼�ʱ,���� ��״�Ӵ���һ��
		//// post-solve"�յ�����¼�ʱ������״�Ѿ��Ӵ�,������ײ�Ѿ�������
		//// separate:�յ�����¼�ʱ,������״�иո�ֹͣ�˽Ӵ�

		//hitListener->onContactSeparate =[=](const PhysicsContact & contact) {
		//	auto nodeA = contact.getShapeA()->getBody()->getNode();
		//	auto nodeB = contact.getShapeB()->getBody()->getNode();
		//	
		//	log("nodeATag:%d", nodeA->getTag());
		//	log("nodeBTag:%d", nodeB->getTag());
		//	if (nodeA&& nodeB) {
		//		// ���������ɫ������
		//		if (nodeA->getTag() == 67) {
		//			nodeA->removeFromParent();
		//		}
		//		else if (nodeB->getTag()==67) {
		//			nodeB->removeFromParent();
		//		}
		//			
		//	
		//		
		//	}
		//	return true;
		//};
		//Director::getInstance()->getEventDispatcher()
		//	->addEventListenerWithSceneGraphPriority(hitListener, this);


		// ��ϰ:�ɻ�(С�ɻ����ɻ�����ײ)
		// 
		auto  bigPlane = rootNode->getChildByName("bigEnemy");
		auto smallPlane = rootNode->getChildByName("smallEnemy");
		auto hero = rootNode->getChildByName("hero");

		auto bigBody = PhysicsBody::createBox(bigPlane->getContentSize(), PHYSICS_MATERIAL2);
		bigBody->setDynamic(false);
		bigPlane->setPhysicsBody(bigBody);
		auto smallBody = PhysicsBody::createBox(smallPlane->getContentSize(), PHYSICS_MATERIAL2);
		smallPlane->setPhysicsBody(smallBody);
		auto heroBody = PhysicsBody::createBox(hero->getContentSize(), PHYSICS_MATERIAL2);

		hero->setPhysicsBody(heroBody);
		hero->setTag(41);
		smallPlane->setTag(40);

		// ����С�л�������л�
		smallBody->setCollisionBitmask(2);
		bigBody->setCategoryBitmask(1);
		
		// С�ɻ���ս����ײ,��ײ���

		smallBody->setContactTestBitmask(1);
		heroBody->setContactTestBitmask(3);
		//smallBody->setCollisionBitmask(4);// С�ɻ����Դ���
		// ��ը��Ч���
		//auto  bomb = Sprite::create("BigExolodeA.png", Rect(0, 0,109 ,100));
	    

		// �¼�����
		EventListenerPhysicsContact * hitListener = EventListenerPhysicsContact::create();
		hitListener->onContactBegin = [=](PhysicsContact & contact) {
			auto nodeA = contact.getShapeA()->getBody()->getNode();
			auto nodeB = contact.getShapeB()->getBody()->getNode();
			if (nodeA && nodeB) {
				auto node = nodeA;
				
				 if (nodeB->getTag() == 40) {
					 node = nodeB;
				}
				 node->getPhysicsBody()->setVelocity(Vec2(0, 0));
				// ���챬ը��Ч
				 Vector<SpriteFrame *>frames(10);
				 for (int i = 0; i < 10; i++) {
					 frames.pushBack(Sprite::create("BigExplodeA.png", Rect(i * 109, 0, 109, 100))
						 ->getSpriteFrame());
				 }
				 Animate * animate = Animate::create(Animation::createWithSpriteFrames(frames, 0.05f));

				  
				 node->runAction(Sequence::create(Repeat::create(animate,2),
					 CallFunc::create([=]{
					 //node->setVisible(false);
					 node->removeFromParent();
				 }),
				 
				 NULL));
				 
				
			}

			return true;
		};
		Director::getInstance()->getEventDispatcher()
				->addEventListenerWithSceneGraphPriority(hitListener, this);
		// �л�����
		Vector<SpriteFrame *> frames(2);
		frames.pushBack(Sprite::create("SmallEnemy1.png")->getSpriteFrame());
		frames.pushBack(Sprite::create("SmallEnemy2.png")->getSpriteFrame());
		
		smallPlane->runAction(RepeatForever::create(
			Animate::create(Animation::createWithSpriteFrames(frames, 0.05f))));
		// �л�����
		//smallPlane->runAction(MoveBy::create(3, Vec2(0, -900)));
		smallBody->setVelocity(Vec2(0, -50));

		return true;
}
void HelloWorld::myCallback(float dt) {
	
	//this.pinwheelBody->setPhysicsBody(-10);
//	pinwheelBody->setAngularDamping(2);
	//m_lTimer++;
	//if (m_lTimer > m_maxTime) {
	//	m_maxTime = 1;
	//}
	////���ٶ�
	//if (m_lTimer % 17 == 0) {
	//	pinwheelBody->setAngularVelocity(-6);
	//	pinwheelBody->setAngularDamping(0);
	//	log("hello  speed");
	//}
	//////������
	//if (m_lTimer % 13 == 0) {
	//	pinwheelBody->setAngularDamping(0.5);
	//	log("damping");
	//}

	log("hello %f",time);
}