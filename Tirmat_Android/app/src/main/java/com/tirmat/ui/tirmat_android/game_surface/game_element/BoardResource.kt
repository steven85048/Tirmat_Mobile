package com.tirmat.ui.tirmat_android.game_surface.game_element

import android.graphics.*

class BoardResource : GameElement {

    var indexX : Int? = null
    var indexY : Int? = null

    var resourceSize : Int? = null

    // Will be replaced by shared resource object in future
    var resourceType : Int? = null

    var previousCanvasWidth : Double? = null
    var previousCanvasHeight : Double? = null

    var mResourcePaint : Paint? = null
    var mRenderRect : Rect? = null
    var mIsElementDirty : Boolean = true

    constructor( aX : Int, aY : Int, aSize : Int, aColor : Int, aMaskFilter : BlurMaskFilter ) {
        indexX = aX
        indexY = aY

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
        val currTopX = indexX?.toDouble()
        val currTopY = indexY?.toDouble()
        val currResourceSize = resourceSize?.toDouble()

        val canvasWidth : Double = aCanvas.width.toDouble()
        val canvasHeight : Double = aCanvas.height.toDouble()

        if( canvasHeight != previousCanvasHeight || canvasWidth != previousCanvasWidth ) {
            previousCanvasWidth = canvasWidth
            previousCanvasHeight = canvasHeight

            mIsElementDirty = true
        }

        if( mIsElementDirty && currTopX != null && currTopY != null && currResourceSize != null ) {

            val left = ( BoardConfig.MARGIN_SIDES + ( currTopX * currResourceSize ) ).toInt()
            val top = BoardConfig.MAX_MARGIN_TOP + ( currTopY * currResourceSize ).toInt()
            val right = ( left + currResourceSize ).toInt()
            val bottom = ( top + currResourceSize ).toInt()

            mRenderRect = Rect(left, top, right, bottom )

            mIsElementDirty = false
        }

        aCanvas.drawRect(mRenderRect, mResourcePaint)
    }

    override fun hasCollided( aX : Int, aY : Int ) : Boolean? {
        if( mRenderRect != null ) {
            return mRenderRect?.contains(aX, aY)
        }

        return false
    }
}