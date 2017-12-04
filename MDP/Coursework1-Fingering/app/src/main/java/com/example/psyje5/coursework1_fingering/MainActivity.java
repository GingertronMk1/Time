package com.example.psyje5.coursework1_fingering;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.util.Log;
import android.widget.EditText;
import android.widget.FrameLayout;

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
        Intent intent = new Intent(MainActivity.this, Painting.class);
        intent.putExtras(initBundle);
        startActivity(intent);
    }

    public void loadImage(View v){
        Log.d("What to do ", "load an image from Downloads");
        //activity_main.addView(myFingerPainterView);
    }
}
