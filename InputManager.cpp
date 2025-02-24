#include "InputManager.h"
#include "DxLib.h"

void InputManager::Initialize()
{
    input_ = 0;
    edge_input_ = 0;
}

void InputManager::Update()
{
    // �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
    i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // �G�b�W����������͂��Z�b�g
    edge_input_ = i & ~input_;

    // ���͏�Ԃ̕ۑ�
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