package com.example.jack.psyje5recipebook;

/**
 * Created by Jack on 04/12/2017.
 */

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

public class RecProvider extends ContentProvider {

    private DBHelper dbHelper = null;
/*
    private static final UriMatcher uriMatcher;
    static {
        uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
        uriMatcher.addURI(RecProviderContract.AUTHORITY, "recipes", 1);
        uriMatcher.addURI(RecProviderContract.AUTHORITY, "recipes/#", 2);
        uriMatcher.addURI(RecProviderContract.AUTHORITY, "*", 3);
    }
*/
    @Override
    public boolean onCreate() {
        this.dbHelper = new DBHelper(this.getContext(), "test", null, 1);
        return true;
    }

    @Nullable
    @Override
    public Cursor query(@NonNull Uri uri, @Nullable String[] strings, @Nullable String s, @Nullable String[] strings1, @Nullable String s1) {
        return null;
    }

    @Nullable
    @Override
    public String getType(@NonNull Uri uri) {
        if (uri.getLastPathSegment()==null) {
            return "vnd.android.cursor.dir/RecProvider.data.text";
        } else {
            return "vnd.android.cursor.item/RecProvider.data.text";
        }
    }

    @Nullable
    @Override
    public Uri insert(@NonNull Uri uri, @Nullable ContentValues contentValues) {
        return null;
    }

    @Override
    public int delete(@NonNull Uri uri, @Nullable String s, @Nullable String[] strings) {
        return 0;
    }

    @Override
    public int update(@NonNull Uri uri, @Nullable ContentValues contentValues, @Nullable String s, @Nullable String[] strings) {
        return 0;
    }
}
