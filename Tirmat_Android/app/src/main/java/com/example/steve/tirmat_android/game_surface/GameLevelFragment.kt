package com.example.steve.tirmat_android.game_surface

import android.content.Context
import android.net.Uri
import android.os.Bundle
import android.app.Fragment
import android.view.LayoutInflater
import android.view.SurfaceView
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout

import com.example.steve.tirmat_android.R


class GameLevelFragment : Fragment() {

    private var listener: OnFragmentInteractionListener? = null
    private var gameSurfaceView : GameView? = null;

    // Get passed data from parent activity here
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_game_level, container, false)
    }

    override fun onViewCreated(view: View?, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        // Attach the game surface to the game
        var surfaceContainer : LinearLayout? = view?.findViewById( GameLevelFragment.SURFACE_CONTAINER_ID );
        gameSurfaceView = GameView( getActivity().applicationContext );

        surfaceContainer?.addView( gameSurfaceView );
    }

    // onAttach and onDetach guarantee that this fragment is still apart of the parent activity

    override fun onAttach(context: Context) {
        super.onAttach(context)
        if (context is OnFragmentInteractionListener) {
            listener = context
        } else {
            throw RuntimeException(context.toString() + " must implement OnFragmentInteractionListener")
        }
    }

    override fun onDetach() {
        super.onDetach()
        listener = null
    }

    override fun onStart() {
        super.onStart();
    }

    override fun onPause() {
        super.onPause();
    }

    // This interface defines the ways other classes can
    // listen to events from this fragment
    interface OnFragmentInteractionListener {
        fun onFragmentInteraction(uri: Uri)
    }

    // Equivalent to static members
    companion object {
        val SURFACE_CONTAINER_ID = R.id.board_container;

        @JvmStatic
        fun newInstance() = GameLevelFragment();
    }
}
