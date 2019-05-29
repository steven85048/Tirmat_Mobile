package com.example.steve.tirmat_android.game_surface.game_element

import android.graphics.Canvas

// Holds the cells on the game board and groups up
// the draw and update operations
class GameBoard {
    var mGameBoard : MutableList< MutableList< GameElement > >? = null;

    constructor() {}

    // Allocate memory for the game board
    private fun initmGameBoard( aCanvasWidth : Int, aCanvasHeight : Int ) {
        mGameBoard = ArrayList< MutableList< GameElement > >()

        for( indexX in 0 until BoardConfig.BOARD_WIDTH ) {
            var currList : MutableList< GameElement > = ArrayList< GameElement >()

            for( indexY in 0 until BoardConfig.BOARD_HEIGHT ) {

                var newElement : GameElement = GameElementFactory.createBoardResource( indexX, indexY, BoardConfig.calculateResourceSize( aCanvasWidth, aCanvasHeight ) )
                currList?.add( newElement )
            }

            mGameBoard?.add( currList )
        }
    }

    fun onDraw( aCanvas : Canvas) {
        if( mGameBoard == null ) {
            initmGameBoard( aCanvas.width, aCanvas.height )
        }

        mGameBoard?.let {
            for (resourceList in it) {
                for (resource in resourceList) {
                    resource.onDraw( aCanvas )
                }
            }
        }
    }

    fun getCollidedElement( aX : Int, aY : Int ) : GameElement? {
        mGameBoard?.let {
            for (resourceList in it) {
                for (resource in resourceList) {
                    var hasCollided = resource.hasCollided( aX, aY )

                    hasCollided?.let {
                        if( it ) {
                            return resource
                        }
                    }
                }
            }
        }

        return null
    }

    fun onGameStateUpdate() {

    }

}