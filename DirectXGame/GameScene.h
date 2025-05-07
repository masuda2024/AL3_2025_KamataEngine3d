#pragma once
#include"KamataEngine.h"
#include"Player.h"
#include"vector"
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


	
	std::vector<std::vector<KamataEngine::WorldTransform*>>worldTransformBlocks_;


	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;



	//自キャラ
	Player* player_ = nullptr;



    //更新
	void Update();

	//描画
	void Draw();
};