package com.example.steve.tirmat_android.game_surface

import android.graphics.Canvas
import com.example.steve.tirmat_android.game_surface.game_element.GameBoard
import com.example.steve.tirmat_android.game_surface.game_element.GameElement
import com.example.steve.tirmat_android.game_surface.game_element.GameElementFactory

// Holds onto game elements and renders them as necessary
// Also handles game element thread safety - while the canvas
// is being drawn on the game state must NOT change
class GameElementManager {

    private var mGameView : GameView? = null
    private var mGameBoard : GameBoard? = null

    constructor( aGameView : GameView ) {
        mGameView = aGameView
        mGameBoard = GameBoard()
    }

    // Game elements draw onto the canvas as necessary
    fun onDraw( aCanvas : Canvas ) {
        mGameBoard?.onDraw( aCanvas )
    }

    fun getCollidedElement( aX : Int, aY : Int ) : GameElement? {
        // just return the board's element for now
        var theCollidedElement = mGameBoard?.getCollidedElement( aX, aY )
        return theCollidedElement
    }

    // Receives updated game state from the engine
    // and modifies game elements
    fun onGameStateUpdate() {

    }
}