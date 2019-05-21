package com.example.steve.tirmat_android.game_surface

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.Rect
import android.util.Log
import android.view.MotionEvent
import android.view.SurfaceHolder
import android.view.SurfaceView
import com.example.steve.tirmat_android.game_surface.surface_event.SurfaceEventController

// Holds and handles events from the game SurfaceView
// Starts background rendering thread, receives draw events from that,
// and then tells the gameElementManager to draw its elements
class GameView : SurfaceView, SurfaceHolder.Callback {
    private var mContext : Context? = null
    private var mGameElementManager : GameElementManager? = null;
    private var mSurfaceEventController : SurfaceEventController? = null;
    private var mSurfaceHolder : SurfaceHolder? = null

    private var mRenderThread : RenderThread? = null

    constructor(aContext : Context?): super(aContext){
        mContext = context

        mRenderThread = RenderThread(this)
        mGameElementManager = GameElementManager( this )
        mSurfaceEventController = SurfaceEventController( mGameElementManager )

        mSurfaceHolder = getHolder()
        mSurfaceHolder?.addCallback(this)

    }

    // Draws the passed canvas from the render thread;
    // the child thread should handle thread safety
    fun drawCanvas( aCanvas : Canvas? ) {
        aCanvas?.let {
            mGameElementManager?.onDraw( it )
        }
    }

    // ==============================================
    // SurfaceView OVERRIDES
    // ==============================================

    override fun onTouchEvent( aEvent : MotionEvent ): Boolean {
        mSurfaceEventController?.onSurfaceMotionEvent( aEvent )
        return true
    }

    // SurfaceHolder.Callback OVERRIDES
    override fun surfaceDestroyed(aHolder : SurfaceHolder) {
        Log.e("GameView", "SurfaceDestroyed");

        mRenderThread?.let {
            it?.cancelRender()
            it?.join()
        }
    }

    override fun surfaceCreated(aHolder : SurfaceHolder) {
        Log.e("GameView", "SurfaceCreated");

        mRenderThread?.let {
            it?.startRender()
            it?.start()
        }
    }

    override fun surfaceChanged(aHolder : SurfaceHolder, aFormat : Int, aWidth : Int, aHeight : Int) {
        mSurfaceHolder = aHolder;
    }
}