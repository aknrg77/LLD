class ParkingLot{
    private parkingLotId: number;
    private address: Address;
    private parkingFloors: ParkingFloor[];
    static instance: ParkingLot;
    private ParkingLot(parkingLotId: number, address: Address, parkingFloors: ParkingFloor[]){
        this.parkingLotId = parkingLotId;
        this.address = address;
        this.parkingFloors = parkingFloors;
    }
    static getInstance(): ParkingLot{
        if(!ParkingLot.instance){
            ParkingLot.instance = new ParkingLot();
        }
        return ParkingLot.instance;
    }

    addFloor(parkingLotId: number, parkingFloor: ParkingFloor){
        this.parkingLotId = parkingLotId
        this.parkingFloors.push(parkingFloor);
    }

    removeFloor(parkingFloor: ParkingFloor){
        this.parkingFloors = (this.parkingFloors.filter(floor => floor!== parkingFloor));
    }

    getParkingForVehicleAndPark(vehicle: Vehicle): ParkingSpot{
        let slot: any = null;
        for(let floor of this.parkingFloors){
            slot = floor.getReleventParkingSpotAndPark(vehicle);
            if (slot!==null){
                break;
            }
        }
        return slot;
    }

    scanAndPay(ticket: Ticket): Number{
        let endTime: any = Date.now();
        ticket.getParkingSpot().free(ticket.getVehicle());
        let duration: any = Math.ceil((endTime-ticket.getStartTime())/1000);
        let price: any = ParkingSpotType[ticket.getVehicle().getVehicleCategory()]*duration;
        return price;
    }

};

class ParkingFloor{
    private parkingFloorId: number;
    private parkingSlots = new Map<VehicleCategory, Map<number, ParkingSpot>>;
                                // ((Car, (1st Floor, ParkingSpot))
    parkingFloor(parkingFloorId: number, parkingSlots: Map<VehicleCategory, Map<number, ParkingSpot>>){
        this.parkingFloorId = parkingFloorId;
        this.parkingSlots = parkingSlots;
    }

    getReleventParkingSpotAndPark(vehicle: Vehicle): ParkingSpot{
        let releventParkingSpot: Map<number, ParkingSpot> | any= this.parkingSlots.get(vehicle.getVehicleCategory());
        let slot: any= null;
        
        for(let entry of releventParkingSpot.values()){
            if(entry.isFree()){
                slot = entry;
                slot.park(vehicle);
                break;
            }
        }

        return slot;
    }

};

class ParkingSpot{
    private parkingSpotId: number;
    private parkingSpotType: VehicleCategory;
    private isAvailable: boolean = true;
    private vehicle: Vehicle | null;
    
    park(vehicle: Vehicle): ParkingSpot{
        this.vehicle = vehicle;
        this.isAvailable = false;
        this.parkingSpotId = Date.now();
        this.parkingSpotType = vehicle.getVehicleCategory();

        return this;
    }

    isFree(){
        return this.isAvailable;
    }

    free(vehicle: Vehicle): void{
        this.vehicle = null;
        this.isAvailable = true;
    }
};


enum ParkingSpotType{
    "car" = 0.5,
    "motorcycle" = 0.25
};

class Vehicle{
    private vehicleId: number;
    private vehicleCategory: VehicleCategory

    getVehicleCategory(): VehicleCategory{
        return this.vehicleCategory;
    }
}

enum VehicleCategory{
    Car = "car",
    MotorCycle = "motorcycle"
};


class Address{
    private street: String;
    private block: String;
    private city: String;
    private state: String;
    private country: String;
};

class Ticket{
    private ticketNumber: String;
    private startTime: any;
    private endTime: any;
    private vehicle: Vehicle;
    private parkingSpot: ParkingSpot;

    Ticket(vehicle: Vehicle, parkingSpot: ParkingSpot){
        this.ticketNumber = String(Date.now());
        this.startTime = Date.now();
        this.vehicle = vehicle;
        this.parkingSpot = parkingSpot;
    }

    getStartTime(): any{
        return this.startTime;
    }

    getVehicle(): Vehicle{
        return this.vehicle;
    }

    getParkingSpot(): ParkingSpot{
        return this.parkingSpot;
    }
};
