#pragma once
#include"KamataEngine.h"

//ゲームシーン
class GameScene
{
public:
	//初期化	
	 
	~GameScene(); //~はdelete 	
	void Initialize();

	uint32_t textureHandle_ = 0;
	

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;

    //更新
	void Update();

	//描画
	void Draw();
};