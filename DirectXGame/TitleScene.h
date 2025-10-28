#pragma once
#include "Fade.h"
#include "Skydome.h"
#include <KamataEngine.h>
class TitleScene {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	void Initialize();
	void Update();
	void Draw();
	~TitleScene();

	KamataEngine::Model* model_;
	KamataEngine::Model* modelPlayer_;
	KamataEngine::Model* modelTitle_;
	KamataEngine::Model* modelCredit_;
	KamataEngine::Camera camera_;
	KamataEngine::Model* modelSkydome_;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::WorldTransform worldTransformPlayer_;
	// タイトルからゲーム
	bool isFinished() const { return finished_; }
	// タイトルからチュートリアル
	bool isFinished2() const { return finished2_; }

private:
	bool nextTutorial_ = false;

	// タイトルからゲーム
	bool finished_ = false;

	// タイトルからチュートリアル
	bool finished2_ = false;

	Fade* fade_ = nullptr;

	Phase phase_ = Phase::kFadeIn;
};