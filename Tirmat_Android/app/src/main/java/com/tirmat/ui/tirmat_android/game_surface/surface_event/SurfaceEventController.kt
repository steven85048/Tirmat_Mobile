package com.tirmat.ui.tirmat_android.game_surface.surface_event

import android.util.Log
import android.view.MotionEvent
import com.tirmat.ui.generated.djinni.GameEngineFactoryIntf
import com.tirmat.ui.generated.djinni.GameInteractorIntf
import com.tirmat.ui.generated.djinni.ResourceType
import com.tirmat.ui.tirmat_android.game_surface.GameElementManager
import com.tirmat.ui.tirmat_android.game_surface.game_element.BoardResource

// Handles motion events received from the surface;
// Generates Event object depending on the analyzed state
class SurfaceEventController {

    var mGameElementManager : GameElementManager? = null
    var mGameInteractor : GameInteractorIntf? = null

    constructor( aGameElementManager : GameElementManager?, aGameEngineInteractor : GameInteractorIntf ) {
        mGameElementManager = aGameElementManager
        mGameInteractor = aGameEngineInteractor
    }

    // Handler for events received from the SurfaceView (MotionEvent)
    fun onSurfaceMotionEvent( aMotionEvent : MotionEvent ) {
        val action = aMotionEvent.actionMasked

        when( action ) {
            MotionEvent.ACTION_DOWN -> {
                var gameElement = mGameElementManager?.getCollidedElement( aMotionEvent.x.toInt(), aMotionEvent.y.toInt() )

                if( gameElement is BoardResource ){
                    var indexX = gameElement.indexX
                    var indexY = gameElement.indexY

                    if( indexX != null && indexY != null ) {
                        mGameInteractor?.AddResource( indexX, indexY, ResourceType.L1 )
                    }
                }

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