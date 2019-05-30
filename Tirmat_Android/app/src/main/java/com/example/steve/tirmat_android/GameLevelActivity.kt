package com.example.steve.tirmat_android

import android.app.Activity
import android.os.Bundle
import android.util.Log
import com.example.steve.generated.GameInteractor
import kotlinx.android.synthetic.main.activity_game_level.*

class GameLevelActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        var interactor : GameInteractor = GameInteractor.Create();
        Log.e( "Testing C++", interactor.Test() )

        setContentView(R.layout.activity_game_level)
    }

    companion object {

        // Loads the engine on startup
        init {
            System.loadLibrary("game_engine")
        }
    }
}
