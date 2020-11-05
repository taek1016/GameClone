#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	// ID_DYNAMIC : 실시간 업데이트가 필요한 컴포넌트
	enum COMPONENTID	{ ID_DYNAMIC, ID_STATIC, ID_END };

	enum WINMODE		{ MODE_FULL, MODE_WIN };

	enum INFO			{ INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION		{ ROT_X, ROT_Y, ROT_Z, ROT_END };

	enum BUFFERID		{ BUFFER_TRICOL, BUFFER_RCCOL, BUFFER_RCTEX, BUFFER_TERRAINTEX, BUFFER_CUBETEX };
	enum TEXTURETYPE	{ TEX_NORMAL, TEX_CUBE, TEX_END };

	enum RENDERID		{ RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };

	enum COLLTYPE		{ COL_FALSE, COL_TRUE, COL_END };
	enum MESHTYPE		{ TYPE_STATIC, TYPE_DYNAMIC, TYPE_NAVI };

	enum MOUSEKEYSTATE	{ DIM_LB, DIM_RB, DIM_MB, DIM_END };

	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum COMPONENT_TYPE { BUFFER, CAMERA, CONTROLLER, RIGIDBODY, ANIMATOR, TRANSFORM, BODY, TEXTURE, TERRAIN, COLLIDER, PARTICLE, COMP_TYPE_END };

	enum COLLIDER_TYPE	{ COLLISION_CUBE, COLLISION_SPHERE, COLLISION_END };

	enum COLLISION		{ COLL_BODY, COLL_ATTACK, COLL_END };

	enum OBJ_STATUS		{ STATUS_IDLE_NORMAL, STATUS_IDLE_WITH_ITEM, STATUS_MOVE, STATUS_ATTACK, STATUS_DIE, STATUS_END };

	enum ANIMTRANSFORM	{ TRANS_POS, TRANS_ROT, TRANS_SCALE, TRANS_END };

	enum ANIMSTATE		{ ANIM_NONE, ANIM_GUN, ANIM_SAW, ANIM_END };

	enum IS_MONSTER		{ OBJ_NOT, OBJ_MONSTER, OBJ_END};
}

#endif // Engine_Enum_h__
