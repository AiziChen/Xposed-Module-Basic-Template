package org.quanye.xposed_module_template;

import org.quanye.xposed_module_template.hack.HackMain;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.IXposedHookZygoteInit;
import de.robv.android.xposed.XSharedPreferences;
import de.robv.android.xposed.XposedBridge;
import de.robv.android.xposed.callbacks.XC_LoadPackage;
import io.michaelrocks.paranoid.Obfuscate;

@Obfuscate
public class HackEntry implements IXposedHookLoadPackage, IXposedHookZygoteInit {
    private final static String modulePackageName = HackEntry.class.getPackage().getName();
    private XSharedPreferences sharedPreferences;

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        String appPkgName = "cn.com.weilaihui3";
        if (appPkgName.equals(loadPackageParam.packageName) && appPkgName.equals(loadPackageParam.processName)) {
            XposedBridge.log("We are already in `" + appPkgName + "`!");
            HackMain.hackEntry(loadPackageParam);
        }
    }

    @Override
    public void initZygote(StartupParam startupParam) throws Throwable {
        this.sharedPreferences = new XSharedPreferences(modulePackageName, "default");
//        XposedBridge.log(modulePackageName + " initZygote");
    }
}