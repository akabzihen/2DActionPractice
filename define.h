#pragma once

#define SCREEN_WIDTH     (640)                          // 画面の横幅
#define SCREEN_HEIGHT    (480)                          // 画面の縦幅
#define CHIP_SIZE        (32)                           // 一つのチップのサイズ
#define MAP_WIDTH        (60)                           // マップの横幅
#define MAP_HEIGHT       (SCREEN_HEIGHT / CHIP_SIZE)    // マップの縦幅

#define G                (0.3F)                         // キャラに掛かる重力加速度
#define JUMP_POWER       (9.0F)                         // キャラのジャンプ力
#define SPEED            (5.0F)                         // キャラの移動スピード
#define CHAR_SIZE        (30)                           // プレイヤーのサイズ
#define MAX_SHOT	100                                  //ショットの最大数
//#define MAX_ENEMY_SHOT 1
#define MAX_GIMMICK 10
#define MAX_ENEMY 10