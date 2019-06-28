#pragma once
#include <map>
#include <string>
#include "cocostudio/CocoStudio.h"
#include <vector>

#include "ConstUtil.h"

using std::map;
using  std::string;
USING_NS_CC;
/**
敌人工厂类，适用于制造敌人
*/
class EnemyFactory
{
private :
	//map<int, Vector<Character*> *> enemyMap;// 类型-敌人数组,暂时无用,没有解决泛型的问题
	//Vector <int>  enemyType;//类型列表
	Vector <Sprite *>* enemysType1;
	Vector <Sprite *>* enemysType2;
	Vector <Sprite *>* enemysType3;
public:
	EnemyFactory();
	~EnemyFactory();
	//根据敌人类型,在指定位置产生敌人,并且执行移动行为
	void produceEnemy(int type,int tag, Point postion, Point speed,int enemyCount,Node * root);
	//根据敌人类型,产生对应的动画,参数需要传递动画执行时间,执行次数
	Animate * produceAnimate(int type,float duration,int times);
};

