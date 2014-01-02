package org.eagle;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.LineNumberReader;

import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;

public class SplashActivity extends Activity {

	private int mDelayTime;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_splash);

		mDelayTime = 5000;
		readDelayTime();
		new Handler().postDelayed(new Runnable() {
			@Override
			public void run() {
				Intent intent;
				if (mDelayTime < 1000) {
					intent = new Intent(SplashActivity.this,
							SuccessActivity.class);
					startActivity(intent);	
				} else {
					intent = new Intent(SplashActivity.this,
							MainActivity.class);
					startActivity(intent);
				}
				finish();
			}
		}, mDelayTime);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.splash, menu);
		return true;
	}

	private void readDelayTime() {
		String sdcard = Environment.getExternalStorageDirectory()
				.getAbsolutePath();

		LineNumberReader lnr = null;
		try {
			FileInputStream fis = new FileInputStream(sdcard
					+ "/test_delay_time.txt");
			InputStreamReader isr = new InputStreamReader(fis);
			lnr = new LineNumberReader(isr);
			String s = null;
			while ((s = lnr.readLine()) != null) {
				mDelayTime = Integer.parseInt(s);
				break;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (null != lnr)
				try {
					lnr.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
	}

}
