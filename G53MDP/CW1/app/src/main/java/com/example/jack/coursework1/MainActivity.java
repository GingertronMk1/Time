/*
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
*/

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
    static final int BRUSH_SIZE_REQUEST = 2;
    static final int BRUSH_SHAPE_REQUEST = 3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Bundle infoBundle = getIntent().getExtras();

        FingerPainterView myFingerPainterView = new FingerPainterView(this);
        RelativeLayout layout = (RelativeLayout) findViewById(R.id.paintingLayout);
        myFingerPainterView.setId(R.id.myFingerPainterViewId);
        //int colour = infoBundle.getInt("Colour");
        //Log.d("Colour", Integer.toString(colour));
        myFingerPainterView.setColour(0xFF000000);
        layout.addView(myFingerPainterView);
    }

    public void changeColour(View v) {
        Intent i = new Intent(this, ColourChange.class);
        startActivityForResult(i, COLOUR_CHANGE_REQUEST);
    }

    public void changeSize(View v) {
        Intent i = new Intent(this, BrushSize.class);
        startActivityForResult(i, BRUSH_SIZE_REQUEST);
    }

    public void changeShape(View v) {
        Intent i = new Intent(this, BrushShape.class);
        startActivityForResult(i, BRUSH_SHAPE_REQUEST);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case COLOUR_CHANGE_REQUEST:
                if (resultCode == Activity.RESULT_OK) {
                    FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
                    int newColour = data.getExtras().getInt("newColour");
                    Log.d("New Colour", Integer.toHexString(newColour));
                    Log.d("Size", Integer.toString(myFPV.getBrushWidth()));
                    myFPV.setColour(newColour);
                }
                break;
            case BRUSH_SIZE_REQUEST:
                if (resultCode == Activity.RESULT_OK) {
                    FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
                    int newSize = data.getExtras().getInt("newSize");
                    Log.d("New Size", Integer.toString(newSize));
                    Log.d("Colour", Integer.toHexString(myFPV.getColour()));
                    myFPV.setBrushWidth(newSize);
                }
                break;
            case BRUSH_SHAPE_REQUEST:
                if (resultCode == Activity.RESULT_OK) {
                    FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
                    int newShape = data.getExtras().getInt("newShape");
                    switch (newShape) {
                        case 0:
                            myFPV.setBrush(Paint.Cap.ROUND);
                            break;
                        case 1:
                            myFPV.setBrush(Paint.Cap.SQUARE);
                            break;
                    }
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
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedState) {
        final FingerPainterView myFPV = findViewById(R.id.myFingerPainterViewId);
        int oldColour = savedState.getInt("oldColour");
        int oldWidth = savedState.getInt("oldWidth");
        myFPV.setColour(oldColour);
        myFPV.setBrushWidth(oldWidth);
    }

}