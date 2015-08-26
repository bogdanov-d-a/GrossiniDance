#include "HelloWorldScene.h"
#include "AnimationKit.h"

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

HelloWorld::HelloWorld()
{}

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

	// create animation kits
	m_danceKit = AnimationKit::create(0.2f);
	if (!m_danceKit.Keeps())
		return false;
	m_spinKit = AnimationKit::create(0.2f);
	if (!m_spinKit.Keeps())
		return false;

	for (int frameNum = 0; frameNum < 14; ++frameNum)
	{
		const int x = frameNum % 5;
		const int y = frameNum / 5;

		SpriteFrame *frame = SpriteFrame::createWithTexture(batchNode->getTexture(),
			Rect(Vec2(x * frameSize.width, y * frameSize.height), frameSize));
		if (!frame)
			return false;

		m_danceKit->GetAnimation()->addSpriteFrame(frame);
		if (frameNum >= 10)
			m_spinKit->GetAnimation()->addSpriteFrame(frame);

		if (frameNum == 14)
			break;
	}

	if (!m_danceKit->InitAction())
		return false;
	if (!m_spinKit->InitAction())
		return false;

	// run the action
	danceSprite->runAction(m_danceKit->GetAction());

	// add event listener keyboard
	auto eventListener = EventListenerKeyboard::create();
	if (!eventListener)
		return false;

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		danceSprite->stopAllActions();
		danceSprite->runAction(m_spinKit->GetAction());
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		danceSprite->stopAllActions();
		danceSprite->runAction(m_danceKit->GetAction());
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	return true;
}
