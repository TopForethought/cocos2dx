#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "EnemyFactory.h"
#include "PlayerAnmateFactory.h"
#include "GameToolFactory.h"
#include "Player2.h"
#include <vector>
#include "ConstUtil.h"
#include "ui.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;



Sprite* coin[3];
//PhysicsBody* coinBody[5];
Sprite* heart;
Sprite* darts[5];
Size visibleSize;
Vec2 origin;
//int life = 3;//���Է���player
int score;
//���˹���
EnemyFactory *  enemyFactory;
//��Ϸ���߹���
GameToolFactory * gameToolFactory;
//��Ҷ�������
PlayerAnmateFactory * playerAniFactory;
RepeatForever  * runAnimateRepeat;


//��ҽ�ɫ
Player2  *player;

//���ڵ�,�����ȡ���ӽڵ�
Node * rootNode;
int frameNo = 1;// ��¼��Ϸ֡
//�����ƶ��ٶ�  ����ʱ�����Ӷ�����
Point * enemySpeed;//�����ƶ��ٶ�
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
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
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    if ( !Layer::init() )
    {
        return false;
    }

	//���˹���
	enemyFactory = new EnemyFactory();
	//��Ҷ�������
	 playerAniFactory =new PlayerAnmateFactory();
	//��Ϸ���߹���
	 gameToolFactory = new GameToolFactory();
	 enemySpeed = new Point(-300, 0);

    rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
	//
	hp.setPostion(210, visibleSize.height -100);
	addChild(hp.getNode());
	hp.setHp(PLAYER_MAX_LIFE);
	score.setPostion(100, visibleSize.height - 100);
	addChild(score.getNode());
	//��ʼ��Ѫ������
	/*Sprite* lifeNum[4];
	for (int i = 0; i < 4; i++) {
		lifeNum[i] = Sprite::create("number.png", Rect(24 * i, 64, 24, 32));
		lifeNum[i]->setScale(1.5);
		lifeNum[i]->setPosition(160, 560);
		lifeNum[i]->setVisible(false);
		rootNode->addChild(lifeNum[i]);
	}
	lifeNum[3]->setVisible(true);*/
	

	Sprite* background= dynamic_cast<Sprite*>(rootNode->getChildByName("background"));
	
	Sprite* ground = dynamic_cast<Sprite*>(rootNode->getChildByName("ground"));
	ground->runAction(Sequence::create(MoveTo::create(SPEED_BACKGROUND_2/2, Point(0, 120)), CallFunc::create([=] {
		ground->setPosition(2045, 120);
		ground->runAction(RepeatForever::create(Sequence::create(MoveTo::create(SPEED_BACKGROUND_2, Point(0, 120)), CallFunc::create([=] {
			ground->setPosition(2045, 120);
		}), NULL)));
	}), NULL));
	Sprite* ground1 = dynamic_cast<Sprite*>(rootNode->getChildByName("ground1"));
	ground1->runAction(RepeatForever::create(Sequence::create(MoveTo::create(SPEED_BACKGROUND_2, Point(0, 120)), CallFunc::create([=] {
		ground1->setPosition(2045, 120);
	}), NULL)));

	Sprite* human = dynamic_cast<Sprite*>(rootNode->getChildByName("human"));

	//��ʼ�����
	player = new Player2(human,PLAYER_MAX_LIFE);
	PhysicsBody* humanBody = PhysicsBody::createBox(human->getContentSize()/5*4);
	humanBody->setDynamic(false);
	humanBody->setContactTestBitmask(CONTACT_MASK_HUMAN);
	humanBody->setTag(PLAYER_TAG);
	human->setPhysicsBody(humanBody);
	human->setScale(0.4f);


	runAnimateRepeat = RepeatForever::create(playerAniFactory->runAnimate(RUN_ANIMATE_TAG));
	runAnimateRepeat->setTag(RUN_ANIMATE_TAG);
	human->runAction(runAnimateRepeat);

	
	/*
	for (int i = 0; i < 5; i++) {
		darts[i] = Sprite::create("darts.png");
		darts[i]->setScale(0.5f);
		darts[i]->setVisible(false);
		PhysicsBody* dartsBody = PhysicsBody::createBox(darts[i]->getContentSize()/5*4);
		dartsBody->setContactTestBitmask(0x0100);
		dartsBody->setCategoryBitmask(0x0100);
		dartsBody->setCollisionBitmask(1);
		dartsBody->setTag(30 + i);
		darts[i]->setPhysicsBody(dartsBody);
		darts[i]->setTag(30 + i);
		rootNode->addChild(darts[i]);
	}*/

	Button* jump = dynamic_cast<Button*>(rootNode->getChildByName("jump"));
	
	//�����Ծ��������Ծ��������ز����ܶ�����
	jump->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN) {
		//	Animation* jumpAnimation = Animation::createWithSpriteFrames(jumpFrames, 0.05);
			jump->setEnabled(false);
			
		    human->stopActionByTag(RUN_ANIMATE_TAG);     //ͣ����
	
			MoveBy* mb = MoveBy::create(0.5, Point(0, visibleSize.height / 4));
			auto jumpAct = Sequence::create(EaseOut::create(mb->clone(), 2.5f), EaseIn::create(mb->reverse(), 2.5f), NULL);
			human->runAction(jumpAct);
			
			human->runAction(Sequence::create(playerAniFactory->jumpAnimate(JUMP_ANIMATE_TAG),
				CallFunc::create([=] {
				//Animation* runAnimation = Animation::createWithSpriteFrames(runFrames, 0.025);
				//human->stopAllActions();
				runAnimateRepeat = RepeatForever::create(playerAniFactory->runAnimate(RUN_ANIMATE_TAG));
				runAnimateRepeat->setTag(RUN_ANIMATE_TAG);
				human->runAction(runAnimateRepeat);//��ػָ�����
				jump->setEnabled(true);
			}),
				NULL)
			);
		}
	});
	



	/*human->runAction(playerAniFactory->protectAnimate(PROTECT_ANIMATE_TAG));*/

	
	//��ײ���
	EventListenerPhysicsContact* hitListener = EventListenerPhysicsContact::create();
	hitListener->onContactBegin = [=](const PhysicsContact& contact) {
		// ����tagA ��player Ҳ������tagB ��player
		auto shapeA = contact.getShapeA();
		auto shapeB= contact.getShapeB();
		auto tagA = shapeA->getBody()->getTag();
		auto tagB = shapeB->getBody()->getTag();
		if (tagB != PLAYER_TAG) {
			int temp = tagA;
			tagA = tagB;
			tagB = temp;
			auto temp2 = shapeA;
			shapeA = shapeB;
			shapeB = shapeA;
	 }
		log("tagA:%d,tagB:%d", tagA, tagB);
		if (tagB == PLAYER_TAG) {//tagB ��player
			log("in tagB:%d score: %d",  tagB,player->getScore());
		
			//TAGA �����ǵ���Ҳ�����ǽ��
			Node * ownerA;//
			switch (tagA)
			{
			case TOOL_COIN_TAG:
				//ʰȡ���
				ownerA = shapeA->getBody()->getOwner();
				if (ownerA->isVisible()) {
					//owner->stopAllActions();
					ownerA->setVisible(false);
					player->setScore(player->getScore() + SCORE_UNIT);
					score.setScore(player->getScore());
				}
				
				break;
			case TOOL_BLOOD_TAG:
				// ʰȡѪ��
				ownerA = shapeA->getBody()->getOwner();
				if (ownerA->isVisible()) {
					ownerA->setVisible(false);
					if (player->getLife() < PLAYER_MAX_LIFE) {
						player->setLife(player->getLife() + 1);
						/*lifeNum[player->getLife()]->setVisible(true);
						lifeNum[player->getLife() - 1]->setVisible(false);*/
					}
				}
				
				break;

			case ENEMY_TYPE_1_TAG:
				//��ײ�ش�
				//������ڻ��ܣ��õش����ƶ�
			//	i = tagA - 30;
				ownerA = shapeA->getBody()->getOwner();//��ȡ���������
				log("owner tag:%d", ownerA->getTag());
				if (ownerA->isVisible()) {
					/*	ownerA->stopAllActions();*/
						//�л���,��������
					if (player->ifProtected()) {
						//���ӵ÷�
						player->setScore(player->getScore() + SCORE_PER_ENEMY_ON_PROTECTE);
						ownerA->runAction(Sequence::create(
							MoveBy::create(0.25, Point(0, -150)), MoveBy::create(0.5, Point(-300, 0)),
							CallFunc::create([=]() {
							ownerA->setVisible(false);//�ǽ��������ػ��ǽ�sprite����??


						}), NULL));//
					}
					//û�л���,����
					else {
						ownerA->setVisible(false);
						//����Ѫ��
						if (player->getLife() > 0) {
							//life--;
							player->setLife(player->getLife() - 1);
							log("hurt life:%d", player->getLife());
							//lifeNum[player->getLife()]->setVisible(true);
							//lifeNum[player->getLife() + 1]->setVisible(false);//
						}

					}


				}


				break;
			case ENEMY_TYPE_2_TAG:
				//��ײ����
				//������ڻ��ܣ���
			//	i = tagA - 30;
				ownerA = shapeA->getBody()->getOwner();//��ȡ���������
				log("owner tag:%d", ownerA->getTag());
				if (ownerA->isVisible()) {
					/*	ownerA->stopAllActions();*/
						//�л���,��������
					if (player->ifProtected()) {
						player->setScore(player->getScore() + SCORE_PER_ENEMY_ON_PROTECTE);
						ownerA->runAction(Sequence::create(
							MoveBy::create(0.5, Point(0, 200)), MoveBy::create(0.5, Point(-300, 0)),
							CallFunc::create([=]() {
							ownerA->setVisible(false);//�ǽ��������ػ��ǽ�sprite����??


						}), NULL));//��������
					}
					//û�л���,����
					else {
						ownerA->setVisible(false);
						//����Ѫ��
						if (player->getLife() > 0) {
							//life--;
							player->setLife(player->getLife() - 1);
							log("hurt life:%d", player->getLife());
							//lifeNum[player->getLife()]->setVisible(true);
							//lifeNum[player->getLife() + 1]->setVisible(false);//
						}

					}


				}


				break;
			case ENEMY_TYPE_3_TAG:
				//��ײ����
				//������ڻ��ܣ��÷�������һ�ξ���
			//	i = tagA - 30;
				ownerA = shapeA->getBody()->getOwner();//��ȡ���������
				log("owner tag:%d", ownerA->getTag());
				if (ownerA->isVisible()) {
				/*	ownerA->stopAllActions();*/
					//�л���,��������
					if (player->ifProtected()) {
						player->setScore(player->getScore() + SCORE_PER_ENEMY_ON_PROTECTE);
						ownerA->runAction(Sequence::create(
							MoveBy::create(0.5, Point(0, 300)), MoveBy::create(0.5, Point(-300, 0)),
							CallFunc::create([=]() {
							ownerA->setVisible(false);//�ǽ��������ػ��ǽ�sprite����??
							
						
						}),NULL));//��������
					}
					//û�л���,����
					else {
						ownerA->setVisible(false);
						//����Ѫ��
						if (player->getLife() > 0) {
							//life--;
							player->setLife(player->getLife() - 1);
							log("hurt life:%d", player->getLife());
							//lifeNum[player->getLife()]->setVisible(true);
							//lifeNum[player->getLife() + 1]->setVisible(false);//
						}

					}
					
				
				}
				
				
				break;

			
		/*	default:
				break;*/
			}
				
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hitListener, this);

	schedule(schedule_selector(HelloWorld::callback), FRAME_INTERVAL);
	

	
 






    return true;
}
void HelloWorld::callback(float dt) {
	
	//���µ÷�������ֵ
	score.setScore(player->getScore());
	hp.setHp(player->getLife());
	frameNo++;
	if (frameNo > MAX_FRAME_COUNT) {
		frameNo = 1;
		//�ӿ��ٶ�
		enemySpeed->setPoint(enemySpeed->x - 100, enemySpeed->y);
	}
//��ȡ����
	if (!player->ifProtected() && frameNo%FRAME_INTERVAL_PROTECTED == 0) {
		
		frameNo = 0;
		player->setIsProtected(true);

		player->getSprite()->runAction(Sequence::create(
			Repeat::create(playerAniFactory->protectAnimate(PROTECT_ANIMATE_TAG),5), 
			CallFunc::create([=]() {
			//���ܽ���
			log("protected finished");// 
			player->setIsProtected(false);
			
		}),NULL));
	}
	//�������
		// test produce enemy
	//����ش�
	if (frameNo%FRAME_INTERVAL_ENEMY_TYPE_1 == 0) {
		enemyFactory->produceEnemy(ENEMY_TYPE_1, ENEMY_TYPE_1_TAG,Point(1000, 200), *enemySpeed, 1,rootNode);//��������ӵ���1
		return;
	}
	//�������
	if (frameNo%FRAME_INTERVAL_ENEMY_TYPE_2 == 0) {
		enemyFactory->produceEnemy(ENEMY_TYPE_2, ENEMY_TYPE_2_TAG,Point(1000, 200), *enemySpeed,1, rootNode);//��������ӵ���2
		return;
	}
	//��������
	Point *pos;
	if (frameNo%FRAME_INTERVAL_ENEMY_TYPE_3== 0) {
		pos = new Point(visibleSize.width + 50, rand() % (int)visibleSize.height / 4 + visibleSize.height / 3);
		enemyFactory->produceEnemy(ENEMY_TYPE_3, ENEMY_TYPE_3_TAG, *pos, *enemySpeed+Point(-100,0), rand() % 2, rootNode);
	}
	//�������
	if (frameNo%FRAME_INTERVAL_TOOL_BLOOD == 0) {
		pos = new Point(visibleSize.width + 50, rand() % (int)visibleSize.height / 4 + visibleSize.height / 3);
		gameToolFactory->produceTool(TOOL_TYPE_BLOOD, TOOL_BLOOD_TAG, *pos, Point(-60, 0), 1, rootNode);
	}
	if (frameNo%FRAME_INTERVAL_TOOL_COIN == 0) {
		pos = new Point(visibleSize.width + 50, rand() % (int)visibleSize.height / 4 + visibleSize.height / 3);
		gameToolFactory->produceTool(TOOL_TYPE_COIN, TOOL_COIN_TAG, *pos, Point(-60, 0), rand() % 3, rootNode);
	}
	
	

	
}
