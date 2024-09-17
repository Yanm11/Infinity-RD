import javax.imageio.IIOException;
import java.io.IOException;

public class TestDirMonitor {
    public static void main(String[] args) {
        try {
            DirMonitor watcher = new DirMonitor("/home/parallels/dirWatcherfile.txt",
                                                "/home/parallels/git");
            watcher.watch();
        }
        catch (InterruptedException | IOException ignore) {}
    }
}
