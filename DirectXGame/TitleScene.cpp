/**/
#include"TitleScene.h"
#include "Player.h"
#include "MapChipField.h"

using namespace KamataEngine;


void TitleScene::Initialize()
{
	//3Dモデルの生成
	model_ = Model::CreateFromOBJ("titleFont");
	modelPlayer_ = Model::CreateFromOBJ("player");
	//カメラの初期化
	camera_.Initialize();
	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransformPlayer_.Initialize();
}

void TitleScene::Update()
{


	if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
		finished_ = true;
	}


	/*
	// 自キャラの更新
	player_->Update();
    */
}

void TitleScene::Draw() 
{
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	//ここに3Dモデルインスタンスの描画処理を記述する
	model_->Draw(worldTransform_, camera_);
	modelPlayer_->Draw(worldTransformPlayer_, camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();
}
