package com.example.anto.holterbluetoothinteligente;

import android.Manifest;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.preference.PreferenceManager;

import androidx.core.app.ActivityCompat;
import androidx.core.app.NotificationCompat;
import androidx.core.content.ContextCompat;

import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.ActivityRecognition;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.charset.Charset;
import java.util.UUID;

//TODO


public class analisisecg extends Service
        implements GoogleApiClient.ConnectionCallbacks {

    Handler handler = new Handler();
    BluetoothAdapter btadapter = BluetoothAdapter.getDefaultAdapter();
    static BluetoothSocket btsocket;
    static InputStream instream;
    static boolean servicioactivo = true;
    SharedPreferences sharedPreferences;
    SharedPreferences.Editor editor;
    AlarmManager alarmMgr;
    GoogleApiClient googleApiClient;
    BluetoothDevice device;


    BroadcastReceiver alarmReceiver1 = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {

        PendingIntent alarmIntent3;

        alarmIntent3 = PendingIntent.getBroadcast(getApplicationContext(), 0, new Intent("alarma1"), 0);
        alarmMgr.setExact(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + 60 * 1000, alarmIntent3);
        }
    };


    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    public void onCreate() {
        super.onCreate();

        servicioactivo = true;

        registerReceiver(alarmReceiver1, new IntentFilter("alarma1"));

        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, 0);

        Notification notificacion = new NotificationCompat.Builder(getApplicationContext())
                .setContentTitle("BT Holter")
                .setContentText("Detectando y analizando señal de ECG...")
                .setSmallIcon(R.drawable.ic_stat_name)
                .setColor(ContextCompat.getColor(getApplicationContext(), R.color.colorPrimary))
                .setContentIntent(pendingIntent)
                .build();

        startForeground(1, notificacion);

        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());
        editor = sharedPreferences.edit();

        editor.putBoolean("terminado", false);
        editor.apply();


        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return;
        }

        String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45";
        device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
        Method m = null;
        try {
            m = device.getClass().getMethod("isConnected", (Class[]) null);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
        boolean boo = false;
        try {
            boo = (boolean) m.invoke(device, (Object[]) null);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }

        if(!boo){
            Toast.makeText(getApplicationContext(), "uwu", Toast.LENGTH_SHORT).show();
        }else{


            Toast.makeText(getApplicationContext(), "uwunt", Toast.LENGTH_SHORT).show();
        }

        btsocket = inicio2.bluetoothConnection.getBtSocket();
        Toast.makeText(getApplicationContext(), String.valueOf(btsocket), Toast.LENGTH_SHORT).show();

        new Thread(new recibir(btsocket)).start();
        googleApiClient = new GoogleApiClient.Builder(getApplicationContext())
                .addApi(ActivityRecognition.API)
                .addConnectionCallbacks(this)
                .build();

        googleApiClient.connect();
    }

    @Override
    public void onConnectionSuspended(int cause) {
    }


    @Override
    public void onConnected(Bundle connectionHint) {
        PendingIntent actintent = PendingIntent.getBroadcast(getApplicationContext(), 0, new Intent("activity"), 0);
        ActivityRecognition.ActivityRecognitionApi.requestActivityUpdates(googleApiClient, 0, actintent);
    }



    public void onDestroy() {
        super.onDestroy();
        servicioactivo = false;

        if (instream != null) {
            try {
                instream.close();
            } catch (Exception e) {
            }
            instream = null;
        }

        if (btsocket != null) {
            try {
                btsocket.close();
            } catch (Exception e) {
            }
            btsocket = null;
        }

        unregisterReceiver(alarmReceiver1);

        editor.putBoolean("terminado", true);
        editor.putLong("horafin", System.currentTimeMillis());
        editor.apply();
    }

    class recibir implements Runnable {
        char lectura;
        BluetoothSocket btsocket;
        InputStream instream;


        public recibir(BluetoothSocket socket) {
            btsocket = socket;
            try {
                instream = btsocket.getInputStream();
            } catch (IOException e) {
                instream = null;
            }
        }

        public void run() {
            StringBuilder stringBuilder = new StringBuilder();

            while (servicioactivo) {
                try {
                    byte[] buffer = new byte[30];
                    int bytesRead = instream.read(buffer, 0, 30);

                    if (bytesRead > 0) {
                        for (int i = 0; i < bytesRead; i++) {
                            char c = (char) buffer[i];

                            if (c == '\n') {
                                String receivedLine = stringBuilder.toString();

                                // Process the received line as needed
                                // For example, update UI or perform other operations
                                // You can use a handler or broadcast to communicate with other components

                                // Update UI example:
                                handler.post(new Runnable() {
                                    @Override
                                    public void run() {
                                        // Update UI here with the received line
                                        // For example, update a TextView
                                        Toast.makeText(getApplicationContext(), receivedLine, Toast.LENGTH_SHORT).show();

                                        inicio2.updateTextView(receivedLine);
                                    }
                                });

                                // Broadcast example:
                                Intent dataIntent = new Intent("com.example.bluetooth.DATA_RECEIVED");
                                dataIntent.putExtra("receivedData", receivedLine);
                                sendBroadcast(dataIntent);

                                stringBuilder.setLength(0); // Clear the StringBuilder for the next line
                            } else {
                                stringBuilder.append(c);
                            }
                        }
                    }
                } catch (IOException e) {
                    handler.post(new Runnable() {
                        public void run() {
                            Toast.makeText(getApplicationContext(), "Se perdió la conexión", Toast.LENGTH_SHORT).show();
                        }
                    });
                    break;
                }
            }
        }

    }

}