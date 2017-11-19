package com.example.jack.coursework2_mp3;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.app.PendingIntent;
import android.content.res.Resources;
import android.support.v4.app.NotificationCompat;
import android.app.Notification;
import android.app.NotificationManager;
import android.util.Log;
import android.os.Binder;
public class PlayerService extends Service {

    private final IBinder pBinder = new PlayerBinder();         // Creating a new Binder for an Activity to grab
    final MP3Player servicePlayer = new MP3Player();            // Instantiating an MP3Player

    @Override
    public int onStartCommand (Intent intent, int flags, int startId) { // When we start, we're given an Intent
        String data=(String) intent.getExtras().get("FilePath");        // This will contain a FilePath
        Log.d("PlayerService", data);                              // Let's log it
        servicePlayer.load(data);                                       // Let's also load it into the player
        servicePlayer.play();                                           // And press 'go'
        return Service.START_STICKY;                                    // Start it sticky so the service comes back
    }

    @Override
    public void onCreate() {                                            // When we're created:
        Log.d("PlayerService", "Created");                    // Log this fact
        super.onCreate();                                               // Also create in the usual way
        PendingIntent pi = PendingIntent.getActivity(this, 0, new Intent(this, Player.class), 0);
        Notification n = new NotificationCompat.Builder(this)       // But beyond that, make a notification
                .setTicker(("message"))                                     // allowing us to return to an activity
                .setSmallIcon(android.R.drawable.stat_sys_speakerphone)     // bound to the service
                .setContentTitle("psyje5 Coursework 2")
                .setContentIntent(pi)
                .setAutoCancel(false)
                .build();
        NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        notificationManager.notify(0, n);
    }

    public void playPause() {
        switch(servicePlayer.getState()) {
            case PAUSED: servicePlayer.play(); break;               // If it's paused, play
            case PLAYING: servicePlayer.pause(); break;             // If it's playing, pause
            case STOPPED: servicePlayer.play(); break;              // If it's stopped, play
        };
    }

    public class PlayerBinder extends Binder {
        PlayerService getService() {
            return PlayerService.this;                  // Making a Binder that returns this
        }
    }
    @Override
    public IBinder onBind(Intent intent) {              // When we bind to something, return this Binder
        return pBinder;
    }
}
