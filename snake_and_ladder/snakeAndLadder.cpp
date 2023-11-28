#include <bits/stdc++.h>
using namespace std;

class Board{
    int start;
    int end;
    int size;

    public:
    void getBoard(int size){
        this->start = 1;
        this->end = start + size -1;
        this->size = size;
    }

    int getBoardSize(){
        return this->size;
    }

    int getEnd(){
        return this->end;
    }
};

class Snake{
    int head;
    int tail;

    public:
    Snake(int head, int tail){
        this->head = head;
        this->tail = tail;
    }

    int getHead(){
        return this->head;
    }

    int getTail(){
        return this->tail;
    }
};

class Ladder{
    int start;
    int end;

    public:
    Ladder(int start, int end){
        this->start = start;
        this->end = end;
    }

    int getStart(){
        return this->start;
    }

    int getEnd(){
        return this->end;
    }
};

class Player{
    string name;
    int pos;
    bool won;

    public:
    Player(string name){
        this->name = name;
        this->pos = 0;
        this->won = false;
    }

    int getPosition(){
        return this->pos;
    }

    string getName(){
        return this->name;
    }


    void setPosition(int pos){
        this->pos = pos;
    }

    void setWon(bool won){
        this->won = won;
    }
};

class Dice{
    int maxValue;
    int minValue;
    int currentValue;
    public:
    Dice(int maxValue, int minValue, int currentValue){
        this->maxValue = maxValue;
        this->minValue = minValue;
        this->currentValue = currentValue;
    }    
    int roll(){
        int range = maxValue - minValue + 1;
        return rand() % range + minValue;
    }
};

class Game{
    int numberOfSnakes;
    int numberOfLadders;
    int boardSize;

    queue<Player> players;
    vector<Snake> snakes;
    vector<Ladder> ladders;
    Dice dice = Dice(1, 6, 2);
    Board board;
    public:
    Game(int numberOfSnakes, int numberOfLadders, int boardSize){
        this->numberOfLadders = numberOfLadders;
        this->numberOfSnakes = numberOfSnakes;
        this->boardSize = boardSize;
        snakes.resize(numberOfSnakes);
        ladders.resize(numberOfLadders);
        board.getBoard(boardSize);
        initBoard();
    }

    void initBoard(){

        set<pair<int,int>> slSet;
        for(int i = 0; i<numberOfSnakes; i++){
            while(true){
                int range = board.getBoardSize() -1;
                int snakeHead = rand() % range + 1;
                int snakeTail = rand() % range + 1;

                if(snakeTail >= snakeHead){
                    continue;
                }

                if(slSet.find({snakeHead, snakeTail})==slSet.end()){
                    slSet.insert({snakeHead, snakeTail});
                    Snake snakeObj(snakeHead, snakeTail);
                    snakes.push_back(snakeObj);
                    break;
                }
                
            }
        }

        for(int i = 0; i<numberOfLadders; i++){
            while(true){
                int range = board.getBoardSize() -1;
                int ladderStart = rand() % range + 1;
                int ladderEnd = rand() % range + 1;

                if(ladderEnd <= ladderStart){
                    continue;
                }

                if(slSet.find({ladderStart, ladderEnd})==slSet.end()){
                    slSet.insert({ladderStart, ladderEnd});
                    Ladder ladderObj(ladderStart, ladderEnd);
                    ladders.push_back(ladderObj);
                    break;
                }
                
            }
        }

    }

    void addPlayer(Player player){
        players.push(player);
    }

    void playGame(){
        while(true){
            Player player = players.front();
            players.pop();
            int val = dice.roll();
            int newPosition = player.getPosition() + val;
            if (newPosition > board.getEnd()) {
                player.setPosition(player.getPosition());
                players.push(player);
            } else {
                player.setPosition(getNewPosition(newPosition));
                if (player.getPosition() == board.getEnd()) {
                    player.setWon(true);
                    cout<<"Player " << player.getName() << " Won." <<endl;
                } else {
                    cout<<"Setting " << player.getName() << "'s new position to " << player.getPosition() <<endl;
                    players.push(player);
                }
            }

            if(players.size() < 2){
                break;
            }
        }
    }

    int getNewPosition(int newPosition) {
        for (Snake snake : snakes) {
            if (snake.getHead() == newPosition) {
                cout<<"Snake Bit";
                return snake.getTail();
            }
        }
        for (Ladder ladder : ladders) {
            if (ladder.getStart() == newPosition) {
                cout<<"Climbed ladder";
                return ladder.getEnd();
            }
        }
        return newPosition;
    }

};

int main(){
    Game game(5,5,100);

}
