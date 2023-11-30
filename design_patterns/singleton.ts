class Singleton {
    private static instance: Singleton | null = null;

    // Private constructor to prevent instantiation
    private constructor() {}

    // Static method to get the singleton instance
    public static getInstance(): Singleton {
        if (!Singleton.instance) {
            Singleton.instance = new Singleton();
        }
        return Singleton.instance;
    }

    // Some member function
    public showMessage(): void {
        console.log("Hello from Singleton!");
    }
}

// Example usage
const singletonInstance1 = Singleton.getInstance();
singletonInstance1.showMessage();

// Attempting to create a new instance will not work
// const singletonInstance2 = new Singleton(); // Error: private constructor

// Another way to use the instance
const singletonInstance3 = Singleton.getInstance();
singletonInstance3.showMessage();

// Instances 1 and 3 refer to the same object
console.log(singletonInstance1 === singletonInstance3); // true
