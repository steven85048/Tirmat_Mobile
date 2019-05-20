package com.example.steve.tirmat_android.game_surface.game_element

// Creates the various game elements needed on the game surface
class GameElementFactory {
    companion object {
        fun createTestObject( aX : Int, aY : Int ) : GameElement {
            val newElement : GameElement = BoardResource( aX, aY )
            return newElement
        }
    }
}