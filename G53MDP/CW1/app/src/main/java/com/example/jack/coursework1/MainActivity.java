package com.example.jack.coursework1;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;


public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void loadBlank(View v){
        Log.d("What to do ", "load a blank image");
        Bundle initBundle = new Bundle();
        initBundle.putInt("Colour", 0xFF000000);
        Intent intent = new Intent(MainActivity.this, DrawBlank.class);
        Log.d("Starting", "Blank Drawer");
        intent.putExtras(initBundle);
        startActivity(intent);
    }
}
