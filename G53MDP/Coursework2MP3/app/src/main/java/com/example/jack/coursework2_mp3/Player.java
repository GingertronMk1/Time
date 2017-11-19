package com.example.jack.coursework2_mp3;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.content.ServiceConnection;



public class Player extends AppCompatActivity {

    PlayerService pService;
    boolean pBound = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_player);
    }

    @Override
    protected void onStart() {
        super.onStart();
        Intent intent = new Intent(this, PlayerService.class);
        bindService(intent, pConnection, Context.BIND_AUTO_CREATE);     // On start, Bind to a PlayerService
    }

    @Override
    protected void onStop() {       // On stop, unbind from that service
        super.onStop();
        unbindService(pConnection);
        pBound = false;
    }

    public void playPause(View v) {
        if(pBound) {
            pService.playPause();       // Basically passes play/pause straight through to the method in PlayerService
        }
    }

    private ServiceConnection pConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            PlayerService.PlayerBinder binder = (PlayerService.PlayerBinder) service;   // Creating the connection
            pService = binder.getService();
            pBound = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            pBound = false;
        }
    };
}
