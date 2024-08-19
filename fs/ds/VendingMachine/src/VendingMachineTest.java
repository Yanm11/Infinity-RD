import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.AfterEach;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.*;

class VendingMachineTest {

    private VendingMachine vendingMachine;
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;

    private static class StandardOutputMonitor implements Monitor {
        @Override
        public void display(String outPut) {
            System.out.println(outPut);
        }
    }

    @BeforeEach
    void setUp() {
        System.setOut(new PrintStream(outContent));
        Monitor monitor = new StandardOutputMonitor();
        Product[] products = {
                new ProductIMP("Coke", 250),
                new ProductIMP("Chips", 300),
                new ProductIMP("Candy", 150)
        };
        vendingMachine = new VendingMachine(monitor, products);
    }

    @AfterEach
    void restoreStreams() {
        System.setOut(originalOut);
    }

    private String getOutput() {
        return outContent.toString().trim();
    }

    @Test
    void testInitialState() {
        // We can't check the state directly, so we'll test the initial behavior
        vendingMachine.insertCoin(Coin.SHEKEL);
        assertEquals("", getOutput()); // No output expected when machine is off
        assertEquals(0, vendingMachine.getCredit());
    }

    @Test
    void testTurnOn() {
        vendingMachine.turnOn();
        vendingMachine.insertCoin(Coin.SHEKEL);
        assertEquals(100, vendingMachine.getCredit());
    }

    @Test
    void testTurnOff() {
        vendingMachine.turnOn();
        vendingMachine.insertCoin(Coin.SHEKEL);
        vendingMachine.turnOff();
        assertEquals("100", getOutput()); // Check if change was returned
        assertEquals(0, vendingMachine.getCredit());
    }

    @Test
    void testInsertCoin() {
        vendingMachine.turnOn();
        vendingMachine.insertCoin(Coin.SHEKEL);
        vendingMachine.insertCoin(Coin.TEN_SHEKEL);
        assertEquals(1100, vendingMachine.getCredit());
    }

    @Test
    void testSelectProductWithSufficientCredit() {
        vendingMachine.turnOn();
        vendingMachine.insertCoin(Coin.FIVE_SHEKEL);
        vendingMachine.selectProduct(0); // Assuming Coke is at index 0
        assertEquals("Here is the product you requested:Coke", getOutput());
        assertEquals(250, vendingMachine.getCredit());
    }

    @Test
    void testSelectProductWithInsufficientCredit() {
        vendingMachine.turnOn();
        vendingMachine.insertCoin(Coin.SHEKEL);
        vendingMachine.selectProduct(0); // Assuming Coke is at index 0
        String out = "Please pay:150\nTo purchase:Coke";
        assertEquals(out, getOutput());
        // We can't check the state, but we can verify that inserting more coins allows the purchase
        vendingMachine.insertCoin(Coin.SHEKEL);
        out = out + "\nPlease pay:50\nTo purchase:Coke";
        assertEquals(out, getOutput());
        vendingMachine.insertCoin(Coin.HEZI_SHEKEL);
        out = out + "\nHere is the product you requested:Coke";
        assertEquals(out, getOutput());
    }

    @Test
    void testCancel() {
        vendingMachine.turnOn();
        vendingMachine.insertCoin(Coin.SHEKEL);
        vendingMachine.cancel();
        assertEquals("100", getOutput());
        assertEquals(0, vendingMachine.getCredit());
    }

    @Test
    void testCompleteTransaction() {
        vendingMachine.turnOn();
        vendingMachine.insertCoin(Coin.SHEKEL);
        vendingMachine.selectProduct(2); // Assuming Candy is at index 2
        vendingMachine.insertCoin(Coin.HEZI_SHEKEL);
        assertEquals("Please pay:50\nTo purchase:Candy\nHere is the product you requested:Candy", getOutput());
        assertEquals(0, vendingMachine.getCredit());
    }

    @Test
    void testInsertCoinWhileOff() {
        vendingMachine.insertCoin(Coin.SHEKEL);
        assertEquals(0, vendingMachine.getCredit());
        assertEquals("", getOutput());
    }

    @Test
    void testSelectProductWhileOff() {
        vendingMachine.selectProduct(0);
        assertEquals("", getOutput());
    }

    @Test
    void testProductOutOfStock() {
        vendingMachine.turnOn();

        // Purchase the product 10 times (default initial size)
        for (int i = 0; i < 10; i++) {
            vendingMachine.insertCoin(Coin.SHEKEL);
            vendingMachine.insertCoin(Coin.HEZI_SHEKEL);
            vendingMachine.selectProduct(2); // Assuming Candy is at index 2
            assertEquals("Here is the product you requested:Candy", getOutput());
            outContent.reset(); // Clear the output for the next iteration
        }

        // Try to purchase the product one more time
        vendingMachine.insertCoin(Coin.FIVE_SHEKEL);
        vendingMachine.selectProduct(2);
        assertEquals("Product:Candy is out of stock", getOutput());

        // Ensure the credit is not deducted for out-of-stock product
        assertEquals(500, vendingMachine.getCredit());
    }

    @Test
    void invalidIndex(){
        vendingMachine.selectProduct(6);
        assertEquals("Invalid slot index", getOutput());
    }

    @Test
    void testTimeout() throws InterruptedException {
        vendingMachine.turnOn();
        vendingMachine.selectProduct(0); // Assuming Coke is at index 0

        // Wait for the timeout
        TimeUnit.SECONDS.sleep(6); // Wait for 6 seconds to ensure timeout occurs

        assertEquals("Please pay:250\nTo purchase:Coke\nTimeout: Transaction cancelled Refunding:\n0", getOutput().trim());
        assertEquals(0, vendingMachine.getCredit());

        // Verify that the machine is ready for a new selection and the timeout is canceled
        vendingMachine.insertCoin(Coin.FIVE_SHEKEL);
        vendingMachine.selectProduct(0);
        assertTrue(getOutput().contains("Here is the product you requested:Coke"));

    }
}