package com.example.jack.psyje5recipebook;

import android.support.v4.widget.SimpleCursorAdapter;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.database.sqlite.SQLiteDatabase;
import android.database.Cursor;
import android.view.View;
import android.widget.ListView;
import android.content.Intent;
import android.app.Activity;
import android.util.Log;



public class MainActivity extends AppCompatActivity {

    static final int NEW_RECIPE_REQUEST = 1;
    DBHelper dbHelper;
    SQLiteDatabase db;
    SimpleCursorAdapter recAdapter;
    //DBAdapter dbHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        dbHelper = new DBHelper(this, "test", null, 1);
        db = dbHelper.getWritableDatabase();

        Cursor c = db.query("test", new String[] {"_id", "recipetitle", "recipeinstructions"}, null, null, null, null, null );

        String[] columns = new String[] {
                "recipetitle",
                "recipeinstructions",
        };
        int[] to = new int[] {
                R.id.nameView,
                R.id.bodyView,
        };
        recAdapter = new SimpleCursorAdapter(
                this, R.layout.reclistitem,
                c,
                columns,
                to,
                0);
        ListView lv = (ListView) findViewById(R.id.recList);
        lv.setAdapter(recAdapter);
    }

    public void newRecipe(View v) {
        Intent i = new Intent(this, NewRecipe.class);
        startActivityForResult(i, NEW_RECIPE_REQUEST);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch(requestCode) {
            case NEW_RECIPE_REQUEST:
                if (resultCode == Activity.RESULT_OK) {
                    String newName = data.getExtras().getString("newName");
                    String newBody = data.getExtras().getString("newBody");
                    String newQuery = "INSERT INTO test (recipetitle, recipeinstructions) VALUES (\"" + newName + "\", \"" + newBody + "\");";
                    Log.d("newQuery", newQuery);
                    db.execSQL(newQuery);
                }
        }
    }
}
