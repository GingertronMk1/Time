package com.example.jack.psyje5recipebook;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;

public class DBHelper extends SQLiteOpenHelper {

    public DBHelper (Context context, String name, CursorFactory factory, int version) {

        super(context, name, factory, version);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table test (_id INTEGER PRIMARY KEY AUTOINCREMENT, recipetitle TEXT, recipeinstructions TEXT);");
        db.execSQL("INSERT INTO test (recipetitle, recipeinstructions) VALUES (\"test\", \"This is a test recipe\");");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int i, int i1) {
        db.execSQL("DROP TABLE IF EXISTS test");
        onCreate(db);
    }
}