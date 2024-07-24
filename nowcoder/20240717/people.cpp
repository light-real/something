#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

class People
{
public:
    People(string cname, int cage, double cheight) : name(cname), age(cage), height(cheight), father(nullptr), mather(nullptr)
    {
    }

    ~People()
    {
    }

    string getName()
    {
        return name;
    }

    int getAge()
    {
        return age;
    }

    double getHeight()
    {
        return height;
    }

    People *getFather()
    {
        return father;
    }

    People *getMather()
    {
        return mather;
    }

private:
    string name;
    int age;
    double height;
    People *father;
    People *mather;
    unordered_map<string, People*> relative;
};

void printPeople(People *people)
{
    cout << "name : " << people->getName() << endl
         << "age : " << people->getAge() << endl
         << "height : " << people->getHeight() << endl;
}

int main()
{
    People *tom = new People("tom", 18, 180.1);
    printPeople(tom);
    delete tom;
    return 0;
}
