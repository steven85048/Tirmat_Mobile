package com.example.steve.tirmat_android.game_surface

import android.graphics.Canvas
import com.example.steve.tirmat_android.game_surface.game_element.BoardResource
import com.example.steve.tirmat_android.game_surface.game_element.GameElement

// Holds onto game elements and renders them as necessary
// Also handles game element thread safety - while the canvas
// is being drawn on the game state must NOT change
class GameElementManager {

    private var mGameView : GameView? = null

    private var mTestResource1 : GameElement? = null;
    private var mTestResource2 : GameElement? = null;

    constructor( aGameView : GameView ) {
        mGameView = aGameView

        mTestResource1 = BoardResource(50, 50)
        mTestResource2 = BoardResource( 150, 150)
    }

    // Game elements draw onto the canvas as necessary
    fun onDraw( aCanvas : Canvas ) {
        mTestResource1?.onDraw( aCanvas )
        mTestResource2?.onDraw( aCanvas )
    }

    // Receives updated game state from the engine
    // and modifies game elements
    fun onGameStateUpdate() {

    }
}