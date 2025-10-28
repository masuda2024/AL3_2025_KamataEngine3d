#include "GameClear.h"
#include "GameOver.h"
#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include "Tutorial.h"
#include <Windows.h>

enum class Scene {

	kUnknow = 0,

	kTitle,
	kTutorial,
	kGame,
	kGameClear,
	kGameOver,
};

Scene scene = Scene::kUnknow;

using namespace KamataEngine;

void ChangeScene();

void UpdateScene();

void DrawScene();

GameScene* gameScene = nullptr;

TitleScene* titleScene = nullptr;

Tutorial* tutorial = nullptr;

GameClear* gameclear = nullptr;

GameOver* gameover = nullptr;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"2168_上がれロケット");

	// DirectXCommon*インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// タイトルから始まる
	scene = Scene::kTitle;

	// タイトル
	titleScene = new TitleScene;
	titleScene->Initialize();

	// チュートリアル
	tutorial = new Tutorial;
	tutorial->Initialize();

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	// ゲームクリア
	gameclear = new GameClear;
	gameclear->Initialize();

	// ゲームオーバー
	gameover = new GameOver;
	gameover->Initialize();

	// メインループ
	while (true) {

		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// ゲームシーンの更新
		ChangeScene();

		// 描画開始
		UpdateScene();
		dxCommon->PreDraw();

		// ゲームシーンの描画
		DrawScene();

		// 描画終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;

	// nullptrの代入
	gameScene = nullptr;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->isFinished()) {
			// scene変化
			scene = Scene::kGame;
			// 旧scene開放
			delete titleScene;
			titleScene = nullptr;
			// 新scene生成と初期化
			gameScene = new GameScene;
			gameScene->Initialize();
		}

		else if (titleScene->isFinished2()) {
			// scene変化
			scene = Scene::kTutorial;
			// 旧scene開放
			delete titleScene;
			titleScene = nullptr;
			// 新scene生成と初期化
			tutorial = new Tutorial;
			tutorial->Initialize();
		}
		break;

	case Scene::kTutorial:
		if (tutorial->isFinishedTutorial()) {
			// scene変化
			scene = Scene::kTitle;
			// 旧scene開放
			delete tutorial;
			tutorial = nullptr;
			// 新scene生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;

	case Scene::kGame:
		// ゲームシーンの更新処理
		if (gameScene) {

			if (gameScene->isFinished()) {
				// scene変化
				scene = Scene::kGameClear;
				// 旧scene開放
				delete gameScene;
				gameScene = nullptr;
				// 新scene生成と初期化
				gameclear = new GameClear;
				gameclear->Initialize();
			} else if (gameScene->isFinished2()) {
				// scene変化
				scene = Scene::kGameOver;
				// 旧scene開放
				delete gameScene;
				gameScene = nullptr;
				// 新scene生成と初期化
				gameover = new GameOver;
				gameover->Initialize();
			}
		}
		break;

	case Scene::kGameClear:

		if (gameclear->IsFinishedClear()) {
			// scene変化
			scene = Scene::kTitle;
			// 旧scene開放
			delete gameclear;
			gameclear = nullptr;
			// 新scene生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;

	case Scene::kGameOver:

		if (gameover->IsFinishedOver()) {
			// scene変化
			scene = Scene::kTitle;
			// 旧scene開放
			delete gameover;
			gameover = nullptr;
			// 新scene生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;

	case Scene::kTutorial:
		tutorial->Update();
		break;

	case Scene::kGame:
		gameScene->Update();
		break;

	case Scene::kGameClear:
		gameclear->Update();
		break;

	case Scene::kGameOver:
		gameover->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene) {
			titleScene->Draw();
		}
		break;
	case Scene::kTutorial:
		if (tutorial) {
			tutorial->Draw();
		}
		break;

	case Scene::kGame:
		if (gameScene) {
			gameScene->Draw();
		}
		break;
	case Scene::kGameClear:
		if (gameclear) {
			gameclear->Draw();
		}
		break;
	case Scene::kGameOver:
		if (gameover) {
			gameover->Draw();
		}
		break;
	}
}