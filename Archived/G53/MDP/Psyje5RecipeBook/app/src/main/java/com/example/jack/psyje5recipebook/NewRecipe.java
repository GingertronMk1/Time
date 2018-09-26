package com.example.jack.psyje5recipebook;

import android.support.v7.app.AppCompatActivity;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.util.Log;
import android.content.Intent;


public class NewRecipe extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_new_recipe);
    }

    public void saveRecipe(View v) {
        Intent i = new Intent();
        EditText nameV = (EditText) findViewById(R.id.recName);
        EditText bodyV = (EditText) findViewById(R.id.recBody);
        String newName = nameV.getText().toString();
        String newBody = bodyV.getText().toString();
        Log.d("New name", newName);
        Log.d("New body", newBody);
        i.putExtra("newName", newName);
        i.putExtra("newBody", newBody);
        setResult(Activity.RESULT_OK, i);
        finish();
    }
    public void cancelRecipe(View v) {
        setResult(Activity.RESULT_CANCELED, new Intent());
        finish();
    }
}
