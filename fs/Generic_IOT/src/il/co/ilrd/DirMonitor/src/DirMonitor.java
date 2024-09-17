import java.io.IOException;
import java.nio.file.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DirMonitor {
    private final WatchService watchService;
    private final Path loggerFile;
    private WatchKey key;

    public DirMonitor(String pathToLogger, String pathToWatchedDir) throws IOException{
        // get the path to the logger file and convert it to Path
        loggerFile = Paths.get(pathToLogger);
        //create the watcher service and register the key
        watchService =  FileSystems.getDefault().newWatchService();

        Path dirToWatch = Paths.get(pathToWatchedDir);
        key = dirToWatch.register(watchService,StandardWatchEventKinds.ENTRY_CREATE
                                              ,StandardWatchEventKinds.ENTRY_DELETE
                                              ,StandardWatchEventKinds.ENTRY_MODIFY);
    }

    public void watch() throws InterruptedException, IOException {
        while ((key = watchService.take()) != null) {
            for (WatchEvent<?> event : key.pollEvents()) {
                //format the current timestamp
                LocalDateTime now = LocalDateTime.now();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");
                String timestamp = "<" + now.format(formatter) + "> ";

                //combine the timestamp and the log event to one string
                String logEventMessage = timestamp + "logged: " + event.kind() + " -At- " + event.context() + "\n";

                //write into the file
                Files.write(loggerFile, logEventMessage.getBytes(), StandardOpenOption.APPEND, StandardOpenOption.CREATE);
            }
            key.reset();
        }
    }
}
