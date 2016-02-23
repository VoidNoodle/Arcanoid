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
	int n = 0;
	int blockX = 50;
	int blockY = 600;
	curDir = 'x';
	paddle = Sprite::create("paddle.png");
	paddle->setPosition(200, 100);
	paddle->setAnchorPoint(Vec2(0, 0));
	this->addChild(paddle);
	
	ball = Sprite::create("ball.png");
	ball->setPosition(200, 400);
	paddle->setAnchorPoint(Vec2(0, 0));
	this->addChild(ball);

	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create physics
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + origin.y));
	edgeNode->setAnchorPoint(Vec2(0, 0));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	for (n = 0; n < 5; n++) {
		for (i = 0; i < 10; i++) {
			block = Sprite::create("normal_block.png");
			block->setPosition(blockX, blockY);
			block->setAnchorPoint(Vec2(0, 0));
			this->addChild(block);

			blockX += 39;
		}
		blockY -= 30;
		blockX = 50;
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