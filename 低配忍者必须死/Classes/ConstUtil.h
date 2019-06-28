#pragma once
#include <string>
using std::string;
/**
 全局常量
*/

const int HELLO_WORLD = 1;//测试常量定义

//碰撞掩码相关
const int  CONTACT_MASK_HUMAN= 0x1111;
const int  CONTACT_MASK_COIN= 0x0001;
const int  CAT_MASK_COIN =0x0001;
const int CAT_MASK_BLOOD = 0x0010 ;
const int CONTACT_MASK_BLOOD = 0x0010;
const int COLLISION_MASK_BLOOD = 0;
const int CONTACT_MASK_ENEMY_TYPE_1 = 0x0010;//敌人接触检测码,值判断与human 的接触
const int CONTACT_MASK_ENEMY_TYPE_2 = 0x0100;
const int CONTACT_MASK_ENEMY_TYPE_3 = 0x1000;
//分类相关
 // 敌人分类
//敌人类型定义
const int  ENEMY_TYPE_1 = 1;//地刺
const int  ENEMY_TYPE_2 = 2;//齿轮
const int  ENEMY_TYPE_3 = 3;//飞镖
//道具分类
const int TOOL_TYPE_COIN = 1;//金币
const int TOOL_TYPE_BLOOD = 2;//血包

//数值相关
const int  PLAYER_MAX_LIFE = 3;//最大生命值
const int SCORE_UNIT = 1;//分值单位
const int SCORE_PER_ENEMY_ON_PROTECTE = 50;//分值单位,护盾存在,的得分增加
const int  FRAME_INTERVAL_PROTECTED =19;//每19 帧得到一次护盾
const int  FRAME_INTERVAL_ENEMY_TYPE_1 = 11;
const int  FRAME_INTERVAL_ENEMY_TYPE_2 =7;
const int  FRAME_INTERVAL_ENEMY_TYPE_3 = 3;
//道具产生时间间隔
const int  FRAME_INTERVAL_TOOL_BLOOD = 17;
const int  FRAME_INTERVAL_TOOL_COIN = 2;


const int SPEED_BACKGROUND_2 = 6;//地面移动速度,越大移动越慢(这是移动所需的时间)

//标签相关
const int RUN_ANIMATE_TAG = 10000;//奔跑动画标签
const int JUMP_ANIMATE_TAG = 10001;//跳跃动画标签
const int PROTECT_ANIMATE_TAG = 10002;//护盾动画标签
const int PLAYER_TAG = 0;//玩家标签
const int ENEMY_TYPE_1_TAG = 11000; // 地刺//敌人标签
const int ENEMY_TYPE_2_TAG = 11001;//齿轮
const int ENEMY_TYPE_3_TAG = 11002;//飞镖

const int TOOL_BLOOD_TAG = 12000;//血包标签
const int TOOL_COIN_TAG = 12001;//金币标签

const int FRAME_INTERVAL = 1;//每帧间隔时间长度(秒)
const int MAX_FRAME_COUNT = 60;//周期(一个周期的帧数
class ConstUtil
{
public:
	ConstUtil();
	~ConstUtil();
	// 敌人类型
	 //static char * ENEMY_TYPE_DARTS= ENEMY_TYPE_1;// 飞镖
	 //static string  * ENEMY_TYPE_SKIPWEED =new string("skipweed");//地刺


	
};

