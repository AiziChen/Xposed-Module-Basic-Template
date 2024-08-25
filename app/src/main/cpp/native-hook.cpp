#include <android/log.h>
#include <jni.h>
#include <string>
#include <string_view>
#include <dlfcn.h>
#include "native-hook.h"
#include "hellojni-hook.h"

#define TAG "NativeHookExample"
static HookFunType hook_func = nullptr;

static void on_library_loaded(const char *name, void *handle) {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Library %s loaded at %p", name, handle);
    if (std::string(name).ends_with("libapp.so")) {
        void *faddr = dlsym(handle, "_Z4infoPKc");
        hookf_info(hook_func, name, faddr);
    }
}

extern "C" [[gnu::visibility("default")]] [[gnu::used]]
jint JNI_OnLoad(JavaVM *jvm, void *) {
    JNIEnv *env = nullptr;
    jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "JNI_OnLoad");
    return JNI_VERSION_1_6;
}

extern "C" [[gnu::visibility("default")]] [[gnu::used]]
NativeOnModuleLoaded native_init(const NativeAPIEntries *entries) {
    hook_func = entries->hook_func;
    __android_log_print(ANDROID_LOG_DEBUG, TAG,
                        "LSP native hook library loaded, API v%d, hook function %p",
                        entries->version, hook_func);
    return on_library_loaded;
}