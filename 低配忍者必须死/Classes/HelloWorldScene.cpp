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
//int life = 3;//属性放在player
int score;
//敌人工厂
EnemyFactory *  enemyFactory;
//游戏道具工厂
GameToolFactory * gameToolFactory;
//玩家动画工厂
PlayerAnmateFactory * playerAniFactory;
RepeatForever  * runAnimateRepeat;


//玩家角色
Player2  *player;

//根节点,方便获取孩子节点
Node * rootNode;
int frameNo = 1;// 记录游戏帧
//敌人移动速度  随着时间增加而增大
Point * enemySpeed;//敌人移动速度
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

	//敌人工厂
	enemyFactory = new EnemyFactory();
	//玩家动画工厂
	 playerAniFactory =new PlayerAnmateFactory();
	//游戏道具工厂
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
	//初始化血量数字
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

	//初始化玩家
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
	
	//点击跳跃，播放跳跃动画。落地播放跑动动画
	jump->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN) {
		//	Animation* jumpAnimation = Animation::createWithSpriteFrames(jumpFrames, 0.05);
			jump->setEnabled(false);
			
		    human->stopActionByTag(RUN_ANIMATE_TAG);     //停掉奔
	
			MoveBy* mb = MoveBy::create(0.5, Point(0, visibleSize.height / 4));
			auto jumpAct = Sequence::create(EaseOut::create(mb->clone(), 2.5f), EaseIn::create(mb->reverse(), 2.5f), NULL);
			human->runAction(jumpAct);
			
			human->runAction(Sequence::create(playerAniFactory->jumpAnimate(JUMP_ANIMATE_TAG),
				CallFunc::create([=] {
				//Animation* runAnimation = Animation::createWithSpriteFrames(runFrames, 0.025);
				//human->stopAllActions();
				runAnimateRepeat = RepeatForever::create(playerAniFactory->runAnimate(RUN_ANIMATE_TAG));
				runAnimateRepeat->setTag(RUN_ANIMATE_TAG);
				human->runAction(runAnimateRepeat);//落地恢复奔跑
				jump->setEnabled(true);
			}),
				NULL)
			);
		}
	});
	



	/*human->runAction(playerAniFactory->protectAnimate(PROTECT_ANIMATE_TAG));*/

	
	//碰撞检测
	EventListenerPhysicsContact* hitListener = EventListenerPhysicsContact::create();
	hitListener->onContactBegin = [=](const PhysicsContact& contact) {
		// 可能tagA 是player 也可能是tagB 是player
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
		if (tagB == PLAYER_TAG) {//tagB 是player
			log("in tagB:%d score: %d",  tagB,player->getScore());
		
			//TAGA 可能是敌人也可能是金币
			Node * ownerA;//
			switch (tagA)
			{
			case TOOL_COIN_TAG:
				//拾取金币
				ownerA = shapeA->getBody()->getOwner();
				if (ownerA->isVisible()) {
					//owner->stopAllActions();
					ownerA->setVisible(false);
					player->setScore(player->getScore() + SCORE_UNIT);
					score.setScore(player->getScore());
				}
				
				break;
			case TOOL_BLOOD_TAG:
				// 拾取血块
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
				//碰撞地刺
				//如果存在护盾，让地刺下移动
			//	i = tagA - 30;
				ownerA = shapeA->getBody()->getOwner();//获取刚体的主人
				log("owner tag:%d", ownerA->getTag());
				if (ownerA->isVisible()) {
					/*	ownerA->stopAllActions();*/
						//有护盾,弹开敌人
					if (player->ifProtected()) {
						//增加得分
						player->setScore(player->getScore() + SCORE_PER_ENEMY_ON_PROTECTE);
						ownerA->runAction(Sequence::create(
							MoveBy::create(0.25, Point(0, -150)), MoveBy::create(0.5, Point(-300, 0)),
							CallFunc::create([=]() {
							ownerA->setVisible(false);//是将刚体隐藏还是将sprite隐藏??


						}), NULL));//
					}
					//没有护盾,受伤
					else {
						ownerA->setVisible(false);
						//处理血量
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
				//碰撞齿轮
				//如果存在护盾，让
			//	i = tagA - 30;
				ownerA = shapeA->getBody()->getOwner();//获取刚体的主人
				log("owner tag:%d", ownerA->getTag());
				if (ownerA->isVisible()) {
					/*	ownerA->stopAllActions();*/
						//有护盾,弹开敌人
					if (player->ifProtected()) {
						player->setScore(player->getScore() + SCORE_PER_ENEMY_ON_PROTECTE);
						ownerA->runAction(Sequence::create(
							MoveBy::create(0.5, Point(0, 200)), MoveBy::create(0.5, Point(-300, 0)),
							CallFunc::create([=]() {
							ownerA->setVisible(false);//是将刚体隐藏还是将sprite隐藏??


						}), NULL));//飞镖上移
					}
					//没有护盾,受伤
					else {
						ownerA->setVisible(false);
						//处理血量
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
				//碰撞飞镖
				//如果存在护盾，让飞镖上移一段距离
			//	i = tagA - 30;
				ownerA = shapeA->getBody()->getOwner();//获取刚体的主人
				log("owner tag:%d", ownerA->getTag());
				if (ownerA->isVisible()) {
				/*	ownerA->stopAllActions();*/
					//有护盾,弹开敌人
					if (player->ifProtected()) {
						player->setScore(player->getScore() + SCORE_PER_ENEMY_ON_PROTECTE);
						ownerA->runAction(Sequence::create(
							MoveBy::create(0.5, Point(0, 300)), MoveBy::create(0.5, Point(-300, 0)),
							CallFunc::create([=]() {
							ownerA->setVisible(false);//是将刚体隐藏还是将sprite隐藏??
							
						
						}),NULL));//飞镖上移
					}
					//没有护盾,受伤
					else {
						ownerA->setVisible(false);
						//处理血量
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
	
	//更新得分与生命值
	score.setScore(player->getScore());
	hp.setHp(player->getLife());
	frameNo++;
	if (frameNo > MAX_FRAME_COUNT) {
		frameNo = 1;
		//加快速度
		enemySpeed->setPoint(enemySpeed->x - 100, enemySpeed->y);
	}
//获取护盾
	if (!player->ifProtected() && frameNo%FRAME_INTERVAL_PROTECTED == 0) {
		
		frameNo = 0;
		player->setIsProtected(true);

		player->getSprite()->runAction(Sequence::create(
			Repeat::create(playerAniFactory->protectAnimate(PROTECT_ANIMATE_TAG),5), 
			CallFunc::create([=]() {
			//护盾结束
			log("protected finished");// 
			player->setIsProtected(false);
			
		}),NULL));
	}
	//制造敌人
		// test produce enemy
	//制造地刺
	if (frameNo%FRAME_INTERVAL_ENEMY_TYPE_1 == 0) {
		enemyFactory->produceEnemy(ENEMY_TYPE_1, ENEMY_TYPE_1_TAG,Point(1000, 200), *enemySpeed, 1,rootNode);//场景中添加敌人1
		return;
	}
	//制造齿轮
	if (frameNo%FRAME_INTERVAL_ENEMY_TYPE_2 == 0) {
		enemyFactory->produceEnemy(ENEMY_TYPE_2, ENEMY_TYPE_2_TAG,Point(1000, 200), *enemySpeed,1, rootNode);//场景中添加敌人2
		return;
	}
	//产生飞镖
	Point *pos;
	if (frameNo%FRAME_INTERVAL_ENEMY_TYPE_3== 0) {
		pos = new Point(visibleSize.width + 50, rand() % (int)visibleSize.height / 4 + visibleSize.height / 3);
		enemyFactory->produceEnemy(ENEMY_TYPE_3, ENEMY_TYPE_3_TAG, *pos, *enemySpeed+Point(-100,0), rand() % 2, rootNode);
	}
	//制造道具
	if (frameNo%FRAME_INTERVAL_TOOL_BLOOD == 0) {
		pos = new Point(visibleSize.width + 50, rand() % (int)visibleSize.height / 4 + visibleSize.height / 3);
		gameToolFactory->produceTool(TOOL_TYPE_BLOOD, TOOL_BLOOD_TAG, *pos, Point(-60, 0), 1, rootNode);
	}
	if (frameNo%FRAME_INTERVAL_TOOL_COIN == 0) {
		pos = new Point(visibleSize.width + 50, rand() % (int)visibleSize.height / 4 + visibleSize.height / 3);
		gameToolFactory->produceTool(TOOL_TYPE_COIN, TOOL_COIN_TAG, *pos, Point(-60, 0), rand() % 3, rootNode);
	}
	
	

	
}
