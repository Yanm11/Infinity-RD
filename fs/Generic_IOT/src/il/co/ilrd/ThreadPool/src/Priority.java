package il.co.ilrd.ThreadPool.src;

public enum Priority{
    HIGH(10),
    MEDIUM(5),
    LOW(1);

    private final int value;

    private Priority(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }
}