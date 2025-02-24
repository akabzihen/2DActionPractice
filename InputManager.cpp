#include "InputManager.h"
#include "DxLib.h"

void InputManager::Initialize()
{
    input_ = 0;
    edge_input_ = 0;
}

void InputManager::Update()
{
    // パッド１とキーボードから入力を得る
    i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // エッジを取った入力をセット
    edge_input_ = i & ~input_;

    // 入力状態の保存
    input_ = i;
}

bool InputManager::IsActive(unsigned int mask)
{
    return (input_ & mask) != 0;
}

bool InputManager::IsTrigger(unsigned int mask)
{
    return (edge_input_ & mask) != 0;
}