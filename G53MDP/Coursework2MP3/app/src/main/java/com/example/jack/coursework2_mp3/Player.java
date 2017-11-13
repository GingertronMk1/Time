package com.example.jack.coursework2_mp3;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;


public class Player extends AppCompatActivity {

    final MP3Player player = new MP3Player();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_player);
        Intent filePath = getIntent();
        String fileToPlay = filePath.getExtras().getString("FilePath");
        player.load(fileToPlay);
    }


    public void playPause(View v) {
        switch(player.getState()) {
            case PAUSED: player.play(); break;
            case PLAYING: player.pause(); break;
        };
    }
}
