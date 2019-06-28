#include "EnemyFactory.h"




//敌人大小定义
const Size ENEMY_TYPE_1_SIZE(210, 75);
const Size ENEMY_TYPE_2_SIZE(100, 100);
const Size ENEMY_TYPE_3_SIZE (256,256);
EnemyFactory::EnemyFactory()
{
	//添加敌人类型
	//enemyType.pushBack(ENEMY_TYPE_1);//地刺
	//enemyType.pushBack(ENEMY_TYPE_2);//齿轮
	//初始化敌人数组
	enemysType1 = new Vector<Sprite*>();
	enemysType2 =new Vector<Sprite*>();
	
	enemysType3 = new Vector<Sprite*>();
}


EnemyFactory::~EnemyFactory()
{
}

//敌人生产逻辑
// 1, 检查已有敌人列表,从已有敌人列表已死亡中复活
// 2, 如果数量不够,创建新的敌人,加入数组
//3,对于每个生产出的敌人都需要播放相关的动画
void EnemyFactory::produceEnemy(int type,int tag, Point postion, Point speed, int enemyCount,Node * root)
{
	//if (!enemyType.contains(type)) {
	//	log("enemy type not exists:" + type);
	//	return;
	//}
	int newCount = enemyCount;
	
	switch (type) {

	case ENEMY_TYPE_1:
		//地刺
		log("enemy 1 size:%d", enemysType1->size());
		for (int i = 0; i < enemysType1->size() && newCount>0;i++) {
			Sprite * enemy = enemysType1->at(i);
			if (!enemy->isVisible()) {
				enemy->setPosition(postion);
				newCount--;
				postion += Point(200, 0);
				enemy->setVisible(true);

			}
		}
		//生产全新的敌人
		while (newCount-- > 0) {
			 auto enemy = Sprite::create("sweed01.png", Rect(0,0, 
				 ENEMY_TYPE_1_SIZE.width, ENEMY_TYPE_1_SIZE.height));
			 enemy->setTag(tag);
			enemy->setPosition(postion);
		
			postion += Point(200, 0);
			//启用动画
			Animate * ani = produceAnimate(type, 0.3f, -1);
			enemy->runAction(RepeatForever::create(ani));
			//启用移动动作
			auto toLeft = MoveBy::create(1, speed);
			enemy->runAction(RepeatForever::create(Sequence::create(toLeft, CallFunc::create([=]() {
				//如果移除边界,设置为不可见
				if (enemy->getPosition().x<0) {
					//enemy->setExists(false);
					log("地刺消失:");
					enemy->setVisible(false);
				}
			}), NULL)));
			//添加刚体
			auto body=PhysicsBody::createBox(Size(100, 50));
			body->setContactTestBitmask(CONTACT_MASK_ENEMY_TYPE_1);
			body->setCollisionBitmask(0);
			body->setTag(tag);
			enemy->setPhysicsBody(body);
		     
			root->addChild(enemy);//将敌人加入场景
			enemysType1->pushBack(enemy);
		}

		break;
	case ENEMY_TYPE_2 :
		//齿轮
		log("enemy 2 size:%d", enemysType2->size());
		for (int i = 0; i <enemysType2->size() && newCount>0; i++) {
			Sprite * enemy = enemysType2->at(i);
			if (!enemy->isVisible()) {
				enemy->setPosition(postion);
				newCount--;
				postion += Point(200, 0);
				enemy->setVisible(true);
				enemy->stopAllActions();
				auto toLeft = MoveBy::create(1, speed);
				auto  rotateBy = RotateBy::create(0.2f, -60);
				enemy->runAction(RepeatForever::create(Sequence::create(toLeft, rotateBy, CallFunc::create([=]() {
					//如果移除边界,设置为不可见
					if (enemy->getPosition().x < 0) {
						//enemy->setExists(false);

						enemy->setVisible(false);
					}
				}), NULL)));
			}
		}
		//生产全新的敌人
		while (newCount-- > 0) {
			auto enemy = Sprite::create("roll2.png", Rect(0, 0,
				ENEMY_TYPE_2_SIZE.width, ENEMY_TYPE_2_SIZE.height));
			enemy->setTag(tag);
			enemy->setPosition(postion);

			postion += Point(200, 0);
	
			
			auto toLeft = MoveBy::create(1, speed);
			auto  rotateBy = RotateBy::create(0.2f, -60);
			enemy->runAction(RepeatForever::create(Sequence::create(toLeft, rotateBy, CallFunc::create([=]() {
				//如果移除边界,设置为不可见
				if (enemy->getPosition().x < 0) {
					//enemy->setExists(false);
				
					enemy->setVisible(false);
				}
			}), NULL)));
			//添加刚体
			auto body = PhysicsBody::createCircle(enemy->getContentSize().height / 2);
			body->setTag(tag);
			body->setContactTestBitmask(CONTACT_MASK_ENEMY_TYPE_2);
			body->setCollisionBitmask(0);
			enemy->setPhysicsBody(body);
			root->addChild(enemy);//将敌人加入场景
			enemysType2->pushBack(enemy);
		}

		
		
		break;
		//飞镖
	case ENEMY_TYPE_3:
		log("enemy 3 size:%d", enemysType3->size());
		for (int i = 0; i < enemysType3->size() && newCount>0; i++) {
			Sprite * enemy = enemysType3->at(i);
			if (!enemy->isVisible()) {
				enemy->setPosition(postion);
				newCount--;
				postion += Point(200, 0);
				enemy->setVisible(true);
				enemy->stopAllActions();
				auto toLeft = MoveBy::create(0.5, speed);
				enemy->runAction(RepeatForever::create(Sequence::create(toLeft, CallFunc::create([=]() {
					//如果移除边界,设置为不可见
					if (enemy->getPosition().x < 0) {
						//enemy->setExists(false);

						enemy->setVisible(false);
					}
				}), NULL)));
			}
		}
		//生产全新的敌人

	
		while (newCount-- > 0) {
			auto enemy = Sprite::create("darts.png");
			enemy->setTag(tag);
			enemy->setPosition(postion);
			enemy->setScale(0.5f);
			postion += Point(200, 0);


			auto toLeft = MoveBy::create(0.5, speed);
			
			enemy->runAction(RepeatForever::create(Sequence::create(toLeft, CallFunc::create([=]() {
				//如果移除边界,设置为不可见
				if (enemy->getPosition().x < 0) {
					//enemy->setExists(false);

					enemy->setVisible(false);
				}
			}), NULL)));
			PhysicsBody* dartsBody = PhysicsBody::createBox(enemy->getContentSize() / 5 * 4);
			dartsBody->setContactTestBitmask(0x0100);
			dartsBody->setCategoryBitmask(0x0100);
			dartsBody->setCollisionBitmask(1);
			dartsBody->setTag(tag);
		  dartsBody->setContactTestBitmask(CONTACT_MASK_ENEMY_TYPE_3);
	 	 dartsBody->setCollisionBitmask(0);
			enemy->setPhysicsBody(dartsBody);
	      	root->addChild(enemy);//将敌人加入场景
			enemysType2->pushBack(enemy);
		}



		break;
	default: 
			break;




	}


}

Animate * EnemyFactory::produceAnimate(int type, float duration, int times)
{
	Animate * animate = nullptr;
	Vector<SpriteFrame *> frames;
	switch ( type)
	{
	case ENEMY_TYPE_1:
		//产生地刺动画 6帧
		char * fileFmt = "sweed%02d.png";
		char fileName[20];
		for (int i = 0; i <6; i++) {
			sprintf_s(fileName, fileFmt, (i + 1));
			frames.pushBack(Sprite::create(fileName,Rect(
				0,0,
				ENEMY_TYPE_1_SIZE.width, ENEMY_TYPE_1_SIZE.height))
				->getSpriteFrame());
		}
		animate = Animate::create(Animation::createWithSpriteFrames(frames, duration, times));

		break;

	}
	log(" factory: animate result==nullptr?   " + (animate == nullptr));

	return animate;
}
