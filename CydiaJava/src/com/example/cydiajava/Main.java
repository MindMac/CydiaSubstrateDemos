package com.example.cydiajava;

import java.lang.reflect.Method;
import android.util.Log;
import com.saurik.substrate.MS;
import com.saurik.substrate.MS.ClassLoadHook;

public class Main {
	public static final String TAG = "CydiaSubstrate-Java";
    static void initialize() {
    	ClassLoadHook classLoadHook = new MS.ClassLoadHook() {
			@Override
			public void classLoaded(Class<?> objClass) {
				Method getDeviceId = null;
				try{
					getDeviceId = objClass.getMethod("getDeviceId", new Class<?>[0]);
				}catch(NoSuchMethodException e){
					getDeviceId = null;
				}
				if(getDeviceId != null){
					MS.MethodPointer oldDeviceId = new MS.MethodPointer();
					MS.MethodHook myDeviceId = new MS.MethodHook() {
						@Override
						public Object invoked(Object objClass, Object... args)
								throws Throwable {
							Log.i(TAG, "getDeviceId invoked");
							return "fake-device-id";
						}
					};
					MS.hookMethod(objClass, getDeviceId, myDeviceId, oldDeviceId);
				}
			}
		};
		
		MS.hookClassLoad("android.telephony.TelephonyManager", classLoadHook);
    }
}

