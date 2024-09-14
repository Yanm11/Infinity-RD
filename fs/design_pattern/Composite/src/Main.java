// approve by ido
//14.9.2024

import java.io.FileNotFoundException;

public class Main {
    public static void main(String[] args) {
        Directory dir = null;
        try {
            dir = new Directory(".");
        }
        catch (FileNotFoundException ignored) {}

        dir.print("");
    }
}
