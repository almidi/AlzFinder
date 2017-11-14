package com.example.flogothetispc.alzhaimerfinder;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileOutputStream;
import java.io.IOException;

public class SetupMyDevice extends AppCompatActivity {

   TextView tv;
    Button sendSmsBtn;
    EditText PhoneNumber;
    CheckBox checkbox1;

    private String file = "mydata";
    @Override

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_setup_my_device);

       sendSmsBtn=(Button)findViewById(R.id.button1);
        PhoneNumber=(EditText)findViewById(R.id.editText1);
        checkbox1=(CheckBox)findViewById(R.id.checkBox1);


        sendSmsBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){

                if( checkbox1.isChecked()){
                  String  data=PhoneNumber.getText().toString();
                    try {
                        FileOutputStream fOut = openFileOutput(file,MODE_WORLD_READABLE);
                        fOut.write(data.getBytes());
                        fOut.close();
                        Toast.makeText(getBaseContext(), "file saved", Toast.LENGTH_SHORT).show();
                    }
                    catch (Exception e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                }
            }
        });

    }



}
