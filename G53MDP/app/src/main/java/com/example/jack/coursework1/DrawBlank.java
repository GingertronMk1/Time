package com.example.jack.coursework1;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.util.Log;
import android.widget.RelativeLayout;


public class DrawBlank extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_draw_blank);
        Bundle infoBundle = getIntent().getExtras();

        FingerPainterView myFingerPainterView = new FingerPainterView(this);
        RelativeLayout layout = (RelativeLayout) findViewById(R.id.paintingLayout);
        myFingerPainterView.setId(R.id.myFingerPainterViewId);
        int colour = infoBundle.getInt("Colour");
        Log.d("Colour", Integer.toString(colour));
        myFingerPainterView.setColour(colour);
        layout.addView(myFingerPainterView);
    }

    public void changeColour(View v) {
        Intent i = new Intent(this, ColourChange.class);
        startActivityForResult(i, 1);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == 1) {
            if(resultCode == Activity.RESULT_OK) {
                FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
                int newColour = data.getExtras().getInt("newColour");
                myFPV.setColour(newColour);
            }
        }
    }

//    @Override
//    protected void onSaveInstanceState(Bundle outState) {
//        super.onSaveInstanceState(outState);
//        outState.putInt(this.getColor());
//    }

}
