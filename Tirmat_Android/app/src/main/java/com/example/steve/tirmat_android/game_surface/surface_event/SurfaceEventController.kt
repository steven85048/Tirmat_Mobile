package com.example.steve.tirmat_android.game_surface.surface_event

import android.util.Log
import android.view.MotionEvent
import com.example.steve.tirmat_android.game_surface.GameElementManager

// Handles motion events received from the surface;
// Generates Event object depending on the analyzed state
class SurfaceEventController {

    var mGameElementManager : GameElementManager? = null

    constructor( aGameElementManager : GameElementManager? ) {
        mGameElementManager = aGameElementManager
    }

    // Handler for events received from the SurfaceView (MotionEvent)
    fun onSurfaceMotionEvent( aMotionEvent : MotionEvent ) {
        val action = aMotionEvent.actionMasked

        when( action ) {
            MotionEvent.ACTION_DOWN -> {
                Log.e("SurfaceEventController", "ACTION_DOWN")
            }

            MotionEvent.ACTION_MOVE -> {
                Log.e("SurfaceEventController", "ACTION_MOVE")
            }

            MotionEvent.ACTION_POINTER_UP -> {
                Log.e("SurfaceEventController", "ACTION_POINTER_UP")
            }

            MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                Log.e("SurfaceEventController", "ACTION_UP")
            }
        }
    }
}