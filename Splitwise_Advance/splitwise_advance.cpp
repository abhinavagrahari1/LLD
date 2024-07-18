#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class User
{
private:
    int user_id;
    string name;
    string email;
    string mobile_number;
    map<int, float> balance;

public:
    User(int id, string name, string email, string mobile_number)
    {
        user_id = id;
        this->name = name;
        this->email = email;
        this->mobile_number = mobile_number;
    }

    void addNewFriend(int friend_id)
    {
        balance[friend_id] = 0;
    }

    void updateBalance(int friend_id, float amount)
    {
        balance[friend_id] += amount;
    }

    int getUserId()
    {
        return user_id;
    }

    map<int, float> returnBalance()
    {
        return balance;
    }

    float returnFriendBalance(int friend_id)
    {
        return balance[friend_id];
    }

    string getUserName(){
        return name;
    }
};

enum class ExpenseType
{
    EQUAL,
    EXACT,
    PERCENT
};

class ExpenseManager
{
private:
    vector<User> user_array;

public:
    void addUser(int user_id, string name, string email, string mobile_number)
    {
        for (int i = 0; i < user_array.size(); i++)
        {
            user_array[i].addNewFriend(user_id);
        }
        User U1(user_id, name, email, mobile_number);
        user_array.push_back(U1);
    }

    void addExpense(int payer_id, float amount, int number_of_friends, vector<int> users, ExpenseType type, vector<float> amounts)
    {
        if (type == ExpenseType::EQUAL)
        {
            float final_amount = amount / number_of_friends;

            for (auto &x : user_array)
            {
                if (x.getUserId() == payer_id)
                {
                    for (auto &y : users)
                    {
                        x.updateBalance(y, final_amount);
                    }
                }
            }

            for (auto &x : user_array)
            {
                for (int i = 0; i < number_of_friends; i++)
                {
                    if (x.getUserId() == users[i])
                    {
                        x.updateBalance(payer_id, -final_amount);
                    }
                }
            }
        }

        if (type == ExpenseType::EXACT)
        {
            for (auto &x : user_array)
            {
                if (x.getUserId() == payer_id)
                {
                    for (int i = 0; i < number_of_friends; i++)
                    {
                        x.updateBalance(users[i], amounts[i]);
                    }
                }
            }

            for (auto &x : user_array)
            {
                for (int i = 0; i < number_of_friends; i++)
                {
                    if (x.getUserId() == users[i])
                    {
                        x.updateBalance(payer_id, -amounts[i]);
                    }
                }
            }
        }

        if (type == ExpenseType::PERCENT)
        {
            // convert to percent
            for (int i = 0; i < amounts.size(); i++)
            {
                amounts[i] = amount * (amounts[i] / 100);
            }

            for (auto &x : user_array)
            {
                if (x.getUserId() == payer_id)
                {
                    for (int i = 0; i < number_of_friends; i++)
                    {
                        x.updateBalance(users[i], amounts[i]);
                    }
                }
            }

            for (auto &x : user_array)
            {
                for (int i = 0; i < number_of_friends; i++)
                {
                    if (x.getUserId() == users[i])
                    {
                        x.updateBalance(payer_id, -amounts[i]);
                    }
                }
            }
        }
    }

    void printAllBalances(int user_id)
    {
        for (auto &x : user_array)
        {
            if (x.getUserId() == user_id)
            {
                map<int, float> m1 = x.returnBalance();
                for (auto &y : m1)
                {
                    cout << endl
                         << "Friend " << y.first << " owes you:" << y.second;
                }
            }
        }
    }

    void printUserBalance(int user_id, int friend_id)
    {
        for (auto &x : user_array)
        {
            if (x.getUserId() == user_id)
            {
                cout << endl
                     << "Your friend " << friend_id << " owes you:" << x.returnFriendBalance(friend_id);
            }
        }
    }

    void printAllUsers(){
        for(auto& x: user_array){
            cout<<endl<<"User "<<x.getUserId()<<": "<<x.getUserName() <<endl;
        }
    }
};

int main()
{
    ExpenseManager manager;
    manager.addUser(1, "Abhinav", "email", "123");
    manager.addUser(2, "Cuppa", "gmail", "234");
    manager.addUser(3, "Cuppachino", "gmail", "234");
    manager.addUser(4, "Moca", "gmail", "234");
    manager.addUser(5, "Mocachino", "gmail", "234");
    manager.printAllUsers();

    manager.addExpense(1, 1200, 4, {2,3,4,5}, ExpenseType::EQUAL, {});

    cout<<endl<<"=========================================="<<endl;

    manager.printAllBalances(1);

    cout<<endl<<"=========================================="<<endl;

    manager.addExpense(2, 1500, 4, {1,3,4,5}, ExpenseType::EXACT, {100,300,600,500});

    manager.printAllBalances(1);

    cout<<endl<<"=========================================="<<endl;

    manager.printAllBalances(2);

    cout<<endl<<"=========================================="<<endl;

    manager.printUserBalance(2,1);

    cout<<endl<<"=========================================="<<endl;

    return 0;
}