#pragma once
#include <vector>

const float TRANSITION_TIME = 0.5f;

const float PLAYER_HEALTH = 300.0f;

const float ENEMY_DELTA_START = 200.0f;

const int PLAYER_BITMASK = 0x000001;
const int BULLET_BITMASK = 0x000002;
const int ENEMY_BITMASK = 0x000003;
const int ENEMY_BULLET_BITMASK = 0x000004;

const int HEALTH_BITMASK = 0x000005;
const int SHIELD_BITMASK = 0x000006;
const int POWER_BITMASK = 0x000007;
const int BOMB_BITMASK = 0x000008;

const float BONUCE_HEALTH = 20.0f;
const float BONUCE_TIME = 10.0f;
const float FONT_SIZE = 0.07f;


const std::vector<int> ONE_SLOT = { 0 };
const std::vector<int> COMMON_DOUBLE_SLOTS = { 37, -37 };
const std::vector<int> FAST_DOUBLE_SLOTS = { 33, -33 };
const std::vector<int> POWER_DOUBLE_SLOTS = { 47, -47 };

const std::string HP_LINE = "life.png";
const std::string PROGRESS_LINE = "enemyy.png";
const std::string ACTIVE_SHIELD = "shield_active.png";

const std::string HERO_IMG = "hero_spase_ship.png";

const std::string COMMON_IMG = "enemy_space_ship1.png";
const std::string DOUBLE_COMMON_IMG = "enemy_space_ship3.png";
const std::string HEAVY_COMMON_IMG = "enemy_space_ship2.png";
const std::string FAST_DOUBLE_IMG = "enemy_space_ship4.png";
const std::string POWER_DOUBLE_IMG = "enemy_space_ship5.png";
const std::string VERY_HEAVY_IMG = "enemy_space_ship6.png";
const std::string FIRST_BOSS_IMG = "enemy_boss.png";
const std::string SECOND_BOSS_IMG = "enemy_boss2.png";
const std::string THIRD_BOSS_IMG = "enemy_boss3.png";

const std::string HEALTH_IMG = "Health.png";
const std::string SHIELD_IMG = "Shield.png";
const std::string POWER_BONUCE_IMG = "Power.png";
const std::string BOMB_IMG = "Bomb.png";

const std::string NORMAL_IMG = "enemy_bullet.png";
const std::string FAST_IMG ="fast_bullet.png";
const std::string POWER_IMG = "power_bullet.png";
const std::string ROCKET_IMG ="rocket.png";
const std::string HERO_NORMAL_IMG = "hero_bullet.png";

const float COMMON_HP = 60.0f;
const float DOUBLE_COMMON_HP = 60.0f;
const float HEAVY_COMMON_HP = 100.0f;
const float FAST_DOUBLE_HP = 120.0f;
const float POWER_DOUBLE_HP = 120.0f;
const float VERY_HEAVY_HP = 200.0f;
const float FIRST_BOSS_HP = 350.0f;
const float SECOND_BOSS_HP = 550.0f;
const float THIRD_BOSS_HP = 700.0f;

const float COMMON_SF = 0.6f;
const float DOUBLE_COMMON_SF = 0.75f;
const float HEAVY_COMMON_SF = 0.6f;
const float FAST_DOUBLE_SF = 0.9f;
const float POWER_DOUBLE_SF = 1.2f;
const float VERY_HEAVY_SF = 0.9f;
const float FIRST_BOSS_SF = 0.8f;
const float SECOND_BOSS_SF = 0.7f;
const float THIRD_BOSS_SF = 0.6f;

const std::string LOSE_SPLASH_IMG = "game_over.png";
const std::string WIN_SPLASH_IMG = "win.png";

const std::string SPLASH_IMG = "splash.png";
const std::string BG_IMG = "BG.png";

const std::string PLAY_BUTTON = "play.png";
const std::string PLAY_BUTTON_CLICKED = "PLAY_Clicked.png";

const std::string MAIN_FONT = "text.ttf";

const std::string UPDATE_WAVE_HP = "updateWaveHP";
const std::string END_GAME = "EndGame";
const std::string WIN_GAME = "WinGame";

const std::string BONUCE_SOUND = "sounds/bonus.wav";
const std::string SHOOT_SOUND = "sounds/bullet.wav";
const std::string D_SHOOT_SOUND = "sounds/bullet_x2.wav";
const std::string ROCKET_SOUND = "sounds/rocket.wav";
const std::string EXPLOSION_SOUND = "sounds/explosion.wav";
const std::string BOSS_EXPLOSION_SOUND = "sounds/explosion2.wav";
const std::string BG_SOUND = "sounds/music.wav";
const std::string GAMEOVER_SOUND = "sounds/gameover.WAV";



namespace std
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream ss;
		ss << n;
		return ss.str();
	}
}

