package sdim.game.example;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {

    @Override
    final protected String[] getLibraries(){
        return new String[]{"game"};
    }

    @Override
    final protected String getMainFunction(){
        return "main";
    }


    /*@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }*/
}