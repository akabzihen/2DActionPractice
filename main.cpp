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

//int Input, EdgeInput;      // ���͏��
int FrameStartTime;        // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ�

// �A�N�V�����T���v���v���O�������C���֐�
int ActMain(void);

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);

    // �c�w���C�u�����̏�����
    if (DxLib_Init() == -1) return -1;

    // �A�N�V�����Q�[���̃��C���֐����Ă�
    ActMain();

    // �c�w���C�u�����̌�n��
    DxLib_End();

    // �I��
    return 0;
}

// �A�N�V�����T���v���v���O�������C��
int ActMain(void)
{
    // �`���𗠉�ʂɃZ�b�g
    SetDrawScreen(DX_SCREEN_BACK);

    // ���������M����҂��Ȃ�
    SetWaitVSyncFlag(FALSE);

    // �v���C���[�̏�����
    player.Initialize();
    player.SetPosition(320.0F, 240.0F, 1.0F);

    //��GameStateAction::OnEnter()��
    // �X�e�[�W�̏�����
    //stage_manager.CreateStage();
    //stage_manager.SetStageData(2);

    // �S�[���M�~�b�N�̏�����
    //GimmickBase* goal = gimmick_manager.Create(GimmickBase::GimmickType::Goal);
    //if (goal) {
    //    goal->SetPosition(240.0F, 96.0F,1.0F);
    //}

    // �G�l�~�[�̏�����
    //EnemyBase* test_enemy = enemy_manager.Create(EnemyBase::EnemyType::Test);
    //if (test_enemy) {
    //    test_enemy->SetPosition(660.0F, 408.0F, -1.F);
    //}

    // ���͏�Ԃ̏�����
    input_manager.Initialize();

    // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃^�C���J�E���g�ɃZ�b�g
    FrameStartTime = GetNowCount();

    // ���C�����[�v�J�n�A�d�r�b�L�[�ŊO�ɏo��
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ̃N���A
        ClsDrawScreen();

        // �P/�U�O�b���܂ő҂�
        while (GetNowCount() - FrameStartTime < 1000 / 60) { Sleep(1); }

        // ���݂̃^�C���J�E���g��ۑ�
        FrameStartTime = GetNowCount();

        // ���͏�Ԃ��X�V
        input_manager.Update();

        //GameState�̕ύX
        game_state.Update(0.f);

        // �v���C���[�̈ړ�����
        player.Update(0.f);

        // �V���b�g�̈ړ�����
        bullet_manager.Update();

        // �M�~�b�N�̏���
        gimmick_manager.Update(0.f);

        // �G�l�~�[�̏���
        enemy_manager.Update(0.f);

        // �}�b�v�̕`��
        stage_manager.Render();

        // �M�~�b�N�̕`��
        gimmick_manager.Render();

        // �G�l�~�[�̕`��
        enemy_manager.Render();

        // �L�����N�^�̕`��
        player.Render();

        // �e�̕`��
        bullet_manager.Render();

        // DebugRender�i�����蔻��j�̕`��
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



        // ��ʂ̍X�V
        ScreenFlip();
    }

    // �I��
    return 0;
}