#ifndef __HEADERS_H__
#define __HEADERS_H__

#define NO_EVENT								0
#define DEAD_OBJ								1
#define SCENE_CHANGE							2

#define DEFAULT_PLAYER_SIZE_X					3.f
#define DEFAULT_PLAYER_SIZE_Y					3.f
#define DEFAULT_PLAYER_SPEED					200.f

#define OBJECT_TILE_DOWN_MARGIN					10
#define RENDER_ALL_COLOR						D3DCOLOR_ARGB(255, 255, 255, 255)

#define SWORD_LENGTH							30.f
#define SWORD_SIZE								D3DXVECTOR3(80.f / 40.f, 80.f / 28.f, 0.f)

#define MAKE_ZERO_POINT_THREE_SEC				3.f

#define SHOT_EFFECT_SIZE						D3DXVECTOR3(100.f, 100.f, 0.f)
#define SMOKE_EFFECT_SIZE						D3DXVECTOR3(100.f, 100.f, 0.f)

#define ICE_BULLET_MAKE_EFFECT_SIZE				D3DXVECTOR3(100.f / 31.f, 100.f / 36.f, 0.f)
#define ICE_BULLET_MAKE_ANIMATION				21

#define SPIKE_UP_START_ANIMATION				2

#define SPAER_SPEED								800.f

#define ICE_SPEAR_SIZE							D3DXVECTOR3(30.f, 30.f, 0.f)
#define BANSHEE_BULLET_COUNT					12
#define THIRTY_DEGREE							30.f
#define LENGTH_FROM_BANSHEE						30.f

#define HP_START_POS_X							100.f
#define HP_START_POS_Y							15.f

#define ICE_SPEAR_CREATE_TIME					5.f
#define SET_TARGET_TIME							1.f

#define FULL_HP									1.f

#define MAX_PILLAR_COUNT						4
#define PATTERN_ONE_POSITION					160.f, 200.f, 0.f
#define ICICLE_COUNT							30
#define ICICLE_WIDTH							160.f

#define DEAD_EFFECT_SIZE						D3DXVECTOR3(100.f, 100.f, 0.f)
#define NEXT_ANIMATION_DELAY					0.3f

#define NO_ROTATION								0.f
#define ZERO_POINT_FIVE_SEC						0.5f

#define PLAYER_UI_SIZE_X						150.f
#define PLAYER_UI_SIZE_Y						40.f

#define PLAYER_WIDTH_HALF						20.f
#define PLAYER_HEIGHT_HALF						30.f

#define PLAYER_PIVOT_HEIGHT						0.7f

#define UP_LOOK_VECTOR							D3DXVECTOR3(0.f, -1.f, 0.f)
#define LEFT_LOOK_VECTOR						D3DXVECTOR3(-1.f, 0.f, 0.f)
#define RIGHT_LOOK_VECTOR						D3DXVECTOR3(1.f, 0.f, 0.f)

#define SPEAR_DAMAGE							10.f

#define START_POS_X								1000.f
#define WARNING_MESSAGE_START_POS_X				400.f

#define DASH_TIME								0.2f
#define DASH_REFILL_TIME						1.f

#define WALK_TIME								0.5f

#define SKELETON_SIZE							D3DXVECTOR3(80.f / 32.f, 80.f / 32.f, 0.f)
#define REVERSE									-1.f

#define ATTACK_WIDTH							50.f
#define ATTACK_HEIGHT							50.f

#define MAX_MAPSIZE_X							3400
#define MAX_MAPSIZE_Y							1600

#define TILE_SIZE								40.f

#define INVENTORY_ITEM_SIZE_X					45.f
#define INVENTORY_ITEM_SIZE_Y					45.f

#define MAX_ACC									2.f

#define WINCX									800
#define WINCY									600

#define PURE									= 0
#define TO_HALF									* 0.5f

#define INT_CAST(data)							static_cast<INT>(data)
#define FLOAT_CAST(data)						static_cast<FLOAT>(data)

#define MIN_STR									64
#define MID_STR									128
#define MAX_STR									256

#define KEY_PRESS(key)							(GetAsyncKeyState(key) & 0x8000)

#define NULL_CHECK(ptr)							if(nullptr == (ptr)) return;
#define NULL_CHECK_CONTINUE(ptr)				if(nullptr == (ptr)) continue;
#define NULL_CHECK_RETURN(ptr, val)				if(nullptr == (ptr)) return val;
#define FAILED_CHECK(hr)						if(FAILED(hr)) return;
#define FAILED_CHECK_RETURN(hr, val)			if(FAILED(hr)) return val;

#define NO_COPY(ClassName)							\
private:											\
	ClassName(const ClassName&) = delete;			\
	ClassName& operator=(const ClassName&) = delete;	

#define DECLARE_SINGLETON(ClassName)				\
		NO_COPY(ClassName)							\
public:												\
	static ClassName* GetInstance();				\
	void DestroyInstance();							\
private:											\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)				\
ClassName* ClassName::m_pInstance = nullptr;		\
ClassName* ClassName::GetInstance()					\
{													\
	if(nullptr == m_pInstance)						\
		m_pInstance = new ClassName;				\
	return m_pInstance;								\
}													\
void ClassName::DestroyInstance()					\
{													\
	if(m_pInstance)									\
	{												\
		delete m_pInstance;							\
		m_pInstance = nullptr;						\
	}												\
}
#endif // !__HEADERS_H__
