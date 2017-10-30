package com.example.jack.coursework1;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.SeekBar;

public class BrushSize extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_brush_size);
    }

    protected void returnSize(View v) {
        SeekBar mySB = (SeekBar) findViewById(R.id.sizeBar);
        int currentVal = mySB.getProgress();
        Intent sizeIntent = new Intent();
        sizeIntent.putExtra("newSize", currentVal);
        setResult(Activity.RESULT_OK, sizeIntent);
        finish();
    }
}
