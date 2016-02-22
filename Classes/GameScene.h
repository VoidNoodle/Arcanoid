#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <map>
#include <vector>
class GameScene : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void update(float) override;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	void playerMovement(cocos2d::EventKeyboard::KeyCode);

	CREATE_FUNC(GameScene);
private:
	char curDir;
	cocos2d::Sprite* paddle;
	cocos2d::Vec2 pos;
	static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;
	
public: 
	
};
