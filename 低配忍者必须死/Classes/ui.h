#ifndef UI_H
#define UI_H

#include "res.h"
#include "cocos2d.h"
USING_NS_CC;

#define SCORE_BIT 5

class Score{
private:
	int score;
	Sprite *sprite[SCORE_BIT];
	Node* node;
public:
	Score();
	~Score();
	int getScore();
	void setScore(int score);
	void setPostion(float x, float y);
	Node* getNode();
	float getWidth();
};

class Hp{
private:
	int hp;
	Sprite* sprite;
	Node* node;
public:
	Hp();
	~Hp();
	int getHp();
	void setHp(int hp);
	void setPostion(float x, float y);
	Node* getNode();
};

#endif
