package com.example.steve.tirmat_android

import android.app.Activity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_game_level.*

class GameLevelActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_game_level)
    }

    //external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("libengine")
        }
    }
}
