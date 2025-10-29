#include "Tutorial.h"
// #include "MapChipField.h"
#include "Player.h"
// #include "Fade.h"

using namespace KamataEngine;

Tutorial::~Tutorial() { delete fade_; }

void Tutorial::Initialize() {
	// 3Dモデル
	// model_ = Model::CreateFromOBJ("titleFont");
	// modelPlayer_ = Model::CreateFromOBJ("player");
	modelBack_ = Model::CreateFromOBJ("Back_UI");
	modelskydome_ = Model::CreateFromOBJ("skydome");
	modelTutorialFont_ = Model::CreateFromOBJ("TutorialFont");
	modelTutorialFont2_ = Model::CreateFromOBJ("TutorialFont2");
	

	
	

	// カメラ初期化
	camera_.Initialize();

	worldTransform_.Initialize();
	worldTransformPlayer_.Initialize();

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void Tutorial::Update() {
	switch (phase_) {
	case Phase::kMain:
		if (Input::GetInstance()->PushKey(DIK_E)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			
		}
		break;
	case Phase::kFadeIn:
		fade_->Update();
		if (fade_->isFinished()) {
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->isFinished()) {
			finishedTutorial_ = true;
		}
		break;
	}
}

void Tutorial::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	// model_->Draw(worldTransform_, camera_);

	// modelPlayer_->Draw(worldTransformPlayer_, camera_);

	modelBack_->Draw(worldTransform_, camera_);

	modelskydome_->Draw(worldTransform_, camera_);

	modelTutorialFont_->Draw(worldTransform_, camera_);
	modelTutorialFont2_->Draw(worldTransform_, camera_);

	Model::PostDraw();

	fade_->Draw();
}
