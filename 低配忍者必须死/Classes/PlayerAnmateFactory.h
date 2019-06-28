#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
//玩家动作类
class PlayerAnmateFactory
{
private:
//动画帧
	Vector<SpriteFrame*> runFrames;
	
	Vector<SpriteFrame*> jumpFrames;
	Vector<SpriteFrame *> protectdFrames;
	

public:
	PlayerAnmateFactory();
	~PlayerAnmateFactory();

	//护盾动画
	Animate * protectAnimate(int tag);
	//跳跃动画
	Animate * jumpAnimate(int tag);
	//奔跑动画
	Animate * runAnimate(int tag);
	
};

