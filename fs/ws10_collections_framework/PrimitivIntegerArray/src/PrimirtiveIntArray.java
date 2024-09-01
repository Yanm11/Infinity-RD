import java.lang.reflect.Array;
import java.util.*;

public class PrimirtiveIntArray {
    public static void main(String[] args) {
        /* *************** ex1 ******************** */
        int[] arr = {8,5,8,9,4,1,2,3,6,9,7,8569,48,4869,1483,146,17866};

        //print the array
        System.out.println("ex1:");
        System.out.println(Arrays.toString(arr));

        //create a list from the array
        List<Integer> numberList = new ArrayList<>();
        for (int i : arr) {
            numberList.add(i);
        }

        //sort the collection
        Collections.sort(numberList);
        System.out.println(numberList);
        /* ********************************* */

        /* *************** ex2 ******************** */
        System.out.println("ex2:");

        String[] daysNames = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        int[] daysValues = new int[7];

        HashMap<String, Integer> daysOfWeek = new HashMap<>();
        for (int i = 0; i < daysValues.length; ++i) {
            daysOfWeek.put(daysNames[i], i + 1);
        }
        // print entries
        for (Map.Entry<String,Integer> entry : daysOfWeek.entrySet()) {
            System.out.println(entry.getKey() + ":" + entry.getValue());
        }
        // print values
        for (Integer value : daysOfWeek.values()) {
            System.out.println(value);
        }
        /* ********************************* */

        /* ***************** ex3 **************** */
        System.out.println("ex3:");

        DataObject[] dataObjects = new DataObject[11];
        HashMap<String, Integer> mapDO = new HashMap<>();

        dataObjects[0] = new DataObject("CODE1", 10);
        dataObjects[1] = new DataObject("CODE1", 20);
        dataObjects[2] = new DataObject("CODE1", 30);
        dataObjects[3] = new DataObject("CODE2", 40);
        dataObjects[4] = new DataObject("CODE2", 50);
        dataObjects[5] = new DataObject("CODE2", 60);
        dataObjects[6] = new DataObject("CODE2", 70);
        dataObjects[7] = new DataObject("CODE3", 80);
        dataObjects[8] = new DataObject("CODE3", 90);
        dataObjects[9] = new DataObject("CODE3", 100);
        dataObjects[10] = new DataObject("CODE3", 110);

        for (DataObject i : dataObjects) {
            mapDO.computeIfPresent(i.getCode(), (k,v) -> v + i.getValue());
            mapDO.computeIfAbsent(i.getCode(), k -> i.getValue());
        }

        for (Map.Entry<String,Integer> enrty : mapDO.entrySet()) {
            System.out.println(enrty.getKey() + ":" + enrty.getValue());
        }
    }
}

class DataObject {
    private String code;
    private int value;

    public DataObject(String code, int value) {
        this.code = code;
        this.value = value;
    }

    // getters and setters
    public int getValue() {
        return this.value;
    }
    public void setValue(int value) {
        this.value = value;
    }

    public String getCode() {
        return this.code;
    }
    public void setCode(String code) {
        this.code = code;
    }
}
