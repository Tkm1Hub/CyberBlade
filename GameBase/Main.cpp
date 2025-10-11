#include "stdafx.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"

// 画面設定
int constexpr SCREEN_WIDTH = 1600;
int constexpr SCREEN_HEIGHT = 900;
int constexpr SCREEN_COLOR = 32;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#ifdef _DEBUG	// コンソールDebug用変数
    FILE* _out;
    FILE* _in;
    // _DEBUG

    // コンソールDebug用
    AllocConsole();							// コンソール
    _out = 0;
    freopen_s(&_out, "CON", "w", stdout);	// stdout
    _in = 0;
    freopen_s(&_in, "CON", "r", stdin);		// stdin
#endif	// _DEBUG

    // ウィンドウモードにする
    ChangeWindowMode(TRUE);


    // DXライブラリの初期化（失敗時は終了）
    if (DxLib_Init() == -1) return -1;

    // 画面のサイズと色深度の設定
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);

    // DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
    // Effekseerを使用するには必ず設定する。
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // Effekseerを初期化する。
    // 引数には画面に表示する最大パーティクル数を設定する。
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);

    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);

    // 裏画面に描画
    SetDrawScreen(DX_SCREEN_BACK);

    std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();

    sceneManager->Add<TitleScene>("Title");
    sceneManager->Add<GameScene>("Game");

    // メインゲームループ（ESCキー or ウィンドウ閉じる まで続く）
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // DXライブラリのカメラとEffekseerのカメラを同期する。
        Effekseer_Sync3DSetting();

        auto prevTime = GetNowHiPerformanceCount();  // フレーム開始時刻


        // 更新処理
        sceneManager->Update();

        // 画面の初期化
        ClearDrawScreen();

        // 描画処理
        sceneManager->Draw();

        ScreenFlip();      // 表画面に反映（ダブルバッファリング）

        // 簡易的なFPS固定（60fps = 約16667マイクロ秒）
        auto afterTime = GetNowHiPerformanceCount();
        while (afterTime - prevTime < 16667)
        {
            afterTime = GetNowHiPerformanceCount();
        }
    }

    // Effekseerを終了する。
    Effkseer_End();

    // DXライブラリの終了処理
    DxLib_End();

#ifdef _DEBUG	// コンソールDebug用
    fclose(_out); fclose(_in); FreeConsole();//コンソール解放
#endif	// _debug

    return 0; // 正常終了
}
