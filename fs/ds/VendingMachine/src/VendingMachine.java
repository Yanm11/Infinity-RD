//yan meiri
//19.08.2024
//approved by Or

import java.util.Timer;
import java.util.TimerTask;

public class VendingMachine {

    private VendingMachineState state = VendingMachineState.OFF;;
    private int credit = 0;
    private Monitor monitor;
    private VendingSlot[] slots;
    private static final int DEFAULT_INITIAL_SIZE = 10;
    private Product chosenProduct;
    private int chosenProductCode;

    private Timer inactivityTimer;;
    private static final long TIMEOUT_DURATION = 5000; // 5 seconds

    public VendingMachine(Monitor monitor, Product[] productList) {
        this.monitor = monitor;

        this.slots = new VendingSlot[productList.length];
        for (int i = 0; i < this.slots.length; ++i) {
            this.slots[i] = new VendingSlot(productList[i], DEFAULT_INITIAL_SIZE, i);
        }
    }

    public int getCredit() {
        return credit;
    }
    public void cancel() {
        this.state.cancel(this);
    }
    public void insertCoin(Coin coin) {
        this.state.insertCoin(this, coin);
    }
    public void selectProduct(int slotIndex) {
        if (slotIndex < 0 || slotIndex >= this.slots.length) {
            this.monitor.display("Invalid slot index");
            return;
        }

        this.chosenProduct = this.slots[slotIndex].getProduct();
        this.chosenProductCode = slotIndex;

        this.state.selectProduct(this, this.chosenProduct);
    }
    public void turnOn() {
        this.state.turnOn(this);
    }
    public void turnOff() {
        this.state.turnOff(this);
    }

    // timer functions
    private void startInactivityTimer() {
        this.inactivityTimer = new Timer();
        inactivityTimer.schedule(
                new TimerTask() {
                    @Override
                    public void run() {
                        timeoutAction();
                    }
                }, TIMEOUT_DURATION);
    }

    private void cancelInactivityTimer() {
        if (inactivityTimer != null) {
            inactivityTimer.cancel();
        }
    }

    private void timeoutAction() {
        this.monitor.display("Timeout: Transaction cancelled Refunding:");
        this.state.cancel(this);
    }

    private static class VendingSlot {
        private Product product;
        private int amount;
        private int code;

        //ctor
        public VendingSlot(Product product, int amount, int code){
            this.product = product;
            this.amount = amount;
            this.code = code;
        }

        public void decreaseAmount() {
            this.amount -= 1;
        }

        //optional
        // getters and setter
        public Product getProduct() {
            return product;
        }
        public int getAmount() {
            return amount;
        }
        public int getCode() {
            return code;
        }
        public void setAmount(int amount) {
            this.amount = amount;
        }
        public void setProduct(Product product) {
            this.product = product;
        }
    }

    private enum VendingMachineState {
        WAITING_FOR_SELECTION {
            @Override
            public void cancel(VendingMachine vm) {
                vm.cancelInactivityTimer();
                returnChange(vm);
            }

            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.credit += coin.getValue();
            }

            @Override
            public void selectProduct(VendingMachine vm, Product product) {
                purchaseProduct(vm, product);
            }
        },
        WAITING_FOR_COINS {
            @Override
            public void cancel(VendingMachine vm) {
                vm.cancelInactivityTimer();
                returnChange(vm);
                vm.state = VendingMachineState.WAITING_FOR_SELECTION;
            }

            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.credit += coin.getValue();
                vm.inactivityTimer.cancel();
                vm.state.selectProduct(vm, vm.chosenProduct);
            }

            @Override
            public void selectProduct(VendingMachine vm, Product product) {
               purchaseProduct(vm, product);
            }
        },
        OFF {
            @Override
            public void turnOn(VendingMachine vm) {
                vm.state = VendingMachineState.WAITING_FOR_SELECTION;
            }
            @Override
            public void turnOff(VendingMachine vm) {}
        };

        public void cancel(VendingMachine vm){};
        public void insertCoin(VendingMachine vm, Coin coin){};
        public void selectProduct(VendingMachine vm, Product product){};
        public void turnOn(VendingMachine vm){};
        public void turnOff(VendingMachine vm){
            vm.cancelInactivityTimer();
            returnChange(vm);
            vm.state = VendingMachineState.OFF;
        };

        // helper functions
        public void returnChange(VendingMachine vm) {
            vm.monitor.display(String.valueOf(vm.credit));
            vm.credit = 0;
        }

        int purchaseProduct(VendingMachine vm, Product product) {
            int price = product.getPrice();
            String productName = product.getName();
            VendingSlot slot = vm.slots[vm.chosenProductCode];

            if (vm.credit >= price && slot.amount > 0) {
                vm.monitor.display("Here is the product you requested:" + productName);
                vm.credit -= price;
                slot.decreaseAmount();
                vm.cancelInactivityTimer();
                vm.state = VendingMachineState.WAITING_FOR_SELECTION;

                return 0;
            }
            else if (vm.credit < price && slot.amount > 0){
                int remaining = price - vm.credit;
                vm.monitor.display("Please pay:" + remaining + "\nTo purchase:" + productName);
                vm.state = VendingMachineState.WAITING_FOR_COINS;
                vm.startInactivityTimer();
            }
            else{
                vm.monitor.display("Product:" + productName + " is out of stock");
                vm.cancelInactivityTimer();
                vm.state = VendingMachineState.WAITING_FOR_SELECTION;
            }

            return 1;
        }
    }
}



