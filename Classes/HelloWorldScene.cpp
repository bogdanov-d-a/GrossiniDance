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
	danceSprite->setAnchorPoint(Vec2());
	danceSprite->setPosition(roundf((winSize.width - frameSize.width) / 2),
		roundf((winSize.height - frameSize.height) / 2));

	// create animations
	Animation *danceAnimation = Animation::create();
	if (!danceAnimation)
		return false;
	danceAnimation->setDelayPerUnit(0.2f);

	Animation *spinAnimation = Animation::create();
	if (!spinAnimation)
		return false;
	spinAnimation->setDelayPerUnit(0.2f);

	for (int frameNum = 0; frameNum < 14; ++frameNum)
	{
		const int x = frameNum % 5;
		const int y = frameNum / 5;

		SpriteFrame *frame = SpriteFrame::createWithTexture(batchNode->getTexture(),
			Rect(Vec2(x * frameSize.width, y * frameSize.height), frameSize));
		if (!frame)
			return false;

		danceAnimation->addSpriteFrame(frame);
		if (frameNum >= 10)
			spinAnimation->addSpriteFrame(frame);

		if (frameNum == 14)
			break;
	}

	// create dance action
	Animate *danceActionOnce = Animate::create(danceAnimation);
	if (!danceActionOnce)
		return false;
	m_danceAction = RepeatForever::create(danceActionOnce);
	if (!m_danceAction.Keeps())
		return false;

	// create spin action
	Animate *spinActionOnce = Animate::create(spinAnimation);
	if (!spinActionOnce)
		return false;
	m_spinAction = RepeatForever::create(spinActionOnce);
	if (!m_spinAction.Keeps())
		return false;

	// run the action
	danceSprite->runAction(m_danceAction);

	// add event listener keyboard
	auto eventListener = EventListenerKeyboard::create();
	if (!eventListener)
		return false;

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		danceSprite->stopAllActions();
		danceSprite->runAction(m_spinAction);
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		danceSprite->stopAllActions();
		danceSprite->runAction(m_danceAction);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	return true;
}
