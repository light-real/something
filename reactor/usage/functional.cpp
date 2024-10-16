#include <iostream>
#include <functional>
#include <memory>
using namespace std;

class Myfunc
{
public:
    void equal(std::function<int(int, int)> fn)
    {
        functioncb = fn;
    }
    std::function<int(int, int)> functioncb;
};

int add(int a, int b)
{
    return a + b;
}
int main()
{
    // std::unique_ptr<Myfunc> func = std::make_unique<Myfunc>();
    Myfunc *func = new Myfunc();
    func->equal(add);
    cout << func->functioncb(3, 4) << endl;
    return 0;
}