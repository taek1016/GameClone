#ifndef Enum_h__
#define Enum_h__

enum FRAME_ENUM		{ FRAME_60, FPS_END };
enum TIMER_ENUM		{ TIMER_60FPS, TIMER_IMMEDIATE, TIMER_END };
enum CAMERA_ENUM	{ STATIC_CAMERA, DYNAMIC_CAMERA, CAMERA_END };

// PREFAB에서 Prefab 로딩
// FIELD에서 FIELD 객체들 로딩
// DUNGEON에서 DUNGEON 객체들 로딩
// 각 로딩 씬이 따로 있어야 함.

enum LOADINGID		{ LOADING_DATA, LOADING_FIELD, LOADING_DUNGEON, LOADING_END };
enum RESOURCE_ID	{ RESOURCE_STATIC, RESOURCE_DYNAMIC, RESOURCE_TEXTURE, RESOURCE_END };

enum EQUIP_ENUM		{ ITEM_HEAD, ITEM_SHOULDER, ITEM_CHEST, ITEM_WEAPON, ITEM_FEET, ITEM_END };

enum MOUSE_STATE	{ MOUSE_NORMAL, MOUSE_ATTACK, MOUSE_BUY, MOUSE_LOOT_ALL, MOUSE_STATE_END };

#endif // Enum_h__
