package engine.games.luisg.engine;

import android.app.Activity;
import android.app.NativeActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
//import com.google.android.gms.ads.*;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.AdSize;
//import com.google.android.gms.ads.identifier.AdvertisingIdClient;

/**
 * Created by blubs on 7/19/2016.
 */

public class Launcher extends NativeActivity
{
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		loge("JNI: on create started");
		super.onCreate(savedInstanceState);

		Context context = this.getApplication().getApplicationContext();

		Intent openAdActivity = new Intent(this,AdActivity.class);
		startActivity(openAdActivity);

		loge("JNI: on create finished");
	}

	public void loge(String msg)
	{

		Log.println(Log.ERROR,"jni",msg);
	}
	public void logi(String msg)
	{

		Log.println(Log.INFO,"jni",msg);
	}

	public boolean test(int a, int b)
	{
		loge("test method called with parameters: (" + a + "," + b + ")");
		return (a==b);
	}
}
