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
���˹����࣬�������������
*/
class EnemyFactory
{
private :
	//map<int, Vector<Character*> *> enemyMap;// ����-��������,��ʱ����,û�н�����͵�����
	//Vector <int>  enemyType;//�����б�
	Vector <Sprite *>* enemysType1;
	Vector <Sprite *>* enemysType2;
	Vector <Sprite *>* enemysType3;
public:
	EnemyFactory();
	~EnemyFactory();
	//���ݵ�������,��ָ��λ�ò�������,����ִ���ƶ���Ϊ
	void produceEnemy(int type,int tag, Point postion, Point speed,int enemyCount,Node * root);
	//���ݵ�������,������Ӧ�Ķ���,������Ҫ���ݶ���ִ��ʱ��,ִ�д���
	Animate * produceAnimate(int type,float duration,int times);
};

