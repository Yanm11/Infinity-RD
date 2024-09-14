import java.io.File;

public class SingleFile implements Print {
    private File file;

    public SingleFile(String path) {
        this.file = new File(path);
    }

    @Override
    public void print(String s) {
        System.out.println(s + file.getName());
    }
}


