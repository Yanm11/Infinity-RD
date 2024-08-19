public class VendingMachine {

    private VendingMachineState state;
    private int credit;
    private Monitor monitor;
    private VendingSlot[] slots;
    private static final int DEFAULT_INITIAL_SIZE = 10;
    private Product chosenProduct;
    private int chosenProductCode;

    public VendingMachine(Monitor monitor, Product[] productList) {
        this.monitor = monitor;
        this.credit = 0;
        this.state = VendingMachineState.OFF;

        this.slots = new VendingSlot[productList.length];
        int i = 0;
        for (Product product : productList) {
            this.slots[i] = new VendingSlot(product, DEFAULT_INITIAL_SIZE, i);
            ++i;
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
        Product product = this.slots[slotIndex].getProduct();
        this.chosenProduct = product;
        this.chosenProductCode = slotIndex;

        this.state.selectProduct(this, product);
    }
    public void turnOn() {
        this.state.turnOn(this);
    }
    public void turnOff() {
        this.state.turnOff(this);
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


        // toString
    }

    private enum VendingMachineState {
        WAITING_FOR_SELECTION {
            @Override
            public void cancel(VendingMachine vm) {
                returnChange(vm);
            }

            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.credit += coin.getValue();
            }

            @Override
            public void selectProduct(VendingMachine vm, Product product) {
                if (purchaseProduct(vm, product) == 1){
                    vm.state = VendingMachineState.WAITING_FOR_COINS;
                }

            }

            @Override
            public void turnOn(VendingMachine vm) {}

            @Override
            public void turnOff(VendingMachine vm) {
                returnChange(vm);
                vm.state = VendingMachineState.OFF;
            }
        },
        WAITING_FOR_COINS {
            @Override
            public void cancel(VendingMachine vm) {
                returnChange(vm);
                vm.state = VendingMachineState.WAITING_FOR_SELECTION;
            }

            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.credit += coin.getValue();
                Product product = vm.chosenProduct;

                if (purchaseProduct(vm, product) == 0){
                    vm.state = VendingMachineState.WAITING_FOR_SELECTION;
                }
            }

            @Override
            public void selectProduct(VendingMachine vm, Product product) {
               if (purchaseProduct(vm, product) == 0){
                   vm.state = VendingMachineState.WAITING_FOR_SELECTION;
               }
            }

            @Override
            public void turnOn(VendingMachine vm) {}

            @Override
            public void turnOff(VendingMachine vm) {
                returnChange(vm);
                vm.state = VendingMachineState.OFF;
            }
        },
        OFF {
            @Override
            public void cancel(VendingMachine vm) {}

            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {}

            @Override
            public void selectProduct(VendingMachine vm, Product product) {}

            @Override
            public void turnOn(VendingMachine vm) {
                vm.state = VendingMachineState.WAITING_FOR_SELECTION;
            }

            @Override
            public void turnOff(VendingMachine vm) {}
        };

        public abstract void cancel(VendingMachine vm);
        public abstract void insertCoin(VendingMachine vm, Coin coin);
        public abstract void selectProduct(VendingMachine vm, Product product);
        public abstract void turnOn(VendingMachine vm);
        public abstract void turnOff(VendingMachine vm);

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

                return 0;
            }
            else if (vm.credit < price && slot.amount > 0){
                int remaining = price - vm.credit;
                vm.monitor.display("Please pay:" + remaining + "\nTo purchase:" + productName);
            }
            else{
                vm.monitor.display("Product:" + productName + " is out of stock");
            }

            return 1;
        }
    }
}



