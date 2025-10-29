#pragma once
#include "CameraController.h"
#include "Enemy.h"
#include "Fade.h"
#include "Goal.h"
#include "Grab.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Particle.h"
#include "Player.h"
#include "Skydome.h"
#include "TitleScene.h"
#include <vector>

class GameScene {

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	bool finished_ = false;

	Grab grab_;

	

public:
	enum class Phase {
		kFadeIn,
		kPlay,
		kDeath,
		kFadeOut,
		kFadeOut2,
	};

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// デストラクタ
	~GameScene();

	// 3Dモデル
	KamataEngine::Model* modelBlock_;

	KamataEngine::Model* modelSkydome_ = nullptr;

	KamataEngine::Model* modelPlayer_ = nullptr;

	KamataEngine::Model* modelEnemy_ = nullptr;

	KamataEngine::Model* modelDeathParticle_ = nullptr;

	KamataEngine::Model* modelGrab_ = nullptr;

	KamataEngine::Model* modelGoal_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// 自キャラ
	Player* player_ = nullptr;

	// sky
	Skydome* skydome_ = nullptr;

	// 敵
	std::list<Enemy*> enemies_;

	// ゴール
	Goal* goal_ = nullptr;

	// つかむ場所
	std::vector<Grab*> grabs_;

	// パーティクル
	Particle* Particles_ = nullptr;

	// カメラコントローラ
	CameraController* cameraController_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	void GenerateBlocks();

	void CheckAllCollisions();

	void ChangePhase();

	// ゲームプレイから開始
	Phase phase_;

	bool isFinished() const { return isclear_; }
	bool isFinished2() const { return isover_; }

private:
	// ゲームクリア
	bool nextclear_ = false;
	bool isclear_ = false;

	// ゲームオーバー
	bool nextover_ = false;
	bool isover_ = false;

	bool grabbed = false;

	Fade* fade_ = nullptr;
};