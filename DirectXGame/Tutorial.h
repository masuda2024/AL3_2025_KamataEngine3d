#pragma once
#include "KamataEngine.h"

#include "Fade.h"

#include "Player.h"
#include "Skydome.h"
class Tutorial {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	void Initialize();
	void Update();
	void Draw();
	~Tutorial();

	KamataEngine::Model* model_;
	KamataEngine::Model* modelPlayer_;
	KamataEngine::Model* modelBack_;
	KamataEngine::Camera camera_;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::WorldTransform worldTransformPlayer_;

	// 天球
	KamataEngine::Model* modelskydome_ = nullptr;
	Skydome* skydome_ = nullptr;

	KamataEngine::Model* modelTutorialFont_;

	KamataEngine::Model* modelTutorialFont2_;


	// チュートリアルからタイトル
	bool isFinishedTutorial() const { return finishedTutorial_; }

private:

	// 音声再生ハンドル
	uint32_t soundHandle_ = 0;
	uint32_t voiceHandle_ = 0;


	// チュートリアルからタイトル
	bool finishedTutorial_ = false;

	// フェード
	Fade* fade_ = nullptr;
	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;
};
