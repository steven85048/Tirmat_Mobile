package com.example.steve.tirmat_android.game_surface.game_element

import android.graphics.Canvas

// Holds the cells on the game board and groups up
// the draw and update operations
class GameBoard {
    var gameBoard : MutableList< MutableList< GameElement > >? = null;

    constructor() {
        // Initialize our board with empty cells for now
        // will be based on the game state later
        initGameBoard()
    }

    // Allocate memory for the game board
    private fun initGameBoard() {
        gameBoard = ArrayList< MutableList< GameElement > >()

        for( indexX in 0 until BoardConfig.BOARD_WIDTH ) {
            var currList : MutableList< GameElement > = ArrayList< GameElement >()

            for( indexY in 0 until BoardConfig.BOARD_HEIGHT ) {
                var newElement : GameElement = GameElementFactory.createBoardResource( indexX * BoardConfig.RESOURCE_SIZE, indexY * BoardConfig.RESOURCE_SIZE, BoardConfig.RESOURCE_SIZE )
                currList?.add( newElement )
            }

            gameBoard?.add( currList )
        }
    }

    fun onDraw( aCanvas : Canvas) {
        gameBoard?.let {
            for (resourceList in it) {
                for (resource in resourceList) {
                    resource.onDraw( aCanvas )
                }
            }
        }
    }

    fun onGameStateUpdate() {

    }

}