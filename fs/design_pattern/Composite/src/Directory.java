
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.File;

public class Directory implements Print {
    private String name;
    private ArrayList<Print> files = new ArrayList<>();

    public Directory(String path) throws FileNotFoundException {
       File file = new File(path);

       if (!file.exists()) {
           throw new FileNotFoundException("Path is not correct");
       }

       name = file.getName();

       if(!file.isDirectory()){
            throw new IllegalArgumentException("Not a directory");
       }

       File[] filesArr = file.listFiles();
       Arrays.sort(filesArr);

       for (File f : filesArr) {
           if(f.isDirectory()){
               files.add(new Directory(f.getPath()));
           }
           else{
               files.add(new SingleFile(f.getPath()));
           }
       }
    }

    public void print(String s) {
        System.out.println(s + name);
        for(Print f : files){
            f.print(s + "\t");
        }

    }

    public static void main(String[] args) throws FileNotFoundException{

    }

}



