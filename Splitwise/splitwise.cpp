#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

class User{
    private:
        int id;
        string name;
        string phone;
        map<int, float> user_balance;
    public:
        User(int id, string name, string phone){
            this->id = id;
            this->name = name;
            this->phone = phone;
        }

        void addFriends(int id){
            user_balance[id] = 0.0;
        }

        int returnId(){
            return id;
        }

        void updateUserBalance(int id, float amount){
            user_balance.insert_or_assign(id, amount);
        }

        void returnBalance(int payer_id, int payee_id){
            cout<<endl<<"User Id:"<<payee_id<<" owes user:"<< payer_id<<": "<<user_balance[payee_id]<<endl;
        }

        void returnAllUserBalances(){
            for(auto& x: user_balance){
                cout<<endl<<"User:"<<x.first<<" owes you:"<<x.second<<endl;
            }
        }

        

};

class Manager{
    private:
        vector<User> user_array;
    public:
        void addUser(int id, string name, string phone){
            User U1(id, name, phone);
            if(!user_array.empty()){
                for(auto& x: user_array ){
                    x.addFriends(id);
                }
            }
            user_array.push_back(U1);
        }


        void addExpense(int payer_id, int amount, int payee_id, string type, float to_pay){
            for( auto& x: user_array){
                if(x.returnId() == payer_id){
                    x.updateUserBalance(payee_id, to_pay);
                    cout<<endl<<"Succesful."<<endl;
                    x.returnBalance(x.returnId(), payee_id);
                }
            }
        }

        void checkBalance(int payer_id, int payee_id){
            for( auto& x: user_array){
                if(x.returnId() == payer_id){
                    x.returnBalance(x.returnId(), payee_id);
                }
            }
        }

        void getAllUsers(){
            for( auto& x: user_array){
                cout<<endl<<"User Id:"<<x.returnId()<<endl;
            }
        }

        void printUserBalances(int id){
            for(auto& x: user_array){
                if(x.returnId() ==id){
                    x.returnAllUserBalances();
                }
            }
        }



};

int main(){
    Manager M1;

    M1.addUser(1, "Abhinav", "123");
    M1.addUser(2, "Abhi", "123");
    M1.getAllUsers();
    M1.addExpense(1, 1200, 2,"LATER", 1200.0);
    M1.printUserBalances(1);
    M1.checkBalance(1,2);

    return 0;
}