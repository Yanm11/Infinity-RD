public enum Coin {
    TEN_AGOROT(10),
    HEZI_SHEKEL(50),
    SHEKEL(100),
    SHNEKEL(200),
    FIVE_SHEKEL(500),
    TEN_SHEKEL(1000);

    private final int value;

    private Coin(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}