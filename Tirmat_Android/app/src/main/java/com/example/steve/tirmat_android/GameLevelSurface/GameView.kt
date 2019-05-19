package com.example.steve.tirmat_android.GameLevelSurface

import android.content.Context
import android.graphics.Canvas
import android.view.MotionEvent
import android.view.SurfaceHolder
import android.view.SurfaceView

// Holds and handles events from the game SurfaceView
class GameView : SurfaceView, SurfaceHolder.Callback {
    private var mContext : Context? = null;
    private var mSurfaceHolder : SurfaceHolder? = null;

    private var mRenderThread : RenderThread? = null;

    constructor(aContext : Context?): super(aContext){
        mContext = context;

        mRenderThread = RenderThread(this);

        mSurfaceHolder = getHolder();
        mSurfaceHolder?.addCallback(this);

    }

    // Draws the passed canvas from the render thread;
    // the child thread should handle thread safety
    fun drawCanvas( aCanvas : Canvas? ) {

    }

    // SurfaceView OVERRIDES
    override fun onTouchEvent( aEvent : MotionEvent ): Boolean {
        return true;
    }

    // SurfaceHolder.Callback OVERRIDES
    override fun surfaceDestroyed(aHolder : SurfaceHolder) {
        mRenderThread?.let {
            it?.cancelRender();
            it?.join();
        }
    }

    override fun surfaceCreated(aHolder : SurfaceHolder) {
        mRenderThread?.let {
            it?.startRender();
            it?.start();
        }
    }

    override fun surfaceChanged(aHolder : SurfaceHolder, aFormat : Int, aWidth : Int, aHeight : Int) {

    }
}