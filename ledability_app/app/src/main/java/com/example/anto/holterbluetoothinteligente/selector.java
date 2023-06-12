package com.example.anto.holterbluetoothinteligente;


import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.navigation.NavigationView;

import java.util.HashMap;
import java.util.Map;

public class selector extends Fragment {
    SharedPreferences sharedPreferences;
    SharedPreferences.Editor editor;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        editor = PreferenceManager.getDefaultSharedPreferences(getContext()).edit();

        View v = inflater.inflate(R.layout.fragment_selector, container, false);

        Spinner colorSpinner = v.findViewById(R.id.colorSpinner);
        ArrayAdapter<CharSequence> colorAdapter = ArrayAdapter.createFromResource(requireContext(), R.array.color_options, android.R.layout.simple_spinner_item);
        colorAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        colorSpinner.setAdapter(colorAdapter);
        colorAdapter.notifyDataSetChanged();
        int defaultSelection = 5; // Change this to the desired index of the default value
        colorSpinner.setSelection(defaultSelection);


        return v;
    }

    @Override
    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
    }

    private void setButtonTag(int buttonId, int number) {
        Button button = getView().findViewById(buttonId);
        String tag = button.getTag().toString();
        if (tag.length() > 0) {
            char firstChar = tag.charAt(0);
            tag = String.valueOf(firstChar) + number;
            button.setTag(tag);
        }
    }

    @Override
    public void onDestroyView(){
        super.onDestroyView();
    }


}