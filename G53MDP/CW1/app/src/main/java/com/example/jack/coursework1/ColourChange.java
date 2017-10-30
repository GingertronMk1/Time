package com.example.jack.coursework1;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;


public class ColourChange extends AppCompatActivity {

    static final int BLACK = 0xFF000000;
    static final int RED = 0xFFFF0000;
    static final int GREEN = 0xFF00FF00;
    static final int BLUE = 0xFF0000FF;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_colour_change);
    }

    // What all these do is pass the relevant colour into the actual returner function described below

    public void colourBlack(View v) { returnColour(BLACK); }
    public void colourRed(View v) { returnColour(RED); }
    public void colourGreen(View v) { returnColour(GREEN); }
    public void colourBlue(View v) { returnColour(BLUE); }

    public void returnColour(int colour) {
        Intent colourIntent = new Intent();
        colourIntent.putExtra("newColour", colour);
        setResult(Activity.RESULT_OK, colourIntent);
        finish();
    }
}
