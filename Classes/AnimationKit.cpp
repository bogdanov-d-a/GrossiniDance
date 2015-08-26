#include "AnimationKit.h"

USING_NS_CC;

AnimationKit* AnimationKit::create(float delay, bool repeat)
{
	AnimationKit *pRet = new (std::nothrow) AnimationKit();
	if (pRet && pRet->init(delay, repeat))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool AnimationKit::init(float delay, bool repeat)
{
	m_animation = Animation::create();
	if (!m_animation)
		return false;
	m_animation->setDelayPerUnit(delay);

	m_action = Animate::create(m_animation);
	if (!m_action.Keeps())
		return false;

	if (repeat)
	{
		m_action = RepeatForever::create(m_action);
		if (!m_action.Keeps())
			return false;
	}

	return true;
}

Animation* AnimationKit::GetAnimation() const
{
	return m_animation;
}

ActionInterval* AnimationKit::GetAction() const
{
	return m_action;
}
