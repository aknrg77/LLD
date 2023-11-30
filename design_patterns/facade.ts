// Subsystem 1
class Light {
    turnOn(): void {
        console.log('Light is ON');
    }

    turnOff(): void {
        console.log('Light is OFF');
    }
}

// Subsystem 2
class AirConditioner {
    startCooling(): void {
        console.log('Air Conditioner is cooling');
    }

    stopCooling(): void {
        console.log('Air Conditioner stopped cooling');
    }
}

// Subsystem 3
class SoundSystem {
    turnOn(): void {
        console.log('Sound System is ON');
    }

    turnOff(): void {
        console.log('Sound System is OFF');
    }
}

// Facade
class HomeAutomationFacade {
    private light: Light;
    private airConditioner: AirConditioner;
    private soundSystem: SoundSystem;

    constructor() {
        this.light = new Light();
        this.airConditioner = new AirConditioner();
        this.soundSystem = new SoundSystem();
    }

    // Simplified methods for common actions
    goHome(): void {
        this.light.turnOn();
        this.airConditioner.startCooling();
        this.soundSystem.turnOn();
    }

    leaveHome(): void {
        this.light.turnOff();
        this.airConditioner.stopCooling();
        this.soundSystem.turnOff();
    }
}

// Client code
function useHomeAutomation(): void {
    const homeAutomation = new HomeAutomationFacade();

    // Coming home
    homeAutomation.goHome();

    // Leaving home
    homeAutomation.leaveHome();
}

// Example usage
useHomeAutomation();
