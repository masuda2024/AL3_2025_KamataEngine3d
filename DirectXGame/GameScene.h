#pragma once
#include"KamataEngine.h"
#include"Player.h"
#include"Skydome.h"
#include<vector>
#include"MapChipField.h"
//ゲームシーン
class GameScene
{
public:
	//初期化	
	 
	~GameScene(); //~はdelete 	
	void Initialize();

	uint32_t textureHandle_ = 0;
	

	KamataEngine::Model* modelBlock_ = nullptr;//modelBlock

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;


	//可変個配列
	std::vector<std::vector<KamataEngine::WorldTransform*>>worldTransformBlocks_;


	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;




	//自キャラ
	Player* player_ = nullptr;



	//天球
	Skydome* skydome_ = nullptr;
	KamataEngine::Model* modelskydome_ = nullptr;

	//マップチップフィールド
	MapChipField* mapChipField_;
	
	void GenerateBlocks();



    //更新
	void Update();

	//描画
	void Draw();
};