package com.example.jack.coursework1;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class ColourChange extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_colour_change);
    }

    public void colourBlack(View v) {
        Intent returnIntent = new Intent();
        returnIntent.putExtra("newColour", 0xFFFFFFFF);
        setResult(Activity.RESULT_OK, returnIntent);
        finish();
    }
    public void colourRed(View v) {
        Intent returnIntent = new Intent();
        returnIntent.putExtra("newColour", 0xFFFF0000);
        setResult(Activity.RESULT_OK, returnIntent);
        finish();
    }
    public void colourGreen(View v) {
        Intent returnIntent = new Intent();
        returnIntent.putExtra("newColour", 0xFF00FF00);
        setResult(Activity.RESULT_OK, returnIntent);
        finish();
    }
    public void colourBlue(View v) {
        Intent returnIntent = new Intent();
        returnIntent.putExtra("newColour", 0xFF0000FF);
        setResult(Activity.RESULT_OK, returnIntent);
        finish();
    }
}
