package org.quanye.nativehookexample;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XposedBridge;
import de.robv.android.xposed.callbacks.XC_LoadPackage;
import io.michaelrocks.paranoid.Obfuscate;

@Obfuscate
public class HookEntry implements IXposedHookLoadPackage {
    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam lpparam) throws Throwable {
        if (lpparam.packageName.startsWith("com.cozz.hellojni")) {
            System.loadLibrary("native-hook");
            XposedBridge.log("ok");
        }
    }
}
