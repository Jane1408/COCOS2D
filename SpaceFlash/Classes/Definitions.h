#pragma once
#include <vector>

const float TRANSITION_TIME = 0.5f;

const float PLAYER_HEALTH = 300.0f;

const int PLAYER_BITMASK = 0x000001;
const int BULLET_BITMASK = 0x000002;
const int ENEMY_BITMASK = 0x000003;
const int ENEMY_BULLET_BITMASK = 0x000004;


const std::vector<int> ONE_SLOT = { 0 };
const std::vector<int> COMMON_DOUBLE_SLOTS = { 37, -37 };
const std::vector<int> FAST_DOUBLE_SLOTS = { 33, -33 };
const std::vector<int> POWER_DOUBLE_SLOTS = { 47, -47 };

