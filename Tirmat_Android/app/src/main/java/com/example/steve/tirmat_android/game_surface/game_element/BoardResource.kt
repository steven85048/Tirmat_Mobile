package com.example.steve.tirmat_android.game_surface.game_element

import android.graphics.*

class BoardResource : GameElement {

    var topX : Int? = null
    var topY : Int? = null

    var previousCanvasWidth : Double? = null
    var previousCanvasHeight : Double? = null

    var mResourcePaint : Paint? = null
    var mRenderRect : Rect? = null
    var mIsElementDirty : Boolean = true

    constructor( aX : Int, aY : Int, aColor : Int, aMaskFilter : BlurMaskFilter ) {
        topX = aX
        topY = aY

        mResourcePaint = Paint(0).apply {
            color = aColor
            maskFilter = aMaskFilter
        }

        mIsElementDirty = true
    }

    // ==============================================
    // GameElement OVERRIDES
    // ==============================================

    override fun onDraw( aCanvas : Canvas ) {
        val currTopX = topX?.toDouble()
        val currTopY = topY?.toDouble()

        val canvasWidth : Double = aCanvas.width.toDouble()
        val canvasHeight : Double = aCanvas.height.toDouble()

        if( canvasHeight != previousCanvasHeight || canvasWidth != previousCanvasWidth ) {
            previousCanvasWidth = canvasWidth
            previousCanvasHeight = canvasHeight

            mIsElementDirty = true
        }

        if( currTopX != null && currTopY != null && mIsElementDirty ) {

            val left = ( canvasWidth * ( currTopX / ScaleUtilities.SCALED_WIDTH) ).toInt()
            val top = ( canvasWidth * (currTopY / ScaleUtilities.SCALED_HEIGHT) ).toInt()
            val right = ( canvasWidth * ((currTopX + 20) / ScaleUtilities.SCALED_WIDTH) ).toInt()
            val bottom = ( canvasWidth * ((currTopY + 20) / ScaleUtilities.SCALED_HEIGHT) ).toInt()

            mRenderRect = Rect(left, top, right, bottom )

            mIsElementDirty = false
        }

        aCanvas.drawRect(mRenderRect, mResourcePaint)
        val testPaint : Paint = Paint(0).apply{ color = 0x50505 }
        aCanvas.drawLine(0F, 0F, 20F, 20F, testPaint);

    }

    override fun hasCollided( aX : Int, aY : Int ) {

    }
}