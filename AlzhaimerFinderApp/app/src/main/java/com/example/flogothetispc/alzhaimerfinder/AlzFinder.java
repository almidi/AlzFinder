package com.example.flogothetispc.alzhaimerfinder;

import android.app.PendingIntent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.telephony.SmsManager;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;
import android.Manifest;
import android.content.pm.PackageManager;

import android.app.Activity;

import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.telephony.SmsManager;

import android.util.Log;
import android.view.Menu;
import android.view.View;

import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.FileInputStream;


public class AlzFinder extends AppCompatActivity {
    private String file = "mydata";
    private static  final int PERMISSION_REQUEST_CODE = 1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alz_finder);
    }

    public void SentSms(View v) {

            try {
                FileInputStream fin = openFileInput(file);
                int c;
                String temp="";
                while( (c = fin.read()) != -1){
                    temp = temp + Character.toString((char)c);
                }

                try {


                    if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {

                        if (checkSelfPermission(Manifest.permission.SEND_SMS)
                                == PackageManager.PERMISSION_DENIED) {

                            Log.d("permission", "permission denied to SEND_SMS - requesting it");
                            String[] permissions = {Manifest.permission.SEND_SMS};

                            requestPermissions(permissions, PERMISSION_REQUEST_CODE);

                        }
                    }
                    Toast.makeText(getBaseContext(),temp,Toast.LENGTH_SHORT).show();
                    SmsManager sms = SmsManager.getDefault();
                    PendingIntent sentPI;
                    String SENT = "SMS_SENT";

                    sentPI = PendingIntent.getBroadcast(this, 0,new Intent(SENT), 0);

                    sms.sendTextMessage(temp, null, "@", sentPI, null);
                   Toast.makeText(getApplicationContext(), "SMS Sent Successfully!",
                            Toast.LENGTH_LONG).show();
                } catch (Exception e) {
                    Toast.makeText(getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
                    e.printStackTrace();

                            }


            }
            catch(Exception e){
            }




    }

    public void Setup(View v) {
        Intent intent = new Intent(AlzFinder.this, SetupMyDevice.class);
        startActivity(intent);
    }

}
