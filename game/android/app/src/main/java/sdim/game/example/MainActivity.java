package sdim.game.example;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {

    @Override
    final protected String[] getLibraries() {
        return new String[]{"game"};
    }

    @Override
    final protected String getMainFunction() {
        return "main";
    }

    @Override
    public void loadLibraries() {
        super.loadLibraries();
    }



    /*@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }*/
}