package com.example.jack.coursework1;

import android.app.Activity;
import android.graphics.Paint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.view.View;
import android.util.Log;
import android.widget.RelativeLayout;


public class MainActivity extends AppCompatActivity {

    static final int COLOUR_CHANGE_REQUEST = 1;
    static final int BRUSH_SIZE_SHAPE_REQUEST = 2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        FingerPainterView myFingerPainterView = new FingerPainterView(this);
        RelativeLayout layout = findViewById(R.id.paintingLayout);
        myFingerPainterView.setId(R.id.myFingerPainterViewId);
        myFingerPainterView.setColour(0xFF000000);
        layout.addView(myFingerPainterView);
    }

    public void changeColour(View v) {
        Intent i = new Intent(this, ColourChange.class);
        startActivityForResult(i, COLOUR_CHANGE_REQUEST);
    }

    public void changeSizeAndShape(View v){
        FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
        Intent i = new Intent(this, BrushSizeAndShape.class);
        i.putExtra("oldSize", myFPV.getBrushWidth());
        i.putExtra("oldShape", myFPV.getBrush() == Paint.Cap.ROUND ? 0 : 1);
        startActivityForResult(i, BRUSH_SIZE_SHAPE_REQUEST);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case COLOUR_CHANGE_REQUEST:
                if (resultCode == Activity.RESULT_OK) {
                    FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
                    int newColour = data.getExtras().getInt("newColour");
                    //Log.d("New Colour", Integer.toHexString(newColour));
                    //Log.d("Size", Integer.toString(myFPV.getBrushWidth()));
                    myFPV.setColour(newColour);
                }
                break;
            case BRUSH_SIZE_SHAPE_REQUEST:
                if (resultCode == Activity.RESULT_OK) {
                    FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
                    int newShape = data.getExtras().getInt("newShape");
                    int newSize = data.getExtras().getInt("newSize");
                    myFPV.setBrushWidth(newSize);
                    myFPV.setBrush(newShape == 0 ? Paint.Cap.ROUND : Paint.Cap.SQUARE);
                }
                break;
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        final FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
        outState.putInt("oldColour", myFPV.getColour());
        outState.putInt("oldWidth", myFPV.getBrushWidth());
        outState.putInt("oldShape", myFPV.getBrush() == Paint.Cap.ROUND ? 0 : 1);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedState) {
        final FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
        int oldColour = savedState.getInt("oldColour");
        int oldWidth = savedState.getInt("oldWidth");
        int oldShape = savedState.getInt("oldShape");
        myFPV.setColour(oldColour);
        myFPV.setBrushWidth(oldWidth);
        myFPV.setBrush(oldShape == 0 ? Paint.Cap.ROUND : Paint.Cap.SQUARE);
    }

}