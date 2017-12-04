package com.example.jack.coursework1;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class BrushSizeAndShape extends AppCompatActivity {
    static final int ROUND = 0;
    static final int SQUARE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_brush_size_and_shape);

        // Populating the options with what is currently selected
        Intent oldValues = getIntent();
        // Get the current size and shape of the brush
        int oldShape = oldValues.getExtras().getInt("oldShape");
        int oldSize = oldValues.getExtras().getInt("oldSize");

        // Auto-enter the current size of the brush
        EditText et = findViewById(R.id.sizePicker);
        et.setText(String.valueOf(oldSize), TextView.BufferType.EDITABLE);
        // And auto-select the appropriate radio button
        RadioButton b = findViewById(oldShape == ROUND ? R.id.btnRound : R.id.btnSquare);
        b.setChecked(true);
    }

    public void returnVals(View v) {
        Intent oldValues = getIntent();
        int oldSize = oldValues.getExtras().getInt("OldSize");

        // Getting the two input areas
        RadioGroup rg = findViewById(R.id.roundSquareGroup);
        EditText et = findViewById(R.id.sizePicker);


        // With some fiddling in MainActivity, we can just use the index within the group
        // of the selected radio button. As one is pre-selected, no need to check that
        // one and only one is selected.
        int radioButtonID = rg.getCheckedRadioButtonId();
        View radioButton = rg.findViewById(radioButtonID);
        int roundOrSquare = rg.indexOfChild(radioButton);

        // Size is a bit more complex, as the user can delete what's entered
        // So we check if the editText is empty, and if it is we reuse the original value
        // Otherwise we use the entered value
        // We don't need to type-check as the user can only use the number pad for this
        int newSize;
        if(et.getText().toString().trim().length() != 0) {
            newSize = Integer.parseInt(et.getText().toString());
        } else {
            newSize = oldSize;
        }

        // Finally we wrap this all into a nice Intent and pass it back to MainActivity
        Intent newSizeShape = new Intent();
        newSizeShape.putExtra("newShape", roundOrSquare);
        newSizeShape.putExtra("newSize", newSize);
        setResult(Activity.RESULT_OK, newSizeShape);
        finish();
    }
}
