#include "bin\Util\kpBindLua.h"
#include "bin\Util\kpMath\kpTransform.h"

using namespace JackFruitEngine;

//kpC++ to LUA API bindings
static int bnd_Create_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = new kpVector3f();
    binder.pushusertype(h,"kpVector3f");
    return 1;
}
static int bnd_Create_V2_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	float x;
	x = binder.checknumber(2);
	float y;
	y = binder.checknumber(3);
	kpVector3f* h = new kpVector3f(x, y);
    binder.pushusertype(h,"kpVector3f");
    return 1;
}
static int bnd_Create_V3_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = new kpVector3f(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4));
    binder.pushusertype(h,"kpVector3f");
    return 1;
}
static int bnd_Destroy_vector3 (lua_State* L)
{
    kpBindLua binder(L);
    kpVector3f* hero = (kpVector3f*) binder.checkusertype(1,"kpVector3f");
    delete hero;
    return 0;
}
static int bnd_max_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->Max());
    return 1;
}
static int bnd_dotProduct_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->dotProduct(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")));
    return 1;
}
static int bnd_crossProduct_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	kpVector3f c = h->crossProduct(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"));
	binder.pushusertype(&c, "kpVector3f");
    return 1;
}
static int bnd_length_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->length());
    return 1;
}
static int bnd_normalize_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->normalize();
    return 0;
}
static int bnd_scalar_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	kpVector3f c = h->scalar(binder.checknumber(2));
	binder.pushusertype(&c, "kpVector3f");
    return 1;
}
static int bnd_lerp_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	kpVector3f c = h->lerp(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), binder.checknumber(3));
	binder.pushusertype(&c, "kpVector3f");
    return 1;
}
static int bnd_change_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->change(*(kpVector3f*)binder.checkusertype(1, "kpVector3f"));
    return 0;
}
static int bnd_change3f_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->change(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4));
    return 0;
}
static int bnd_changeX_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->changeX(binder.checknumber(2));
    return 0;
}
static int bnd_changeY_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->changeY(binder.checknumber(2));
    return 0;
}
static int bnd_changeZ_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->changeZ(binder.checknumber(2));
    return 0;
}
static int bnd_x_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->x);
    return 1;
}
static int bnd_y_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->y);
    return 1;
}
static int bnd_z_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->z);
    return 1;
}
static int bnd_setx_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->x = binder.checknumber(2);
    return 0;
}
static int bnd_sety_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->y = binder.checknumber(2);
    return 0;
}
static int bnd_setz_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->z = binder.checknumber(2);
    return 0;
}
static const luaL_Reg kpVector3flib[] = {
	{"new", bnd_Create_vector3},
	{"newV2", bnd_Create_V2_vector3},
	{"newV3", bnd_Create_V3_vector3},
	{"kill", bnd_Destroy_vector3},
	{"max", bnd_max_vector3},
	{"dotProduct", bnd_dotProduct_vector3},
	{"crossProduct", bnd_crossProduct_vector3},
	{"length", bnd_length_vector3},
	{"normalize", bnd_normalize_vector3},
	{"scalar", bnd_scalar_vector3},
	{"lerp", bnd_lerp_vector3},
	{"change", bnd_change_vector3},
	{"change3f", bnd_change3f_vector3},
	{"changeX", bnd_changeX_vector3},
	{"changeY", bnd_changeY_vector3},
	{"changeZ", bnd_changeZ_vector3},
	{"x", bnd_x_vector3},
	{"y", bnd_y_vector3},
	{"z", bnd_z_vector3},	
	{"setX", bnd_setx_vector3},
	{"setY", bnd_sety_vector3},
	{"setZ", bnd_setz_vector3},
	{NULL, NULL}
};
//
static int bnd_Create_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* h = new kpMatrix4f();
    binder.pushusertype(h,"kpMatrix4f");
    return 1;
}
static int bnd_Destroy_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
    delete hero;
    return 0;
}
static int bnd_transpose_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->transpose(), "kpMatrix4f");
    return 1;
}
static int bnd_tranform_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->transform(*(kpVector3f*) binder.checkusertype(2,"kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_identity_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->identity(), "kpMatrix4f");
    return 1;
}
static int bnd_initTranslation3f_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initTranslation(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4)), "kpMatrix4f");
    return 1;
}
static int bnd_initTranslation_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initTranslation(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRotation3f_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotation(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4)), "kpMatrix4f");
    return 1;
}
static int bnd_initRotation_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotation(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initScale3f_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initScale(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4)), "kpMatrix4f");
    return 1;
}
static int bnd_initScale_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initScale(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_projection_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->projection(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4), binder.checknumber(5), binder.checknumber(6)), "kpMatrix4f");
    return 1;
}
static int bnd_ortho_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->ortho(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4), binder.checknumber(5), binder.checknumber(6), binder.checknumber(7)), "kpMatrix4f");
    return 1;
}
static int bnd_frustum_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->frustum(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4), binder.checknumber(5), binder.checknumber(6), binder.checknumber(7)), "kpMatrix4f");
    return 1;
}
static int bnd_view_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->View(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRot_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRot(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f"), *(kpVector3f*)binder.checkusertype(4, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRotationFromVectors_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotationFromVectors(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f"), *(kpVector3f*)binder.checkusertype(4, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRotationFromDirection_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotationFromDirection(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initPerspective_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initPerspective(binder.checknumber(2), binder.checknumber(3), binder.checknumber(4), binder.checknumber(5)), "kpMatrix4f");
    return 1;
}
static int bnd_mul_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->mul(*(kpMatrix4f*)binder.checkusertype(2, "kpMatrix4f")), "kpMatrix4f");
    return 1;
}
static const luaL_Reg kpMatrix4flib[] = {
	{"new", bnd_Create_matrix4},
	{"kill", bnd_Destroy_matrix4},
	{"transpose", bnd_transpose_matrix4},
	{"transform", bnd_tranform_matrix4},
	{"identity", bnd_identity_matrix4},
	{"initTranslation3f", bnd_initTranslation3f_matrix4},
	{"initTranslation", bnd_initTranslation_matrix4},
	{"initRotation3f", bnd_initRotation3f_matrix4},
	{"initRotation", bnd_initRotation_matrix4},
	{"initScale3f", bnd_initScale3f_matrix4},
	{"initScale", bnd_initScale_matrix4},
	{"initRot", bnd_initRot_matrix4},
	{"initRotationFromVectors", bnd_initRotationFromVectors_matrix4},
	{"initRotationFromDirection", bnd_initRotationFromDirection_matrix4},
	{"initPerspective", bnd_initPerspective_matrix4},
	{"projection", bnd_projection_matrix4},
	{"ortho", bnd_ortho_matrix4},
	{"frustum", bnd_frustum_matrix4},
	{"view", bnd_view_matrix4},
	{"mul", bnd_mul_matrix4},
	{NULL, NULL}
};
//kpQuaternion function bindings
static int bnd_Create_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* h = new kpQuaternion();
    binder.pushusertype(h,"kpQuaternion");
    return 1;
}
static int bnd_Create_4f_quaternion (lua_State* L)
{
    kpBindLua binder(L);
	kpQuaternion* h = new kpQuaternion(binder.checknumber(1), binder.checknumber(2), binder.checknumber(3), binder.checknumber(4));
    binder.pushusertype(h,"kpQuaternion");
    return 1;
}
static int bnd_Create_matrix_quaternion (lua_State* L)
{
    kpBindLua binder(L);
	kpQuaternion* h = new kpQuaternion(*(kpMatrix4f*)binder.checkusertype(1, "kpMatrix4f"));
    binder.pushusertype(h,"kpQuaternion");
    return 1;
}
static int bnd_Destroy_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
    delete hero;
    return 0;
}
static int bnd_length_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->length());
    return 1;
}
static int bnd_normalise_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->normalise(), "kpQuaternion");
    return 1;
}
static int bnd_conjugate_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->conjugate(), "kpQuaternion");
    return 1;
}
static int bnd_mul_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->mul(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion")), "kpQuaternion");
    return 1;
}
static int bnd_mul_vec_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->mul(*(kpVector3f*) binder.checkusertype(2,"kpVector3f")), "kpQuaternion");
    return 1;
}
static int bnd_mul_f_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->mul(binder.checknumber(2)), "kpQuaternion");
    return 1;
}
static int bnd_dot_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->dot(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion")));
    return 1;
}
static int bnd_initRotation_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->initRotation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"), binder.checknumber(3)), "kpQuaternion");
    return 1;
}
static int bnd_toRotationMatrix_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->toRotationMatrix(), "kpMatrix4f");
    return 1;
}
static int bnd_lerp_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->lerp(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion"), binder.checknumber(3)), "kpQuaternion");
    return 1;
}
static int bnd_NLerp_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->NLerp(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion"), binder.checknumber(3), binder.checkbool(4)), "kpQuaternion");
    return 1;
}
static int bnd_getForward_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getForward(), "kpVector3f");
    return 1;
}
static int bnd_getBack_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getBack(), "kpVector3f");
    return 1;
}
static int bnd_getUp_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getUp(), "kpVector3f");
    return 1;
}
static int bnd_getDown_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getDown(), "kpVector3f");
    return 1;
}
static int bnd_getLeft_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getLeft(), "kpVector3f");
    return 1;
}
static int bnd_getRight_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getRight(), "kpVector3f");
    return 1;
}
static int bnd_getX_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getX());
    return 1;
}
static int bnd_getY_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getY());
    return 1;
}
static int bnd_getZ_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getZ());
    return 1;
}
static int bnd_getW_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getW());
    return 1;
}
static const luaL_Reg kpQuaternionlib[] = {
	{"new", bnd_Create_quaternion},
	{"new4f", bnd_Create_4f_quaternion},
	{"newFromMatrix", bnd_Create_matrix_quaternion},
	{"kill", bnd_Destroy_quaternion},
	{"length", bnd_length_quaternion},
	{"normalise", bnd_normalise_quaternion},
	{"conjugate", bnd_conjugate_quaternion},
	{"mul", bnd_mul_quaternion},
	{"mulVec", bnd_mul_vec_quaternion},
	{"mulF", bnd_mul_f_quaternion},
	{"dot", bnd_dot_quaternion},
	{"initRotation", bnd_initRotation_quaternion},
	{"toRotationMatrix", bnd_toRotationMatrix_quaternion},
	{"lerp", bnd_lerp_quaternion},
	{"NLerp", bnd_NLerp_quaternion},
	{"getForward", bnd_getForward_quaternion},
	{"getBack", bnd_getBack_quaternion},
	{"getUp", bnd_getUp_quaternion},
	{"getDown", bnd_getDown_quaternion},
	{"getLeft", bnd_getLeft_quaternion},
	{"getRight", bnd_getRight_quaternion},
	{"getX", bnd_getX_quaternion},
	{"getY", bnd_getY_quaternion},
	{"getZ", bnd_getZ_quaternion},
	{"getW", bnd_getW_quaternion},
	{NULL, NULL}
};
//
static int bnd_Create_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform();
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Create_pos_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform(*(kpVector3f*) binder.checkusertype(1,"kpVector3f"));
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Create_pos_rot_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform(*(kpVector3f*) binder.checkusertype(1,"kpVector3f"), *(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Create_pos_rot_scl_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform(*(kpVector3f*) binder.checkusertype(1,"kpVector3f"), *(kpVector3f*) binder.checkusertype(2,"kpVector3f"), *(kpVector3f*) binder.checkusertype(3,"kpVector3f"));
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Destroy_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
    delete hero;
    return 0;
}
static int bnd_Process_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->Process();
    return 0;
}
static int bnd_setParent_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setParent((kpTransform*) binder.checkusertype(2,"kpTransform"));
    return 0;
}
static int bnd_setTranslation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setTranslation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    return 0;
}
static int bnd_setRotation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setRotation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    return 0;
}
static int bnd_rotate_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->rotate(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion"));
    return 0;
}
static int bnd_setScale_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setScale(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    return 0;
}
static int bnd_getLookAtRotation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getLookAtRotation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"), *(kpVector3f*) binder.checkusertype(3,"kpVector3f")), "kpQuaternion");
    return 1;
}
static int bnd_lookAt_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->lookAt(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"), *(kpVector3f*) binder.checkusertype(3,"kpVector3f"));
    return 0;
}
static int bnd_hasChanged_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushinterger(hero->hasChanged());
    return 1;
}
static int bnd_getTransformation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getTransformation(), "kpMatrix4f");
    return 1;
}
static int bnd_getProjectedTransFormation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getProjectedTransFormation(), "kpMatrix4f");
    return 1;
}
static int bnd_getTransformedRot_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getTransformedRot(),"kpQuaternion");
    return 1;
}
static int bnd_getRot_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getRot(),"kpQuaternion");
    return 1;
}
static int bnd_getOrigin_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getOrigin(), "kpVector3f");
    return 1;
}
static int bnd_getPostion_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getPostion(), "kpVector3f");
    return 1;
}
static int bnd_getRotation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getRotation(), "kpVector3f");
    return 1;
}
static int bnd_getScale_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getScale(), "kpVector3f");
    return 1;
}
static int bnd_getUpVector_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getUpVector(), "kpVector3f");
    return 1;
}
static int bnd_getTransformedPos_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getTransformedPos(), "kpVector3f");
    return 1;
}
static const luaL_Reg kpTransformlib[] = {
	{"new", bnd_Create_transform},
	{"newP", bnd_Create_pos_transform},
	{"newPR", bnd_Create_pos_rot_transform},
	{"newPRS", bnd_Create_pos_rot_scl_transform},
	{"kill", bnd_Destroy_transform},
	{"update", bnd_Process_transform},
	{"setParent", bnd_setParent_transform},
	{"setTranslation", bnd_setTranslation_transform},
	{"setRotation", bnd_setRotation_transform},
	{"rotate", bnd_rotate_transform},
	{"setScale", bnd_setScale_transform},
	{"getLookAtRotation", bnd_getLookAtRotation_transform},
	{"lookAt", bnd_lookAt_transform},
	{"hasChanged", bnd_hasChanged_transform},
	{"getTransformation", bnd_getTransformation_transform},
	{"getProjectedTransFormation", bnd_getProjectedTransFormation_transform},
	{"getTransformedRot", bnd_getTransformedRot_transform},
	{"getRot", bnd_getRot_transform},
	{"getOrigin", bnd_getOrigin_transform},
	{"getPostion", bnd_getPostion_transform},
	{"getRotation", bnd_getRotation_transform},
	{"getScale", bnd_getScale_transform},
	{"getUpVector", bnd_getUpVector_transform},
	{"getTransformedPos", bnd_getTransformedPos_transform},
	{NULL, NULL}
};
//kpGameObject function bindings
int kpVECTOR3FLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpVector3f", "", kpVector3flib, bnd_Destroy_vector3);
	return 1;
}
int kpMATRIX4FLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpMatrix4f", "", kpMatrix4flib, bnd_Destroy_matrix4);
	return 1;
}
int kpQUATERNIONLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpQuaternion", "", kpQuaternionlib, bnd_Destroy_quaternion);
	return 1;
}
int kpTRANSFROMLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpTransform", "", kpTransformlib, bnd_Destroy_transform);
	return 1;
}
//API
int kpAPILIBS(lua_State* l)
{
	
	//Custom classes and functions
	//LUA_INI_LIB(l);	
	kpVECTOR3FLIB(l);
	kpMATRIX4FLIB(l);
	kpQUATERNIONLIB(l);
	kpTRANSFROMLIB(l);
	//kpLOGLIB(l);
	//kpTIMERLIB(l);
	return 0;
}