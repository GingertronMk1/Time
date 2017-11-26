package com.example.psyje5.coursework1_fingering;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.util.Log;
import android.widget.EditText;
import android.widget.FrameLayout;

public class Painting extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_painting);
        Bundle infoBundle = getIntent().getExtras();


        FingerPainterView myFingerPainterView = new FingerPainterView(this);
        FrameLayout layout = (FrameLayout) findViewById(R.id.paintingLayout);
        int colour = infoBundle.getInt("Colour");
        Log.d("Colour", Integer.toString(colour));
        myFingerPainterView.setColour(colour);
        layout.addView(myFingerPainterView);
    }

    public void changeColour(View v) {
        Intent colourChangeIntent = new Intent(Painting.this, ColourChange.class);
        startActivity(colourChangeIntent);
    }
}
