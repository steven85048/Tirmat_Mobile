package com.tirmat.ui.tirmat_android.game_surface.game_element

class BoardConfig {

    companion object {
        // Size of the board
        val BOARD_WIDTH = 5
        val BOARD_HEIGHT = 7

        val MAX_CELL_SIZE = 300
        val MIN_CELL_SIZE = 100

        val MAX_MARGIN_TOP = 50
        val MAX_MARGIN_BOTTOM = 250
        val MARGIN_SIDES = 100

        fun calculateResourceSize( aCanvasWidth : Int, aCanvasHeight : Int ) : Int {

            val dimX = ( aCanvasWidth - 2 * MARGIN_SIDES) / BOARD_WIDTH
            val dimY = ( aCanvasHeight - MAX_MARGIN_TOP) / BOARD_HEIGHT

            return Math.min( dimX, dimY )
        }
    }
}