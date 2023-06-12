package com.example.anto.holterbluetoothinteligente;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.AlarmManager;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.graphics.ColorFilter;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.os.CountDownTimer;
import android.os.Handler;
import android.preference.PreferenceManager;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.common.api.GoogleApiClient;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.charset.Charset;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class inicio2 extends AppCompatActivity {
    BluetoothAdapter btadapter = BluetoothAdapter.getDefaultAdapter();
    SharedPreferences.Editor editor;
    Handler handler = new Handler();
    static BluetoothSocket btsocket;
    static InputStream instream;
    static boolean servicioactivo = false;
    SharedPreferences sharedPreferences;
    public static BluetoothConnection bluetoothConnection;
    private static TextView receivedDataTextView;
    private Spinner colorSpinner;
    private static final Map<String, Integer> colorMap = new HashMap<>();
    static {
        colorMap.put("Rojo", 0);
        colorMap.put("Verde", 1);
        colorMap.put("Azul", 2);
        colorMap.put("Amarillo", 3);
        colorMap.put("Rojo-Verde-Azul-Amarillo", 4);
        colorMap.put("Aleatorio", 5);
    }
    private static final Map<Integer, String> colorHexMap = new HashMap<>();
    static {
        colorHexMap.put(0, "#800000"); // Dark Red
        colorHexMap.put(1, "#004D00"); // Dark Green
        colorHexMap.put(2, "#3366FF"); // Dark Blue
        colorHexMap.put(3, "#BFBF00"); // Dark Yellow
        colorHexMap.put(4, "#800080"); // Dark Magenta
        colorHexMap.put(5, "#404040"); // Dark Gray
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        bluetoothConnection = new BluetoothConnection(getApplicationContext());

        editor = PreferenceManager.getDefaultSharedPreferences(this).edit();
        setContentView(R.layout.activity_inicio2);
        registerReceiver(uiUpdateReceiver, new IntentFilter("com.example.UPDATE_UI_ACTION"));

    }

    private void setButtonTag(int buttonId, int number) {
        Button button = findViewById(buttonId);
        String tag = button.getTag().toString();
        if (tag.length() > 0) {
            tag = tag.substring(0, 1) + number; // Update the number part of the tag
        }
        button.setTag(tag);
    }




    public void conectar(View view) {
        String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45";
        BluetoothDevice device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
        bluetoothConnection.connectToDevice(device);
    }

    public static void updateTextView(String text) {
        if (receivedDataTextView != null) {
            receivedDataTextView.post(() -> receivedDataTextView.setText(text));
        }
    }

    private BroadcastReceiver uiUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction().equals("com.example.UPDATE_UI_ACTION")) {
                int resourceId = intent.getIntExtra("resourceId", 0);
                ColorStateList colorStateList = intent.getParcelableExtra("colorStateList");
                int imageId = intent.getIntExtra("imageId", 0);

                ImageView padImageView = findViewById(resourceId);
                padImageView.setImageDrawable(ContextCompat.getDrawable(context, imageId));
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                    padImageView.setImageTintList(colorStateList);
                }

            }
        }
    };


    @SuppressLint("MissingInflatedId")
    public void onButtonClick(View view) {
        if (view.getTag() != null) {
            String argument = view.getTag().toString();
            Spinner spinnerColor = findViewById(R.id.colorSpinner);
            String selectedColor = spinnerColor.getSelectedItem().toString();

            setContentView(R.layout.fragment_programa);
            TextView program_title = findViewById(R.id.program_title);
            program_title.setText(((Button) view).getText().toString());
            TextView program_color = findViewById(R.id.program_color);
            program_color.setText(selectedColor);
            Button iniciarPausar = findViewById(R.id.iniciarPausar);
            iniciarPausar.setTag(argument);

        }
    }

    public static void sendDataToPairedDevice(String message, Context context) {
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

            OutputStream mmOutStream = bluetoothConnection.btSocket.getOutputStream();
            mmOutStream.write(toSend);
            // Your Data is sent to  BT connected paired device ENJOY.
        } catch (Exception e) {
            Toast.makeText(context, "Fallooo en la comunicación", Toast.LENGTH_SHORT).show();
        }
    }

    public class BluetoothConnection {
        private Context context;
        private BluetoothSocket btSocket;

        public BluetoothConnection(Context context) {
            this.context = context;
        }

        public BluetoothSocket getBtSocket() {
            return btSocket;
        }

        public void connectToDevice(BluetoothDevice device) {

            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

            if (btSocket != null) {
                btSocket = getBtSocket();
            }
            if (btSocket == null || !btSocket.isConnected()) {
                try {
                    if (ActivityCompat.checkSelfPermission(context, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                        // TODO: Request Bluetooth permission if needed
                        return;
                    }
                    if (btSocket == null) {
                        btSocket = device.createRfcommSocketToServiceRecord(uuid);
                    }
                } catch (IOException e) {
                    btSocket = null;
                    return;
                }

                try {
                    if (ActivityCompat.checkSelfPermission(context, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                        // TODO: Request Bluetooth permission if needed
                        return;
                    }

                    btSocket.connect();
                    Log.w("YourTag", "Logging a message");
                } catch (IOException connectException) {
                    int connectionState = btadapter.getProfileConnectionState(BluetoothProfile.A2DP);

                    if (connectionState == BluetoothProfile.STATE_CONNECTED){
                        // Closed connection error occurred
                        Log.e("BluetoothConnection", "Connected to device");
                    } else {
                        // Timeout error occurred
                        Log.e("BluetoothConnection", "Timeout error: ");
                        return;

                    }

                }
            }

            handler.post(() -> {
                Toast.makeText(getApplicationContext(), "Dispositivo conectado", Toast.LENGTH_SHORT).show();

                // Perform any other actions after successful connection
            });
            receivedDataTextView = findViewById(R.id.receivedDataTextView);
            setContentView(R.layout.fragment_selector);

            colorSpinner = findViewById(R.id.colorSpinner);
            Spinner colorSpinner = findViewById(R.id.colorSpinner);
            ArrayAdapter<CharSequence> colorAdapter = ArrayAdapter.createFromResource(getApplicationContext(), R.array.color_options, android.R.layout.simple_spinner_item);
            colorAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            colorSpinner.setAdapter(colorAdapter);
            colorAdapter.notifyDataSetChanged();
            int defaultSelection = 5; // Change this to the desired index of the default value
            colorSpinner.setSelection(defaultSelection);

            colorSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                    String selectedColor = parent.getItemAtPosition(position).toString();
                    int colorCode = colorMap.get(selectedColor);
                    for (int i = 1; i <= 4; i++) {
                        String buttonName = "programa" + i;
                        int buttonId = getResources().getIdentifier(buttonName, "id", getPackageName());
                        setButtonTag(buttonId, colorCode);
                    }
                    parent.setSelection(position); // Ensure the selected item remains visible in the spinner
                    int color = Color.parseColor(colorHexMap.get(colorCode));
                    colorSpinner.setBackgroundColor(color);

                }


                @Override
                public void onNothingSelected(AdapterView<?> parent) {
                    for (int i = 1; i <= 4; i++) {
                        String buttonName = "programa" + i;
                        int buttonId = getResources().getIdentifier(buttonName, "id", getPackageName());
                        setButtonTag(buttonId, 5);
                    }
                }
            });


        }
    }

    private int darkenColor(int color, float darknessFactor) {
        int red = (int) (Color.red(color) * darknessFactor);
        int green = (int) (Color.green(color) * darknessFactor);
        int blue = (int) (Color.blue(color) * darknessFactor);
        return Color.rgb(red, green, blue);
    }

    private boolean isColorDark(int color) {
        double darkness =
                1 - (0.299 * Color.red(color) + 0.587 * Color.green(color) + 0.114 * Color.blue(color)) / 255;
        return darkness >= 0.5; // Adjust the darkness threshold as needed
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        overridePendingTransition(0, 0);
        try {
            bluetoothConnection.btSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onActivityResult(int requestcode, int resultcode, Intent data) {
        super.onActivityResult(requestcode, resultcode, data);

        if (requestcode == 1) {
            if (resultcode == RESULT_OK) {
                Toast.makeText(this, "Bluetooth habilitado", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(this, analisisecg.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
                startActivity(intent);
            } else {
            }
        }
    }

    public void iniciarPausar(View view) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException, IOException {
        Button boton = (Button) findViewById(R.id.iniciarPausar);
        String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45";
        BluetoothDevice device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
        Method m = device.getClass().getMethod("isConnected", (Class[]) null);
        boolean boo = (boolean) m.invoke(device, (Object[]) null);
        if (boton.getText().equals("Pausar")) {
            inicio2.sendDataToPairedDevice("Y", getApplicationContext());
            Toast.makeText(getApplicationContext(), "Se pausó", Toast.LENGTH_SHORT).show();
            boton.setText("Reanudar");
        } else if (boton.getText().equals("Conectar")){
            if (!boo) {
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
                boton.setText("Iniciar");
                inicio2.sendDataToPairedDevice("Y", getApplicationContext());
                startService(new Intent(getApplicationContext(), analisisecg.class));
            }else{
                boton.setText("Iniciar");
            }
        } else if (boton.getText().equals("Iniciar")){
            startService(new Intent(getApplicationContext(), analisisecg.class));
            boton.setText("Pausar");
            String argument = view.getTag().toString();
            inicio2.sendDataToPairedDevice(argument, getApplicationContext());
        } else if (boton.getText().equals("Reanudar")){
            boton.setText("Pausar");
            inicio2.sendDataToPairedDevice("Y", getApplicationContext());
        }
    }

    public void finalizar(View view) {
        Button boton1 = (Button) findViewById(R.id.finalizar);
        Button boton2 = (Button) findViewById(R.id.iniciarPausar);
        String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45";
        BluetoothDevice device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
        if (boton1.getText().equals("Finalizar")) {
            Toast.makeText(getApplicationContext(), "Fin de la secuencia", Toast.LENGTH_SHORT).show();
            boton1.setText("Reiniciar");
            boton2.setVisibility(View.GONE);

            for (int i = 0; i <= 3; i++) {
                int padId = getApplicationContext().getResources().getIdentifier("pad"+i, "id", getPackageName());
                int imageId = getResources().getIdentifier("empty_pad", "drawable", getPackageName());
                ImageView padImageView = findViewById(padId);
                padImageView.setImageDrawable(ContextCompat.getDrawable(getApplicationContext(), imageId));
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                    padImageView.setImageTintList(ColorStateList.valueOf(Color.WHITE));
                }
            }


        } else {
            boton1.setText("Finalizar");
            boton2.setVisibility(View.VISIBLE);
            boton2.setText("Conectar");
        }
        inicio2.sendDataToPairedDevice("p6", getApplicationContext());

    }
}