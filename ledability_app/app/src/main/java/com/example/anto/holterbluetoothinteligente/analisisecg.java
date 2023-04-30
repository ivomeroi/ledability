package com.example.anto.holterbluetoothinteligente;

import android.Manifest;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothHeadset;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.IntentSender;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.database.DatabaseErrorHandler;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.drawable.Drawable;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.UserHandle;
import android.preference.PreferenceManager;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.ActivityCompat;
import androidx.core.app.NotificationCompat;
import androidx.core.content.ContextCompat;

import android.telephony.SmsManager;
import android.view.Display;
import android.widget.Toast;

import com.creativityapps.gmailbackgroundlibrary.BackgroundMail;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.ActivityRecognition;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import java.util.UUID;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
//TODO
import java.util.stream.Collectors;

public class analisisecg extends Service
        implements GoogleApiClient.ConnectionCallbacks {

    Handler handler = new Handler();
    BluetoothAdapter btadapter = BluetoothAdapter.getDefaultAdapter();
    static BluetoothSocket btsocket;
    static InputStream instream;
    static boolean servicioactivo = false;
    SharedPreferences sharedPreferences;
    SharedPreferences.Editor editor;
    AlarmManager alarmMgr;
    GoogleApiClient googleApiClient;

    public analisisecg() {
    }


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
        BluetoothDevice device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
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
            new Thread(new conectar(device)).start();
        }
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

    public class conectar implements Runnable {
        public conectar(BluetoothDevice device) {
            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

            try {
                if (ActivityCompat.checkSelfPermission(analisisecg.this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return;
                }
                if (btsocket == null)
                    btsocket = device.createRfcommSocketToServiceRecord(uuid);
            } catch (IOException e) {
                btsocket = null;

            }
        }


        public void run() {
            try {
                if (ActivityCompat.checkSelfPermission(analisisecg.this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return;
                }
                btsocket.connect();
            } catch (IOException connectException) {
//                try {
//                    handler.post(() -> Toast.makeText(getApplicationContext(), "Falló la conexión", Toast.LENGTH_SHORT).show());
//
//                    btsocket.close();
//                } catch (IOException closeException) {
//                }

                return;
            }

            handler.post(() -> {
                Toast.makeText(getApplicationContext(), "Dispositivo conectado", Toast.LENGTH_SHORT).show();

                if (sharedPreferences.getBoolean("mostrarinicio", true)) {
                    Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                    intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
                    startActivity(intent);
                    editor.putBoolean("mostrarinicio", false);
                    editor.apply();
                }
            });
            String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45";
            BluetoothDevice device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
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
            if(boo){
                new Thread(new recibir()).start();
            }

        }


    }


    class recibir implements Runnable {
        int lectura;

        public recibir() {
            try {
                instream = btsocket.getInputStream();
            } catch (IOException e) {
                instream = null;
            }
        }

        public void run() {
            while (servicioactivo) {

                try {
                    lectura = instream.read();
                }


                catch (IOException e) {
                    handler.post(new Runnable() {
                        public void run() {
                            Toast.makeText(getApplicationContext(), "Se perdió la conexión", Toast.LENGTH_SHORT).show();
                        }
                    });
                }
            }
        }
    }


    public static void sendDataToPairedDevice(String message, BluetoothDevice device, Context context) {
        byte[] toSend = message.getBytes(Charset.defaultCharset());
        try {
            UUID applicationUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
            if (ActivityCompat.checkSelfPermission(context, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }

            OutputStream mmOutStream = btsocket.getOutputStream();
            mmOutStream.write(toSend);
            // Your Data is sent to  BT connected paired device ENJOY.
        } catch (Exception e) {
            Toast.makeText(context, "Fallo en la comunicación", Toast.LENGTH_SHORT).show();
        }
    }
}