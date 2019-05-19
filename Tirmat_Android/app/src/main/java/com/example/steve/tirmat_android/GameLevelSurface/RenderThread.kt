package com.example.steve.tirmat_android.GameLevelSurface

import android.graphics.Canvas

class RenderThread : Thread {
    private var mGameView : GameView? = null;
    private var mThreadActive : Boolean = false;

    constructor( aGameView : GameView ) {
        mGameView = aGameView;
    }

    fun startRender() {
        mThreadActive = true;
    }

    fun cancelRender() {
        mThreadActive = false;
    }

    // Thread OVERRIDES

    override fun run() {
        while( mThreadActive ) {
            var theCanvas : Canvas? = null;
            try {
                theCanvas = mGameView?.getHolder()?.lockCanvas();

                mGameView?.let {
                    synchronized( it.getHolder() ) {
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