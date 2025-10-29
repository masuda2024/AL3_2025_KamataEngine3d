#include "GameOver.h"
// #include "MapChipField.h"
#include "Skydome.h"

using namespace KamataEngine;

GameOver::~GameOver() { delete fade_; }

void GameOver::Initialize() {
	// 3Dモデル
	// model_ = Model::CreateFromOBJ("titleFont");
	// modelPlayer_ = Model::CreateFromOBJ("player");
	modelBack_ = Model::CreateFromOBJ("Back_UI");
	modelskydome_ = Model::CreateFromOBJ("skydome");
	modelOverFont_ = Model::CreateFromOBJ("OverFont");
	//  カメラ初期化
	camera_.Initialize();

	worldTransform_.Initialize();
	worldTransformPlayer_.Initialize();

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void GameOver::Update() {
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
			
			finishedOver_ = true;
		}
		break;
	}
}

void GameOver::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	// model_->Draw(worldTransform_, camera_);

	// modelPlayer_->Draw(worldTransformPlayer_, camera_);

	modelBack_->Draw(worldTransform_, camera_);

	modelskydome_->Draw(worldTransform_, camera_);

	modelOverFont_->Draw(worldTransform_, camera_);

	Model::PostDraw();

	fade_->Draw();
}
