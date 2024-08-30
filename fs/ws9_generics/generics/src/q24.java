
import java.util.ArrayList;
import java.util.List;

public class q24 {
    public static void main(String[] args) {
        List rawList;
        List<?> listOfAnyType = new ArrayList<Object>();
        List<Object> listOfObject = new ArrayList<Object>();
        List<String> listOfString = new ArrayList<String>();
        List<Integer> listOfInteger = new ArrayList<Integer>();

        rawList = listOfAnyType;
        rawList = listOfString;
        rawList = listOfInteger;
        listOfAnyType = listOfString;
        listOfAnyType = listOfInteger;
    }
}
