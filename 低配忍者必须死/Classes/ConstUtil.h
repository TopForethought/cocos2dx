#pragma once
#include <string>
using std::string;
/**
 ȫ�ֳ���
*/

const int HELLO_WORLD = 1;//���Գ�������

//��ײ�������
const int  CONTACT_MASK_HUMAN= 0x1111;
const int  CONTACT_MASK_COIN= 0x0001;
const int  CAT_MASK_COIN =0x0001;
const int CAT_MASK_BLOOD = 0x0010 ;
const int CONTACT_MASK_BLOOD = 0x0010;
const int COLLISION_MASK_BLOOD = 0;
const int CONTACT_MASK_ENEMY_TYPE_1 = 0x0010;//���˽Ӵ������,ֵ�ж���human �ĽӴ�
const int CONTACT_MASK_ENEMY_TYPE_2 = 0x0100;
const int CONTACT_MASK_ENEMY_TYPE_3 = 0x1000;
//�������
 // ���˷���
//�������Ͷ���
const int  ENEMY_TYPE_1 = 1;//�ش�
const int  ENEMY_TYPE_2 = 2;//����
const int  ENEMY_TYPE_3 = 3;//����
//���߷���
const int TOOL_TYPE_COIN = 1;//���
const int TOOL_TYPE_BLOOD = 2;//Ѫ��

//��ֵ���
const int  PLAYER_MAX_LIFE = 3;//�������ֵ
const int SCORE_UNIT = 1;//��ֵ��λ
const int SCORE_PER_ENEMY_ON_PROTECTE = 50;//��ֵ��λ,���ܴ���,�ĵ÷�����
const int  FRAME_INTERVAL_PROTECTED =19;//ÿ19 ֡�õ�һ�λ���
const int  FRAME_INTERVAL_ENEMY_TYPE_1 = 11;
const int  FRAME_INTERVAL_ENEMY_TYPE_2 =7;
const int  FRAME_INTERVAL_ENEMY_TYPE_3 = 3;
//���߲���ʱ����
const int  FRAME_INTERVAL_TOOL_BLOOD = 17;
const int  FRAME_INTERVAL_TOOL_COIN = 2;


const int SPEED_BACKGROUND_2 = 6;//�����ƶ��ٶ�,Խ���ƶ�Խ��(�����ƶ������ʱ��)

//��ǩ���
const int RUN_ANIMATE_TAG = 10000;//���ܶ�����ǩ
const int JUMP_ANIMATE_TAG = 10001;//��Ծ������ǩ
const int PROTECT_ANIMATE_TAG = 10002;//���ܶ�����ǩ
const int PLAYER_TAG = 0;//��ұ�ǩ
const int ENEMY_TYPE_1_TAG = 11000; // �ش�//���˱�ǩ
const int ENEMY_TYPE_2_TAG = 11001;//����
const int ENEMY_TYPE_3_TAG = 11002;//����

const int TOOL_BLOOD_TAG = 12000;//Ѫ����ǩ
const int TOOL_COIN_TAG = 12001;//��ұ�ǩ

const int FRAME_INTERVAL = 1;//ÿ֡���ʱ�䳤��(��)
const int MAX_FRAME_COUNT = 60;//����(һ�����ڵ�֡��
class ConstUtil
{
public:
	ConstUtil();
	~ConstUtil();
	// ��������
	 //static char * ENEMY_TYPE_DARTS= ENEMY_TYPE_1;// ����
	 //static string  * ENEMY_TYPE_SKIPWEED =new string("skipweed");//�ش�


	
};

