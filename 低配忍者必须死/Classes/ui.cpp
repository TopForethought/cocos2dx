#include "ui.h"

SpriteFrame* getDigit(int index, int num)
{
	SpriteFrame *frame = SpriteFrame::create("digit.png", Rect(num * 24, index * 32, 24, 32));
	return frame;
}

//===== score =====
Score::Score()
{
	Rect rect(0, 32, 24, 32);
	node = Node::create();
	node->setAnchorPoint(Vec2(0, 1));
	node->setPosition(0, 0);
	node->retain();
	for (int i = 0; i < SCORE_BIT; i++)
	{
		sprite[i] = Sprite::create("digit.png", rect);
		sprite[i]->setPosition(24 * i, 16);
		node->addChild(sprite[i]);
	}
	score = 0;
}

Score::~Score()
{
	node->release();
}

int Score::getScore()
{
	return score;
}

void Score::setScore(int score)
{
	char s[SCORE_BIT];
	int i;
	this->score = score;
	for (i = SCORE_BIT - 1; i >= 0 && score > 0; i--)
	{
		s[i] = score % 10;
		score = score / 10;
	}
	for (; i >= 0; i--)
		s[i] = 0;
	for (i = SCORE_BIT - 1; i >= 0; i--)
		sprite[i]->setSpriteFrame(getDigit(1, s[i]));
}

void Score::setPostion(float x, float y)
{
	node->setPosition(x, y);
}

Node* Score::getNode()
{
	return node;
}

float Score::getWidth()
{
	return 24 * SCORE_BIT;
}

//===== hp =====
Hp::Hp()
{
	node = Node::create();
	node->setAnchorPoint(Vec2(0, 1));
	node->setPosition(0, 0);
	node->retain();
	sprite = Sprite::create("digit.png", Rect(0, 0, 24, 32));
	sprite->setPosition(12, 16);
	node->addChild(sprite);
	hp = 0;
}

Hp::~Hp()
{
	node->release();
}

int Hp::getHp()
{
	return hp;
}

void Hp::setHp(int hp)
{
	this->hp = hp;
	sprite->setSpriteFrame(getDigit(0, hp % 10));

}

void Hp::setPostion(float x, float y)
{
	node->setPosition(x, y);
}

Node* Hp::getNode()
{
	return node;
}