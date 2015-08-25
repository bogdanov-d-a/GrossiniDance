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
	
	// create a sprite batch node
	SpriteBatchNode *batchNode = SpriteBatchNode::create("grossini_dance_atlas.png");
	if (!batchNode)
		return false;
	addChild(batchNode);

	return true;
}
