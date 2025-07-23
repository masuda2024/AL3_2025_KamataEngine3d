#pragma once
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "CameraController.h"
#include "DeathParticle.h"
#include <vector>
// ゲームシーン




class GameScene
{
public:


	// 終了フラグ
	bool finished_ = false;
	// デスフラグのgetter
	bool IsFinished() const { return finished_; }



	void GenerateBlocks();

	// 初期化
	void Initialize();

	//全ての当たり判定
	void CheckAllCollisions();

	//フェーズの切り替え
	void ChangePhase();


	//ゲームのフェーズ(型)
	enum class Phase
	{ 
		kPlay,  //ゲームプレイ
		kDeath, //デス演出
	};
	//ゲームの現在フェーズから開始
	Phase phase_;



	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバックカメラの生成
	// debugCamera_ = new DebugCamera();

	// 天球
	KamataEngine::Model* modelskydome_ = nullptr;

	// モデルプレイヤー
	KamataEngine::Model* modelPlayer_ = nullptr;
	
	//敵
	KamataEngine::Model* modelEnemy_ = nullptr;
	
	//パーティクル
	KamataEngine::Model* modelParticle_ = nullptr;






	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;



	//モデルパーティクル
	DeathParticle* deathParticles_ = nullptr;

	


	//敵
	//Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;




	// キューブ
	Skydome* skydome_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;

	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	// 3D
	KamataEngine::Model* cube_ = nullptr;

	// カメラコントロール
	CameraController* cameraController_ = nullptr;
	// void Initialize();
	// KamataEngine::Model* cameraModel_;

	// デストラクタ
	~GameScene();

	// 更新
	void Update();

	// 描画
	void Draw();
};
