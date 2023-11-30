// Prototype interface
interface Animal {
    clone(): Animal;
    speak(): string;
}

// Concrete prototype
class Dog implements Animal {
    speak(): string {
        return 'Woof!';
    }

    clone(): Animal {
        return Object.create(this);
    }
}

// Client code
function petOwner(animalPrototype: Animal): void {
    const pet = animalPrototype.clone();
    console.log(`Pet says: ${pet.speak()}`);
}

// Example usage
const dogPrototype = new Dog();
petOwner(dogPrototype);

// Creating a new Dog instance through cloning
const anotherDog = dogPrototype.clone();
console.log(anotherDog.speak()); // Outputs: Woof!
