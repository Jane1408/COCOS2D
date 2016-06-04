#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "WaveCommander.h"


class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	cocos2d::Size m_visibleSize;
	void CheckWave(float dt);
	bool onTouchBegan(cocos2d::Touch* pTouches, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void CheckGameCollision(cocos2d::PhysicsBody & first, cocos2d::PhysicsBody & second);
	bool onContactBegin(cocos2d::PhysicsContact &contact);


	cocos2d::RefPtr<Player> m_player;
	WaveCommander * commander;
};

