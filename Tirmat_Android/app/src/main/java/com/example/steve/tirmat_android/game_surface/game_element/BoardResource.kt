package com.example.steve.tirmat_android.game_surface.game_element

import android.graphics.Canvas
import android.graphics.Paint
import android.graphics.Rect

class BoardResource : GameElement {

    var elementLocation : Rect? = null

    constructor( aX : Int, aY : Int ) {
        // Testing for now
        elementLocation = Rect( aX, aY, aX + 50, aY + 50 )
    }

    // ==============================================
    // GameElement OVERRIDES
    // ==============================================

    override fun onDraw( aCanvas : Canvas) {
        var paint : Paint = Paint()
        aCanvas.drawRect( elementLocation, paint )
    }

    override fun hasCollided( aX : Int, aY : Int ) {

    }
}