#include "GameScene.h"
#include "MapChipField.h"
#include "MyMath.h"
#include "CameraController.h"
#include "Player.h"
using namespace KamataEngine;

GameScene::~GameScene() 
{
	// モデルの解放(ブロックを並べる)
	delete modelBlock_;

	delete modelPlayer_;

	// 自キャラの解放
	delete player_;

	//カメラコントローラーの解放
	delete cameraController_;

	// 天球の解放
	delete skydome_;

	// マップチップフィールドの解放
	delete mapChipField_;

	/*
	for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlocks_)
	{
	    delete worldTransformBlock;
	}
	*/

	// ブロックの解放
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete debugCamera_;
}

void GameScene::Initialize()
{


	// textureHandle_ = TextureManager::Load("block.png");
	// textureHandle_ = TextureManager::Load("block.png");

	// modelBlock_ = Model::Create(); //////
	modelBlock_ = Model::CreateFromOBJ("block");

	// 自キャラ
	modelPlayer_ = Model::CreateFromOBJ("player");

	worldTransform_.Initialize();
	camera_.Initialize();




	//マップチップフィールドの生成
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	GenerateBlocks();



	// 自キャラの生成
	player_ = new Player();
	


	player_->SetMapChipField(mapChipField_);



	

	// カメラコントローラーの生成
	cameraController_ = new CameraController();
	// カメラコントローラーの初期化
	cameraController_->Initialize();
	// 追従対象をリセット
	cameraController_->SetTarget(player_);
	// リセット(瞬間合わせ)
	cameraController_->Reset();

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);


	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);
	//player_->Initialize( modelPlayer_,  textureHandle_, &camera_);
	player_->Initialize(modelPlayer_, &camera_, playerPosition);

	// 天球の生成
	modelskydome_ = KamataEngine::Model::CreateFromOBJ("skydome", true);
	// 天球の初期化
	skydome_ = new Skydome();
	skydome_->Initialize(modelskydome_, textureHandle_, &camera_);

	

	

	// 要素数
	// const uint32_t kNumBlockVirtical = 10;
	// const uint32_t kNumBlockHorizontal = 20;

	// ブロック1個分の横幅
	// const float kBlockWidth = 2.0f;
	// const float kBlockHeight = 2.0f;

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::GenerateBlocks() 
{

	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) 
	{
		// 1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i)
	{
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) 
		{
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock)
			{
				KamataEngine::WorldTransform* worldTransform = new KamataEngine::WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);

				// worldTransformBlocks_[i][j] = new KamataEngine::WorldTransform();
				// worldTransformBlocks_[i][j]->Initialize();
				// worldTransformBlocks_[i][j]->translation_.x = (kBlockWidth+2) * j;
				// worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
			}
		}
	}
}

void GameScene::Update()
{
	// 自キャラの更新
	player_->Update();


	//カメラコントローラーの更新
	cameraController_->Update();


	// 天球の更新
	skydome_->Update();

	// ブロックの更新
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) 
	{
		for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlockLine)
		{

			if (!worldTransformBlock)
				continue;

			// アフィン変換行列の作成
			worldTransformBlock->matWorld_ = MakeAffinMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			// worldTransformBlock->matWorld_=アフィン変換行列;

			// 定数バッファに転送する
			worldTransformBlock->TransferMatrix();
		}
	}

	// デバッグカメラの更新
	debugCamera_->Update();
#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_O)) 
	{
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	// カメラの処理
	if (isDebugCameraActive_)
	{
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	} else 
	{


		//////////
		camera_.matView = cameraController_->GetViewProjection().matView;
		camera_.matProjection = cameraController_->GetViewProjection().matProjection;
		//////////


		// ビュープロジェクション行列の更新と転送
		//camera_.UpdateMatrix();
		camera_.TransferMatrix();
	}


	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);



}


void GameScene::Draw() 
{

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	// 自キャラの描画
	player_->Draw();
	// model_->Draw(worldTransform_,camera_,textureHandle_);

	// 天球の描画
	skydome_->Draw();

	// ブロックの描画
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
	{
		for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlockLine) 
		{
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}

	Model::PostDraw();
}