package com.tirmat.ui.tirmat_android

import android.app.Activity
import android.os.Bundle
import com.tirmat.steve.tirmat_android.R

class GameLevelActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_game_level)
    }

    companion object {
        // Loads the engine on startup
        init {
            System.loadLibrary("engine")
        }
    }
}
