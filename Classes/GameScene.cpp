#include "GameScene.h"
#include "SimpleAudioEngine.h"
//make a datamanager class later
USING_NS_CC;

Scene* GameScene::createScene() {
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameScene::create();

	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;

}

bool GameScene::init() {
	//code here LOL

	int i = 0;
	paddle = Sprite::create("paddle.png");
	paddle->setPosition(200, 200);
	paddle->setAnchorPoint(Vec2(0, 0));
	this->addChild(paddle);
	curDir = 'x';
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleSize();

	//create physics
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 * origin.x, visibleSize.height / 2 * origin.y));

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	for (i = 0; i < 10; i++) {
		auto block = Sprite::create("blockpnghere.png");
	}

	//creating keyboard listener
	auto kbListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	kbListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] == std::chrono::high_resolution_clock::now();
		}
		return true;
	};
	kbListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys.erase(keyCode);
	};


	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(kbListener, paddle);
	this->scheduleUpdate();
	return true;


}
bool GameScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys.find(keyCode) != keys.end())
		return true;
	return false;
}

void GameScene::playerMovement(EventKeyboard::KeyCode keyCode) {
	pos = paddle->getPosition();
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		curDir = 'a';
			
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		curDir = 'd';
	}
	else curDir = 'n';
	
}

void GameScene::update(float delta) {
	pos = paddle->getPosition();
	Node::update(delta);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		curDir = 'a';
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		curDir = 'd';
	}
	else curDir = 'n';

	if (curDir == 'a') {
		pos.x = pos.x - 150 * delta;
	}
	if (curDir == 'd') {
		pos.x = pos.x + 150 * delta;
	}
	paddle->setPosition(pos);
}
std::map<cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point> GameScene::keys;