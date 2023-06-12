package com.example.anto.holterbluetoothinteligente;

import android.Manifest;
import android.app.Activity;
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
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.preference.PreferenceManager;

import androidx.core.app.ActivityCompat;
import androidx.core.app.NotificationCompat;
import androidx.core.content.ContextCompat;

import android.util.Log;
import android.widget.ImageView;
import android.widget.Toast;

import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.ActivityRecognition;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class analisisecg extends Service implements GoogleApiClient.ConnectionCallbacks {

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

        if (!boo) {
            Toast.makeText(getApplicationContext(), "uwu", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(getApplicationContext(), "uwunt", Toast.LENGTH_SHORT).show();
        }

        btsocket = inicio2.bluetoothConnection.getBtSocket();

        new Thread(new recibir(btsocket, getApplicationContext())).start();
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
    }

    class recibir implements Runnable {
        BluetoothSocket btsocket;
        InputStream instream;
        private Map<Integer, Integer> colorMap;
        private Map<Character, String> symbolMap;
        private Context context;

        public recibir(BluetoothSocket socket, Context context) {
            btsocket = socket;
            this.context = context;
            try {
                instream = btsocket.getInputStream();
            } catch (IOException e) {
                instream = null;
            }
            initializeColorMap();
            initializeSymbolMap();
        }

        private void initializeColorMap() {
            colorMap = new HashMap<>();
            colorMap.put(0, Color.RED);     // Color.RED
            colorMap.put(1, Color.GREEN);  // Color.GREEN
            colorMap.put(2, Color.CYAN);  // Color.BLUE
            colorMap.put(3, Color.YELLOW);  // Color.YELLOW
            colorMap.put(6, Color.WHITE);  // Color.YELLOW
        }

        private void initializeSymbolMap() {
            symbolMap = new HashMap<>();
            symbolMap.put('a', "flecha_arriba");
            symbolMap.put('b', "flecha_abajo");
            symbolMap.put('c', "flecha_izquierda");
            symbolMap.put('d', "flecha_derecha");
            symbolMap.put('e', "uno");
            symbolMap.put('f', "dos");
            symbolMap.put('g', "tres");
            symbolMap.put('h', "cuatro");
            symbolMap.put('i', "cinco");
            symbolMap.put('j', "seis");
            symbolMap.put('k', "siete");
            symbolMap.put('l', "ocho");
            symbolMap.put('m', "nueve");
            symbolMap.put('n', "cero");
            symbolMap.put('o', "circulo");
            symbolMap.put('p', "empty_pad");

        }

        public void run() {
            StringBuilder stringBuilder = new StringBuilder();
            boolean isFirstLineReceived = false;
            boolean isSecondLineReceived = false;
            Log.d("AnalisisECG", "a");

            while (servicioactivo) {
                try {
                    ColorStateList colorStateList = null;
                    byte[] data = new byte[30];
                    int bytesRead = instream.read(data, 0, 30);
                    byte[] buffer = Arrays.copyOf(data, bytesRead);
                    String dataString = new String(buffer, 0, bytesRead).trim();

                    if (dataString.length() == 1 && Character.isDigit(dataString.charAt(0))) {
                        stringBuilder.append(dataString);
                        isFirstLineReceived = true;
                    } else if (dataString.length() == 2 && Character.isLetter(dataString.charAt(0)) && Character.isDigit(dataString.charAt(1))) {
                        stringBuilder.append(dataString);
                        isSecondLineReceived = true;
                    }

                    if (isFirstLineReceived && isSecondLineReceived) {
                        String combinedData = stringBuilder.toString();

                        int padNumber = Character.getNumericValue(combinedData.charAt(0));
                        char symbol = combinedData.charAt(1);
                        int color = Character.getNumericValue(combinedData.charAt(2));

                        String padName = "pad" + padNumber;
                        int padId = getApplicationContext().getResources().getIdentifier(padName, "id", getPackageName());

                        String symbolName = symbolMap.get(symbol);

                        int imageId = -1;
                        int colorValue = -1;

                        if (symbol >= 'a' && symbol <= 'p') {
                            imageId = getResources().getIdentifier(symbolName, "drawable", getPackageName());
                        }
                        if(color <= 3 || color == 6){
                            colorValue = colorMap.get(color);
                            colorStateList = ColorStateList.valueOf(colorValue);
                        }

                        if ((colorValue != -1) && (imageId != -1) && (padName != null)) {
                            Log.d("AnalisisECG", "Received packet:");
                            Log.d("AnalisisECG", "Pad ID: " + padId);
                            Log.d("AnalisisECG", "symbolname: " + symbolName);
                            Log.d("AnalisisECG", "Color: " + color);
                            updatePAD(padId, colorStateList, imageId);
                        }


                        // Reset flags and StringBuilder for the next iteration
                        isFirstLineReceived = false;
                        isSecondLineReceived = false;
                        stringBuilder.setLength(0);

                    } else {
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

    public void updatePAD(final int resourceId, final ColorStateList colorStateList, final int imageId) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                // Broadcast an intent to the Activity to update the UI
                Intent intent = new Intent("com.example.UPDATE_UI_ACTION");
                intent.putExtra("resourceId", resourceId);
                intent.putExtra("colorStateList", colorStateList);
                intent.putExtra("imageId", imageId);
                sendBroadcast(intent);
            }
        });
    }
}
