package com.example.steve.tirmat_android.game_surface.game_element

import android.graphics.BlurMaskFilter
import android.graphics.Color

// Creates the various game elements needed on the game surface
class GameElementFactory {
    companion object {
        fun createBoardResource( aX : Int, aY : Int, resourceSize : Int ) : GameElement {
            val color : Int = Color.WHITE
            val maskFilter : BlurMaskFilter = BlurMaskFilter( 8f, BlurMaskFilter.Blur.NORMAL )

            val newElement : GameElement = BoardResource( aX, aY, resourceSize, color, maskFilter )
            return newElement
        }
    }
}