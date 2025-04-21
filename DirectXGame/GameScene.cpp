#include"GameScene.h"

using namespace KamataEngine;



GameScene::~GameScene()
{
	delete model_;
	//自キャラの解放
	delete player_;
}



void GameScene::Initialize()
{
	

	textureHandle_ = TextureManager::Load("block.png");

	model_ = Model::Create();//////



	worldTransform_.Initialize();
	camera_.Initialize();


	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize( model_,  textureHandle_, &camera_);

	
}

void GameScene::Update()
{
	//自キャラの更新
	player_->Update();
}

void GameScene::Draw() 
{
	



	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	// 自キャラの描画
	player_->Draw();
	//model_->Draw(worldTransform_,camera_,textureHandle_);


	Model::PostDraw();

	
}