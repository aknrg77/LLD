#include<vector>
#include<queue>
#include<iostream>
#include<pair>
using namespace std;

class GameBoard{
  private:
  vector<vector<char>> board;
  int boardSize;
  queue<Player>nextTurn;

  public:
  GameBoard(int boardSize, vector<Player> players){
    this->boardSize = boardSize;
    this->nextTurn.push(players[0]);
    this->nextTurn.push(players[1]);

    board.resize((2*boardSize) -1);

    for(int i =0; i<board.size(); i++){
      board[i].resize((2*boardSize) -1);
    }

    initializeGameBoard();
  }

  private:
  void initializeGameBoard(){
    for(int i = 0; i<board.size(); i++){
      for(int j = 0; j<board[0].size(); j++){
        if(i%2==0 && j%2!=0) board[i][j] = '|';
        if(i%2!=0 && j%2==0) board[i][j] = '-';
        if(i%2!=0 && j%2 !=0) board[i][j] = '+';
      }
    }

    /*
        *  | |
          -+-+-
           | |
          -+-+-
           | |
        * */
  }

  void printBoard(){
    for(int i = 0; i<board.size(); i++){
      for(int j = 0; j<board[0].size(); j++){
        cout<<board[i][j]<<" ";
      }
      cout<<endl;
    }
  }

  public:
  void startGame(){
    int count = 0;
    while(true){
      count++;
      if(count >= (boardSize*boardSize -1)){
        cout<<"Match Draw";
        break;
      }

      Player player = this->nextTurn.front();
      nextTurn.pop();

      pair<int, int> position = getPostion(player);
      board[position.first][position.second] = player.getSymbol();
      cout<<"Board after the move";

      printBoard();

      if(count>= this->boardSize && checkEndGame(position.first, position.second)) break;
      nextTurn.push(player);
      }
    }
  }


  pair<int,int> getPosition(Player player){
    while(true){
      int row, col;
      cout<<"Enter row "<<endl;
      cin>>row;
      cout<<"Enter col"<<endl;
      cin>>col;

      if(notValidInput(row,col)){
        return {row,col};
      }
    }
  }

  bool notValidInput(int row, int col){
    if(row -1 > boardSize || row -1 <0 || col -1 < 0 || col -1 > boardSize){
      return false;
    }
    if(board[row -1][col -1]!=0){
      return false;
    }
    return true;
  }

  bool checkEndGame(int row, int col){
  
    string winString1 = "";
    string winString2 = "";
    string winStringPlayer = "";
    for(int i = 0; i<boardSize; i++){
      winString1+="X";
      winString2+="0";
    }

    for(int i =0; i<boardSize; i++){
      winStringPlayer += board[i][col-1];
    }

    if(winStringPlayer == winString1 || winStringPlayer == winString2){
      return true;
    }

    winStringPlayer = "";

    for(int j =0; j<boardSize; j++){
      winStringPlayer += board[row-1][j];
    }

    if(winStringPlayer == winString1 || winStringPlayer == winString2){
      return true;
    }

    winStringPlayer = "";

    for(int i = row-1, j = col-1; i>=0 , j>=0; i--, j--){
      winStringPlayer += board[i][j];
    }

    if(winStringPlayer == winString1 || winStringPlayer == winString2){
      return true;
    }

    winStringPlayer = "";
    for(int i = row-1, j = col-1; j >= 0 && i < boardSize; i++, j--){
      winStringPlayer += board[i][j];
    }

    if(winStringPlayer == winString1 || winStringPlayer == winString2){
      return true;
    }

    return false;

};

class Player{

};

int main(){

}