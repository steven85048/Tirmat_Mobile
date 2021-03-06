package com.tirmat.ui.tirmat_android.game_surface.game_element

import android.graphics.Canvas

interface GameElement {
    fun onDraw( aCanvas : Canvas)
    fun hasCollided( aX : Int, aY : Int ) : Boolean?
}