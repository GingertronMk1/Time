package com.example.jack.coursework2_mp3;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.content.ServiceConnection;
import android.widget.ProgressBar;



public class Player extends AppCompatActivity {

    PlayerService.PlayerBinder pService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_player);
        ProgressBar pProgressBar = findViewById(R.id.progressBar);
        pProgressBar.setIndeterminate(false);
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
    }

    public void playPause(View v) {
            pService.playPause();       // Basically passes play/pause straight through to the method in PlayerService
    }

    private ServiceConnection pConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            pService = (PlayerService.PlayerBinder) service;   // Creating the connection
            pService.registerCallback(callback);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            pService.unregisterCallback(callback);
            pService = null;
        }
    };

    CallbackInterface callback = new CallbackInterface() {

        @Override
        public void counterEvent(final int counter) {
            runOnUiThread(new Runnable() {
                @Override
                public void run(){
                    ProgressBar pb = findViewById(R.id.progressBar);
                    pb.setProgress(counter);
                }
            });
        }
    };

}
