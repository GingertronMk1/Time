package com.example.jack.coursework2_mp3;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.io.File;


public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Intent i = new Intent(this, Player.class);


        final ListView lv = (ListView) findViewById(R.id.listView);
        File musicDir = new File(
                Environment.getExternalStorageDirectory().getPath()+ "/Music/");
        Log.d("FilePath", String.valueOf(musicDir));
        File list[] = musicDir.listFiles();

        lv.setAdapter(new ArrayAdapter<File>(this,
                android.R.layout.simple_list_item_1, list));
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> myAdapter,
                                    View myView,
                                    int myItemInt,
                                    long mylng) {
                File selectedFromList =(File) (lv.getItemAtPosition(myItemInt));
                Log.d("g53mdp", selectedFromList.getAbsolutePath());
                // do something with selectedFromList...
                i.putExtra("FilePath", selectedFromList.getAbsolutePath());
                startActivity(i);
            }
        });

    }
}
