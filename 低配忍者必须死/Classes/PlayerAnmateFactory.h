#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
//��Ҷ�����
class PlayerAnmateFactory
{
private:
//����֡
	Vector<SpriteFrame*> runFrames;
	
	Vector<SpriteFrame*> jumpFrames;
	Vector<SpriteFrame *> protectdFrames;
	

public:
	PlayerAnmateFactory();
	~PlayerAnmateFactory();

	//���ܶ���
	Animate * protectAnimate(int tag);
	//��Ծ����
	Animate * jumpAnimate(int tag);
	//���ܶ���
	Animate * runAnimate(int tag);
	
};

