package sdim.game.example;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;

public class JniManager {
    private Context context;

    public JniManager() {
        if (!this.initJni("Hello", 42)) {
            throw new RuntimeException("JNI not inited");
        }
    }

    boolean openUrl(String url) {
        try {
            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
            context.startActivity(intent);
        } catch (ActivityNotFoundException activityNotFoundException) {
            return false;
        }
        return true;
    }

    private native boolean initJni(String name, int version);
}
