//
// Created by coq on 22/12/2023.
//
#include <android/log.h>
#include <string>
#include "hellojni-hook.h"

#define TAG "NativeHookExample-hellojni-hook"

std::string (*bk_info)(const char * msg);
std::string info(const char *msg) {
    bk_info("hello, world");
    __android_log_print(ANDROID_LOG_ERROR, "HelloJni", "hook: %s", msg);
    return "Hello from hook";
}

void hookf_info(HookFunType hook_func, const char *name, void *faddr) {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "%s address: %p", name, faddr);
    hook_func(faddr, (void *) info, (void **) &bk_info);
}