#include<bits/stdc++.h>
using namespace std;
class Hotel{
    string name;
    int id;
    Location hotelLocation;
    vector<Room> roomList;
};

class Location{
    double longitude;
    double latitude;
};

class Room{
    string roomNumber;
    RoomStyle roomStyle;
    RoomStatus roomStatus;
    double bookingPrice;
    vector<RoomKey> roomKeys;
    vector<HouseKeepingLog> houseKeepingLog;
};

enum RoomStyle{
    STANDARD, DELUX, FAMILY_SUITE
};

enum RoomStatus {
	
	AVAILABLE, RESERVED, NOT_AVAILBLE, OCCUPIED, SERVICE_IN_PROGRESS
};

class RoomKey{
    string keyId;
    string barCode;
    string issuedAt;
    bool isMaster;
    bool isActive;

    void assignRoom(Room room);
};

class HouseKeepingLog{
    string description;
    string startDate;
    HouseKeeper housekeeper;
    void addRoom(Room room);
};

class Person{
    string name;
    Account accountDetail;
    string phone;
};

class Account{
    string username;
    string password;
    AccountStatus accountstatus;
};

enum AccountStatus {
	ACTIVE, CLOSED, BLOCKED
};

class HouseKeeper: public Person{
    vector<Room> getRoomServiced(string date);
};

class Guest: public Person{
    Search searchObj;
    Booking bookingObj;

    vector<RoomBooking> getAllRoomBooking();
    RoomBooking createBoodking();
    RoomBooking cancelBooking(int bookingId);
};

class Receptionist: public Person{
    Search searchObj;
    Booking bookingObj;

    checkInGuest(Guest guest, RoomBooking bookingInfo);
    checkOutGuest(Guest guest, RoomBooking bookingInfo);
};

class search {

	vector<Room> searchRoom(RoomStyle roomStyle, string startDate, int duration);

}

class Admin: public Person{
    void addRomm(Room roomDetail);
	Room deleteRoom(string roomId);
	void editRoom(Room roomDetail);
};

class RoomBooking{
    string bookingId;
    string startDate;
    int durationInDays;
    BookingStatus bookingStatus;
    vector<Guest> guestList;
    BaseRoomCharge totalRoomCharges;
};


/**
*	Decorator pattern is used to decorate the prices here.
**/

class BaseRoomCharge {

	double getCost();

};

class RoomCharge implements BaseRoomCharge {

	
	double cost;
	double getCost() {
		return cost;
	}
	void setCost(double cost) {
		this->cost = cost;
	}
};

class RoomServiceCharge implements BaseRoomCharge {

	double cost;
	BaseRoomCharge baseRoomCharge;
	double getCost() {
		baseRoomCharge.setCost(baseRoomCharge.getCost() + cost);
		return baseRoomCharge.getCost();
	}
};

class InRoomPurchaseCharges implements BaseRoomCharge {

	double cost;
	BaseRoomCharge baseRoomCharge;
	Double getCost() {
		baseRoomCharge.setCost(baseRoomCharge.getCost() + cost);
		return baseRoomCharge.getCost();
	}
};

class Booking {

	RoomBooking createBooking(Guest guestInfo);
	RoomBooking cancelBooking(int bookingId);

};





int main(){

}