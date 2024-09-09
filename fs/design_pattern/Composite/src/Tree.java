import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.io.File;

public class Tree {
    private File file;

    public Tree(String path) {
        file = new File(path);
    }

    public void print() {
        printFiles(file, 0);
    }

    // helper function
    private void printFiles(File file, int tabLevel) {
        File[] files = file.listFiles();

        if (files == null) {
            return;
        }

        for (File singleFile : files) {
            //for proper indentation
            StringBuilder indent = new StringBuilder();
            for (int i = 0; i < tabLevel; i++) {
                indent.append("\t");
            }

            System.out.println(indent + singleFile.getName());
            printFiles(singleFile , tabLevel + 1);
        }
    }

    public static void main(String[] args) {
        Tree tree = new Tree(".");

        tree.print();
    }

}



