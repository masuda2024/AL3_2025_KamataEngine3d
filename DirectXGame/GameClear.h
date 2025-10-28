#pragma once
#include "KamataEngine.h"

#include "Fade.h"

#include "Player.h"
#include "Skydome.h"
class GameClear {
public:
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};
	void Initialize();
	void Update();
	void Draw();
	~GameClear();

	KamataEngine::Model* model_;
	KamataEngine::Model* modelPlayer_;
	KamataEngine::Model* modelBack_;
	KamataEngine::Camera camera_;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::WorldTransform worldTransformPlayer_;

	// 天球
	KamataEngine::Model* modelskydome_ = nullptr;
	Skydome* skydome_ = nullptr;

    KamataEngine::Model* modelClearFont_;

	// デスフラグのgetter
	bool IsFinishedClear() const { return finishedClear_; }

private:
	// 終了フラグ
	bool finishedClear_ = false;

	// フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;
};
