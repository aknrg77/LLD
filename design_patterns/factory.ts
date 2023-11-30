// Product interface
interface Animal {
    speak(): string;
}

// Concrete products
class Dog implements Animal {
    speak(): string {
        return 'Woof!';
    }
}

class Cat implements Animal {
    speak(): string {
        return 'Meow!';
    }
}

// Creator interface
interface AnimalFactory {
    createAnimal(): Animal;
}

// Concrete creators
class DogFactory implements AnimalFactory {
    createAnimal(): Animal {
        return new Dog();
    }
}

class CatFactory implements AnimalFactory {
    createAnimal(): Animal {
        return new Cat();
    }
}

// Client code
function petOwner(factory: AnimalFactory): void {
    const pet = factory.createAnimal();
    console.log(`Pet says: ${pet.speak()}`);
}

// Example usage
const dogFactory = new DogFactory();
petOwner(dogFactory);

const catFactory = new CatFactory();
petOwner(catFactory);
