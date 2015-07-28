#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>
#include <string>

#define LOG_TAG "addon"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

class Player;
class ItemInstance;
class TilePos;
class Vec3;

static bool (*GameMode$useItemOn_real)(Player&, ItemInstance*, TilePos const&, signed char, Vec3 const&);

static bool GameMode$useItemOn_hook(Player& player, ItemInstance* item, TilePos const& tilepos, signed char sc, Vec3 const& vec3) {
	return GameMode$useItemOn_real(player, item, tilepos, sc, vec3);
}


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	LOGI("We will make the coolest mod ever! :-)!");

	void* useItemOn = dlsym(RTLD_DEFAULT, "_ZN8GameMode9useItemOnER6PlayerP12ItemInstanceRK7TilePosaRK4Vec3");	
	MSHookFunction(useItemOn, (void*) &GameMode$useItemOn_hook, (void**) &GameMode$useItemOn_real);	

	return JNI_VERSION_1_2;
}
