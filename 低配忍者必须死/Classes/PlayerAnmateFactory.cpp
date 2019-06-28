#include "PlayerAnmateFactory.h"



PlayerAnmateFactory::PlayerAnmateFactory()
{
	//��ʼ������֡

	//����
	char file[20];
	for (int i = 1; i <= 7; i++) {
		
		sprintf_s(file, "run/run%d.png", i);
		runFrames.pushBack((Sprite::create(file))->getSpriteFrame());
	}

	//��Ծ
	for (int i = 1; i <= 20; i++) {
		
		sprintf_s(file, "jump/jump%d.png", i);
		jumpFrames.pushBack((Sprite::create(file))->getSpriteFrame());
	}
	//����
	char * fileFmt = "protect%d.png";
	
	for (int i = 0; i < 6; i++) {
		sprintf_s(file, fileFmt, (i + 1));

		protectdFrames.pushBack(Sprite::create(file)->getSpriteFrame());
	}

}


PlayerAnmateFactory::~PlayerAnmateFactory()
{
}

//���ܶ���
Animate * PlayerAnmateFactory::protectAnimate(int tag)
{
	
	
	auto animate = Animate::create(Animation::createWithSpriteFrames(protectdFrames, 0.05f, 20));
	animate->setTag(tag);
	return animate;
	
	
	
	
}

Animate * PlayerAnmateFactory::jumpAnimate(int tag)
{
	
	
	auto ani = Animate::create(Animation::createWithSpriteFrames(jumpFrames, 0.05));
	ani->setTag(tag);
	return ani;
	
}

Animate * PlayerAnmateFactory::runAnimate(int tag)
{
	auto animate= Animate::create(Animation::createWithSpriteFrames(runFrames, 0.04));
	animate->setTag(tag);
	return animate;
}
