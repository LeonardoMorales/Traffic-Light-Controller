package com.example.trafficlightapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Switch
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import com.example.trafficlightapp.databinding.ActivityMainBinding
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase

class MainActivity : AppCompatActivity() {

    //Data Binding
    private lateinit var binding: ActivityMainBinding

    //Firebase
    private lateinit var database: FirebaseDatabase
    private lateinit var reference: DatabaseReference

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        binding = DataBindingUtil.setContentView(this@MainActivity, R.layout.activity_main)

        database = FirebaseDatabase.getInstance()
        reference = database.getReference("ESP32/Traffic-Light/Value")

        binding.apply {

            redSwitch.text = Status.isOn(false)
            yellowSwitch.text = Status.isOn(false)
            greenSwitch.text = Status.isOn(false)

            redSwitch.setOnCheckedChangeListener { buttonView, isChecked -> if(isChecked) redSwitchChecked() else redSwitchUnchecked() }

            yellowSwitch.setOnCheckedChangeListener { buttonView, isChecked -> if(isChecked) yellowSwitchChecked() else yellowSwitchUnchecked() }

            greenSwitch.setOnCheckedChangeListener { buttonView, isChecked -> if(isChecked) greenSwitchChecked() else greenSwitchUnchecked() }
        }
    }

    private fun redSwitchChecked() {

        binding.apply {
            redSwitch.text = Status.isOn(true)
            yellowSwitch.text = Status.isOn(false)
            greenSwitch.text = Status.isOn(false)

            yellowSwitch.isChecked = false
            greenSwitch.isChecked = false
        }

        uploadFirebaseValue("red")
    }

    private fun redSwitchUnchecked() {
        binding.redSwitch.text = Status.isOn(false)

        reference.setValue("off")
    }

    private fun yellowSwitchChecked() {

        binding.apply {
            redSwitch.text = Status.isOn(false)
            yellowSwitch.text = Status.isOn(true)
            greenSwitch.text = Status.isOn(false)

            redSwitch.isChecked = false
            greenSwitch.isChecked = false
        }

        uploadFirebaseValue("yellow")
    }

    private fun yellowSwitchUnchecked() {
        binding.yellowSwitch.text = Status.isOn(false)

        reference.setValue("off")
    }

    private fun greenSwitchChecked() {

        binding.apply {
            redSwitch.text = Status.isOn(false)
            yellowSwitch.text = Status.isOn(false)
            greenSwitch.text = Status.isOn(true)

            redSwitch.isChecked = false
            yellowSwitch.isChecked = false
        }

        uploadFirebaseValue("green")
    }

    private fun greenSwitchUnchecked() {
        binding.greenSwitch.text = Status.isOn(false)

        reference.setValue("off")
    }


    private fun uploadFirebaseValue(color: String) {
        reference.setValue(color)
    }
}
