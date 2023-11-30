#include <bits/stdc++.h>
using namespace std;

enum Direction{
    Up,
    Down,
    Idle
};

enum Location{
    Outside,
    Inside
};

class Request{
    public:
    int currentFloor;
    int desiredFloor;
    Direction direction;
    Location location;

    Request(int currentFloor, int desiredFloor, Direction direction, Location location){
        this->currentFloor = currentFloor;
        this->desiredFloor = desiredFloor;
        this->direction = direction;
        this->location = location;
    }
};

class Elevator{
    public:
    int currentFloor;
    Direction direction;
    //min heap
    priority_queue<Request, vector<Request>, greater<Request>> upqueue;

    //max heap
    priority_queue<Request> downqueue;

    Elevator(int currentFloor){
        this->currentFloor = currentFloor;
        this->direction = Direction::Idle;
    }

    void sendUpRequest(Request upRequest){
        if (upRequest.location == Location::Outside){
            Request upReq = Request(upRequest.currentFloor, upRequest.currentFloor, Direction::Up, Location::Outside);
            upqueue.push(upReq);
            cout<<"Append up request going to floor "<< upRequest.currentFloor <<"."<<endl;
        }

        upqueue.push(upRequest);
        cout<<"Append up request going to floor "<< upRequest.desiredFloor <<"."<<endl;
    }

    void sendDownRequest(Request downRequest){
        if (downRequest.location == Location::Outside){
            Request downReq = Request(downRequest.currentFloor, downRequest.currentFloor, Direction::Down, Location::Outside);
            downqueue.push(downReq);
            cout<<"Append down request going to floor "<< downRequest.currentFloor <<"."<<endl;
        }

        downqueue.push(downRequest);
        cout<<"Append down request going to floor "<< downRequest.desiredFloor <<"."<<endl;

    }

    void run(){
        while(!upqueue.empty() || !downqueue.empty()){
            processRequest();
        }
        cout<<"Finished all requests."<<endl;
        this->direction = Direction::Idle;
    }


    void processRequest(){
        if(this->direction == Direction::Up || this->direction == Direction::Idle){
            processUpRequest();
            processDownRequest();
        }else{
            processDownRequest();
            processUpRequest();
        }
    }

    void processUpRequest(){
        while(!upqueue.empty()){
            Request upRequest = upqueue.top();
            upqueue.pop();
            this->currentFloor = upRequest.desiredFloor;
            cout<<"Processing up requests. Elevator stopped at floor " <<this->currentFloor<< "."<<endl;
        }
        if(!downqueue.empty()){
            this->direction = Direction::Down;
        }else{
            this->direction = Direction::Idle;
        }
    }

    void processDownRequest(){
        while(!downqueue.empty()){
            Request downRequest = downqueue.top();
            downqueue.pop();
            this->currentFloor = downRequest.desiredFloor;
            cout<<"Processing up requests. Elevator stopped at floor " <<this->currentFloor<< "."<<endl;
        }
        if(!upqueue.empty()){
            this->direction = Direction::Up;
        }else{
            this->direction = Direction::Idle;
        }
    }


};

int main(){
    Elevator elevator = Elevator(0);

        Request upRequest1 = Request(elevator.currentFloor, 5, Direction::Up, Location::Inside);
        Request upRequest2 = Request(elevator.currentFloor, 3, Direction::Up, Location::Inside);

        Request downRequest1 = Request(elevator.currentFloor, 1, Direction::Down, Location::Inside);
        Request downRequest2 = Request(elevator.currentFloor, 2, Direction::Down, Location::Inside);
        Request downRequest3 = Request(4, 0, Direction::Down, Location::Outside);

        // Two people inside of the elevator pressed button to go up to floor 5 and 3.
        elevator.sendUpRequest(upRequest1);
        elevator.sendUpRequest(upRequest2);

        // One person outside of the elevator at floor 4 pressed button to go down to floor 0
        elevator.sendDownRequest(downRequest3);

        // Two person inside of the elevator pressed button to go down to floor 1 and 2.
        elevator.sendDownRequest(downRequest1);
        elevator.sendDownRequest(downRequest2);


        elevator.run();
}