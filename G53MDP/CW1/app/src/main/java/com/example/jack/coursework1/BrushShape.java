package com.example.jack.coursework1;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class BrushShape extends AppCompatActivity {
    static final int ROUND = 0;     // cos it's a circle
    static final int SQUARE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_brush_shape);
    }

    // Relatively simple, two functions that return either a 0 (for a round brush) or a 1 (for a square one)

    protected void returnSquare(View v) {
        Intent shapeIntent = new Intent();
        shapeIntent.putExtra("newShape", SQUARE);
        setResult(Activity.RESULT_OK, shapeIntent);
        finish();
    }

    protected void returnRound(View v) {
        Intent shapeIntent = new Intent();
        shapeIntent.putExtra("newShape", ROUND);
        setResult(Activity.RESULT_OK, shapeIntent);
        finish();
    }
}
