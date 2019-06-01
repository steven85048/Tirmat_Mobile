package com.tirmat.ui.tirmat_android.game_surface.surface_event

import android.util.Log
import com.tirmat.ui.generated.djinni.GameEngineState
import com.tirmat.ui.generated.djinni.GameStateListenerIntf
import com.tirmat.ui.tirmat_android.game_surface.GameElementManager

class GameStateObserver : GameStateListenerIntf {

    var mGameElementManager : GameElementManager? = null

    constructor( aGameElementManager : GameElementManager ) {
        mGameElementManager = aGameElementManager
    }

    override fun GetState( aState : GameEngineState) {
        var board = aState.board
        for( boardCol in board ) {
            var colString: String = ""

            for (boardCell in boardCol) {
                colString += boardCell.resource.name + " ";
            }

            Log.e("GameStateObserver", colString )
        }
    }
}