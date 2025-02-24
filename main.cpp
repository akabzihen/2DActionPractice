#include "stdafx.h"
#include "bullet.h"
#include "player.h"
#include "StageManager.h"
#include "InputManager.h"
#include "BulletManager.h"
#include "GimmickManager.h"
#include "EnemyManager.h"
#include "DebugManager.h"

#include "GameState.h"

Player player;
StageManager stage_manager;
InputManager input_manager;
BulletManager bullet_manager;
GimmickManager gimmick_manager;
EnemyManager enemy_manager;
DebugManager debug_manager;

GameState game_state;

//int Input, EdgeInput;      // 入力状態
int FrameStartTime;        // ６０ＦＰＳ固定用、時間保存用変数

// アクションサンプルプログラムメイン関数
int ActMain(void);

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);

    // ＤＸライブラリの初期化
    if (DxLib_Init() == -1) return -1;

    // アクションゲームのメイン関数を呼ぶ
    ActMain();

    // ＤＸライブラリの後始末
    DxLib_End();

    // 終了
    return 0;
}

// アクションサンプルプログラムメイン
int ActMain(void)
{
    // 描画先を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);

    // 垂直同期信号を待たない
    SetWaitVSyncFlag(FALSE);

    // プレイヤーの初期化
    player.Initialize();
    player.SetPosition(320.0F, 240.0F, 1.0F);

    //↓GameStateAction::OnEnter()で
    // ステージの初期化
    //stage_manager.CreateStage();
    //stage_manager.SetStageData(2);

    // ゴールギミックの初期化
    //GimmickBase* goal = gimmick_manager.Create(GimmickBase::GimmickType::Goal);
    //if (goal) {
    //    goal->SetPosition(240.0F, 96.0F,1.0F);
    //}

    // エネミーの初期化
    //EnemyBase* test_enemy = enemy_manager.Create(EnemyBase::EnemyType::Test);
    //if (test_enemy) {
    //    test_enemy->SetPosition(660.0F, 408.0F, -1.F);
    //}

    // 入力状態の初期化
    input_manager.Initialize();

    // ６０ＦＰＳ固定用、時間保存用変数を現在のタイムカウントにセット
    FrameStartTime = GetNowCount();

    // メインループ開始、ＥＳＣキーで外に出る
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 画面のクリア
        ClsDrawScreen();

        // １/６０秒立つまで待つ
        while (GetNowCount() - FrameStartTime < 1000 / 60) { Sleep(1); }

        // 現在のタイムカウントを保存
        FrameStartTime = GetNowCount();

        // 入力状態を更新
        input_manager.Update();

        //GameStateの変更
        game_state.Update(0.f);

        // プレイヤーの移動処理
        player.Update(0.f);

        // ショットの移動処理
        bullet_manager.Update();

        // ギミックの処理
        gimmick_manager.Update(0.f);

        // エネミーの処理
        enemy_manager.Update(0.f);

        // マップの描画
        stage_manager.Render();

        // ギミックの描画
        gimmick_manager.Render();

        // エネミーの描画
        enemy_manager.Render();

        // キャラクタの描画
        player.Render();

        // 弾の描画
        bullet_manager.Render();

        // DebugRender（当たり判定）の描画
        debug_manager.DebugRender();

        //int change_stage_index = -1;
        //bool is_requested_change_stage = false;
        //if (input_manager.IsTrigger(PAD_INPUT_4)) {
        //    is_requested_change_stage = true;
        //    change_stage_index = 1;
        //}
        //else if (input_manager.IsTrigger(PAD_INPUT_5)) {
        //    is_requested_change_stage = true;
        //    change_stage_index = 2;
        //}

        //if (is_requested_change_stage) {
        //    player.Initialize();
        //    player.SetPosition(320.0F, 240.0F);
        //    stage_manager.SetStageData(change_stage_index);
        //}



        // 画面の更新
        ScreenFlip();
    }

    // 終了
    return 0;
}