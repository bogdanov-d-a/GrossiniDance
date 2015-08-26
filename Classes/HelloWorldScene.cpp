#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	if (!scene)
		return nullptr;
	
	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	if (!layer)
		return nullptr;

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
		return false;

	const Size frameSize(85, 121);

	// create a sprite batch node
	SpriteBatchNode *batchNode = SpriteBatchNode::create("grossini_dance_atlas.png");
	if (!batchNode)
		return false;
	addChild(batchNode);

	// create a sprite
	Sprite *danceSprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(Vec2(), frameSize));
	if (!danceSprite)
		return false;
	batchNode->addChild(danceSprite);

	// center the sprite
	Size winSize = Director::getInstance()->getWinSize();
	danceSprite->setPosition(winSize.width / 2, winSize.height / 2);

	// create an animation
	Animation *danceAnimation = Animation::create();
	danceAnimation->setDelayPerUnit(0.2f);
	for (int frameNum = 0; frameNum < 14; ++frameNum)
	{
		const int x = frameNum % 5;
		const int y = frameNum / 5;

		SpriteFrame *frame = SpriteFrame::createWithTexture(batchNode->getTexture(),
			Rect(Vec2(x * frameSize.width, y * frameSize.height), frameSize));
		if (!frame)
			return false;
		danceAnimation->addSpriteFrame(frame);

		if (frameNum == 14)
			break;
	}

	// create an action
	Animate *danceAction = Animate::create(danceAnimation);
	if (!danceAction)
		return false;
	RepeatForever *repeat = RepeatForever::create(danceAction);
	if (!repeat)
		return false;

	// run the action
	danceSprite->runAction(repeat);

	return true;
}
