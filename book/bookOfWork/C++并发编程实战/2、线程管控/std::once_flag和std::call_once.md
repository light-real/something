# std::call_once

`std::once_flag` 是 C++11 中引入的线程安全辅助类，与 `std::call_once` 函数配合使用，确保某个函数在多线程环境中只执行一次。它通常用于实现单例模式或进行延迟初始化等场景，以保证线程安全 。

### 使用方法：
1. **声明 `std::once_flag` 对象**：通常作为静态成员变量或全局变量，以便在多个线程之间共享。
2. **调用 `std::call_once` 函数**：将 `std::once_flag` 对象作为参数传递给 `std::call_once`，以及需要执行的函数或可调用对象（例如 lambda 表达式）。

### 示例代码：
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::once_flag flag;

void do_something() {
    std::call_once(flag, []() {
        std::cout << "do_something() called once" << std::endl;
    });
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread t1(do_something);
    std::thread t2(do_something);
    
    t1.join();
    t2.join();
    
    return 0;
}
```
在这个示例中，无论 `do_something` 函数被多少个线程调用，`std::call_once` 确保 lambda 表达式只执行一次，并打印出“do_something() called once”。随后，每个线程都会打印自己的线程 ID 。

### 注意事项：
- `std::once_flag` 对象既不可复制也不可移动，确保了其唯一性。
- `std::call_once` 可用于确保任何可调用对象（包括普通函数、lambda 表达式、函数对象等）只执行一次。
- 如果 `std::call_once` 被多次调用传入相同的 `std::once_flag` 对象，只有一个调用会实际执行传入的函数，其他调用将等待该函数执行完毕 。

`std::once_flag` 结构体通过提供同步机制来确保特定任务仅在首次执行时被执行一次，无论有多少个线程尝试执行它。它通过提供一个同步机制，允许线程等待特定任务被执行，并在任务被第一次执行后将其标记为已完成。`std::once_flag` 结构体具有删除的拷贝构造函数和赋值运算符，这意味着它不能从另一个 `std::once_flag` 实例中拷贝或赋值。在内部，`std::once_flag` 结构体包含一个 `_M_once` 成员变量，类型为 `__gthread_once_t`，它由底层线程库（在本例中为 gthreads）用于处理目标任务的同步和执行。`std::call_once` 函数是 `std::once_flag` 的友元函数，它接受一个 `std::once_flag` 实例以及一个目标函数和其参数。它确保目标函数仅被执行一次，并对调用它的所有线程进行同步访问 。

在 C++11 中，`std::call_once` 函数和 `std::once_flag` 结构体被引入，用于确保在多线程环境中某个函数只被调用一次。这两者通常用于实现线程安全的单例模式或延迟初始化资源。`std::once_flag` 是一个不可复制和移动的类型，它通过内部状态来确保与之关联的函数只会被执行一次。当 `std::call_once` 被调用时，它会检查 `std::once_flag` 的状态，如果状态表明函数尚未执行，`std::call_once` 将执行提供的函数或可调用对象，然后更新标志位以反映函数已被执行。如果 `std::call_once` 被多次调用，且传入的是同一个 `std::once_flag` 对象，只有一个调用会实际执行函数，其他调用将等待或跳过执行 。

`std::once_flag` 是 C++11 中引入的线程安全辅助类，用于 `std::call_once` 函数。它允许多个 `std::call_once` 调用相互协调，确保只有一个调用实际运行完成。这个类不可复制亦不可移动。使用 `std::once_flag` 可以避免在多线程环境下多次执行同一个函数，从而提高程序性能和正确性 。

总的来说，`std::once_flag` 和 `std::call_once` 的使用是为了在多线程环境中保证代码块或函数只执行一次，从而避免潜在的竞态条件和线程安全问题。这通常用于单例模式的实现、资源的懒加载初始化等场景。
