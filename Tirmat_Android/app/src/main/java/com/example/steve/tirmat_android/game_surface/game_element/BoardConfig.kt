package com.example.steve.tirmat_android.game_surface.game_element

class BoardConfig {

    companion object {
        // Every screen has a different number of pixels, so we need to scale
        // for every pixel operation while maintaining the aspect ratio
        val SCALED_WIDTH = 500
        val SCALED_HEIGHT = 1000

        // Size of the board
        val BOARD_WIDTH = 5
        val BOARD_HEIGHT = 7
        val RESOURCE_SIZE = 50
    }
}