package com.tirmat.ui.tirmat_android.game_surface

import android.graphics.Canvas
import android.util.Log

class RenderThread : Thread {
    private var mGameView : GameView? = null
    private var mThreadActive : Boolean = false

    constructor( aGameView : GameView) {
        mGameView = aGameView
    }

    fun startRender() {
        mThreadActive = true
    }

    fun cancelRender() {
        mThreadActive = false
    }

    // Thread OVERRIDES

    override fun run() {
        while( mThreadActive ) {
            var theCanvas : Canvas? = null
            try {
                theCanvas = mGameView?.getHolder()?.lockCanvas()

                mGameView?.let {
                    synchronized( it.getHolder() ) {
                        Log.e( "RenderThread.kt", "Rendering next canvas frame" )
                        this.mGameView?.drawCanvas( theCanvas )
                        it.drawCanvas( theCanvas );
                    }
                }

            } finally {
                theCanvas?.let {
                    this.mGameView?.getHolder()?.unlockCanvasAndPost( it );
                }
            }
        }
    }
}