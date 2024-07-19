#include<iostream>
#include<string>
#include<vector>


using namespace std;

class User{
    private:
        int user_id;
        int score;
    public:
        User(int user_id){
            this->user_id =user_id;
            score=0;
        }

        int getUserId(){
            return user_id;
        }

        int getScore(){
            return score;
        }

        void upateScore(int dice){
            score = dice;
            if(score < 0){
                score =0;
            }

            if(score>100){
                score =100;
            }
        }
};

class Board{
    private:
        vector<User> player_array;
        std::vector<int> snake_ladder_array;
    public:
        Board(){
            for(int i=0; i<100;i++){
                snake_ladder_array.push_back(0);
            }
        }
        void addUser(int player_id){
            User u1(player_id);
            player_array.push_back(u1);
        }

        void addLadder(int number, int value){
            snake_ladder_array[number] +=value;
        }

        void addSnake(int number, int value){
            snake_ladder_array[number] -= value;
        }

        bool checkWinner(){
            for( auto& x: player_array){
                    if(x.getScore()>=18){
                        cout<<endl<<"Player:"<<x.getUserId()<<" wins.";
                        return true;
                    }
            }

            return false;
        }

        void updateScore(int user_id, int score){
            if(score<=0 || score>=7){
                cout<< endl<<"Bad input. Play Again."<<endl;
                return;
            }

            for(int i=0; i<player_array.size(); i++){
                if(player_array[i].getUserId() == user_id){
                    int curr_Score = player_array[i].getScore()+ score;
                    cout<<"..."<<curr_Score;
                    curr_Score += snake_ladder_array[curr_Score];
                    cout<<"//"<<curr_Score;
                    player_array[i].upateScore(curr_Score);
                    cout<<endl<<"Player:"<<player_array[i].getUserId()<<" Current score:"<<player_array[i].getScore();
                }
            }
        }

};

int main(){
    Board boardManager;
    bool winner = false;
    vector<int> players;

    boardManager.addUser(1);
    players.push_back(1);
    boardManager.addUser(2);
    players.push_back(2);


    boardManager.addSnake(4, 1);
    boardManager.addLadder(12, 5);
    int i=1;

    while(!boardManager.checkWinner()){
        cout<<endl<<"Player"<<players[i-1]<<" play your move:";
        int move;
        cin>>move;
        boardManager.updateScore(i, move);
        if( i+1 > players.size()){
            i=1;
        }else{
            i++;
        }
    }

    return 0;
}