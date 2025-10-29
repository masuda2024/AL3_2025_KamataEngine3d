#include"TitleScene.h"

using namespace KamataEngine;

TitleScene::~TitleScene() { delete fade_; }

void TitleScene::Initialize() {
	// 3Dモデル
	model_ = Model::CreateFromOBJ("titleFont");
	// modelPlayer_ = Model::CreateFromOBJ("player");
	modelTitle_ = Model::CreateFromOBJ("Title_UI");
	modelCredit_ = Model::CreateFromOBJ("Credit");
	modelSkydome_ = Model::CreateFromOBJ("skydome");
	
	
	
	
	
	
	
	// カメラ初期化
	camera_.Initialize();

	worldTransform_.Initialize();
	worldTransformPlayer_.Initialize();

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void TitleScene::Update() {

	switch (phase_) {
	case Phase::kMain:
		// スペースキーでゲーム
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			
		}

		// Tキーを押してチュートリアル
		if (Input::GetInstance()->PushKey(DIK_T)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			
			nextTutorial_ = true;
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
			if (nextTutorial_ == true) {
				finished2_ = true;
			} else {
				finished_ = true;
			}
		}
		break;
	}
}

void TitleScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	model_->Draw(worldTransform_, camera_);

	// modelPlayer_->Draw(worldTransformPlayer_, camera_);

	modelTitle_->Draw(worldTransform_, camera_);
	modelSkydome_->Draw(worldTransform_, camera_);
	modelCredit_->Draw(worldTransform_, camera_);
	Model::PostDraw();

	fade_->Draw();
}
