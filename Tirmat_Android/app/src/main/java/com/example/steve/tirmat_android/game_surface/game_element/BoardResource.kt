package com.example.steve.tirmat_android.game_surface.game_element

import android.graphics.*

class BoardResource : GameElement {

    var topX : Int? = null
    var topY : Int? = null
    var resourceSize : Int? = null

    // Will be replaced by shared resource object in future
    var resourceType : Int? = null

    var previousCanvasWidth : Double? = null
    var previousCanvasHeight : Double? = null

    var mResourcePaint : Paint? = null
    var mRenderRect : Rect? = null
    var mIsElementDirty : Boolean = true

    constructor( aX : Int, aY : Int, aSize : Int, aColor : Int, aMaskFilter : BlurMaskFilter ) {
        topX = aX
        topY = aY
        resourceSize = aSize

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
        val currResourceSize = resourceSize?.toDouble()

        val canvasWidth : Double = aCanvas.width.toDouble()
        val canvasHeight : Double = aCanvas.height.toDouble()

        if( canvasHeight != previousCanvasHeight || canvasWidth != previousCanvasWidth ) {
            previousCanvasWidth = canvasWidth
            previousCanvasHeight = canvasHeight

            mIsElementDirty = true
        }

        if( currTopX != null && currTopY != null && currResourceSize != null && mIsElementDirty ) {

            val left = ( canvasWidth * ( currTopX / BoardConfig.SCALED_WIDTH) ).toInt()
            val top = ( canvasWidth * (currTopY / BoardConfig.SCALED_HEIGHT) ).toInt()
            val right = ( canvasWidth * ((currTopX + currResourceSize) / BoardConfig.SCALED_WIDTH) ).toInt()
            val bottom = ( canvasWidth * ((currTopY + currResourceSize) / BoardConfig.SCALED_HEIGHT) ).toInt()

            mRenderRect = Rect(left, top, right, bottom )

            mIsElementDirty = false
        }

        aCanvas.drawRect(mRenderRect, mResourcePaint)
    }

    override fun hasCollided( aX : Int, aY : Int ) {

    }
}