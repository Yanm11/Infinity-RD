
enum EWeekDay {
    SUNDAY(1),
    MONDAY(2),
    TUESDAY(3),
    WEDNESDAY(4),
    THURSDAY(5),
    FRIDAY(6),
    SATURDAY(7);

    private int value;

    EWeekDay(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public static EWeekDay fromValue(int value) {
        switch (value) {
            case 1: return SUNDAY;
            case 2: return MONDAY;
            case 3: return TUESDAY;
            case 4: return WEDNESDAY;
            case 5: return THURSDAY;
            case 6: return FRIDAY;
            case 7: return SATURDAY;
            default: return null;
        }
    }

    public void printValues() {
        for (EWeekDay day : EWeekDay.values()) {
                System.out.println(day.toString());
        }
    }

}

public class EnumsEx {
    public static void main(String[] args) {
        EWeekDay weekDay = EWeekDay.SATURDAY;
        System.out.println(weekDay.getValue());
        System.out.println(EWeekDay.fromValue(weekDay.getValue()));
        System.out.println(EWeekDay.fromValue(EWeekDay.SUNDAY.getValue()));
        weekDay.printValues();
    }
}

