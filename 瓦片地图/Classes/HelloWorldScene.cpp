#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	// 读取地图
	TMXTiledMap * tileMap = dynamic_cast<TMXTiledMap *>(rootNode->getChildByName("Map_1"));
	// 读取对象层
	TMXObjectGroup * walk = tileMap->getObjectGroup("meta");
	// 读取所有标识点序列
	ValueVector path = walk->getObjects();
	int size = path.size();
		// 读出标识点坐标
		Point * points = new Point[size];
	int n = 0;
	for (auto pos : path) {
		ValueMap map=pos.asValueMap();
		points[n] = Point(map["x"].asInt(),
			map["y"].asInt());
		n++;

	}

	//构建序列动作
	Vector <FiniteTimeAction *> actionsArray;
	
	int delta = points[0].distance(points[1]);
	for (int i = 0; i < size-1; i++) {
		actionsArray.pushBack(MoveTo::create(
			5 * (points[i].distance(points[i + 1]) / delta), points[i + 1]));
	}
	Sequence * seq = Sequence::create(actionsArray);
	Sprite * monster =  dynamic_cast<Sprite *> (rootNode->getChildByName("monster"));
	monster->runAction(seq);
    return true;
}
