`std::shared_mutex` 是 C++14 标准引入的一种互斥量，用于提供读写锁的功能。它允许多个读者线程同时访问共享资源，但写者线程则需要独占访问。这种锁非常适合于读多写少的场景，可以提高并发性能。

### 特性：
- **共享所有权**：多个线程可以同时获取共享所有权（即读取访问）。
- **独占所有权**：写者线程需要完全的独占所有权，此时不允许其他线程获取任何类型的所有权。

### 成员函数：
- **lock()**：获取独占所有权。
- **unlock()**：释放独占所有权。
- **lock_shared()**：获取共享所有权。
- **unlock_shared()**：释放共享所有权。
- **try_lock()**：尝试获取独占所有权，如果失败则立即返回。
- **try_lock_for()**：尝试在指定的时间内获取独占所有权。
- **try_lock_until()**：尝试在指定的时间点前获取独占所有权。
- **try_lock_shared()**：尝试获取共享所有权，如果失败则立即返回。
- **try_lock_shared_for()**：尝试在指定的时间内获取共享所有权。
- **try_lock_shared_until()**：尝试在指定的时间点前获取共享所有权。

### 使用场景：
当一个资源被多个线程频繁读取，但写入操作较少时，使用 `std::shared_mutex` 可以提高程序的并发性能。例如，缓存系统或配置信息的访问。

### 示例代码：
```cpp
#include <iostream>
#include <shared_mutex>
#include <thread>

std::shared_mutex rw_mutex;
int shared_data = 0;

void reader() {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);
    // 读取 shared_data
    std::cout << "Read data: " << shared_data << std::endl;
}

void writer(int value) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);
    // 写入 shared_data
    shared_data = value;
    std::cout << "Wrote data: " << shared_data << std::endl;
}

int main() {
    std::thread writers[2], readers[4];

    // 启动写者线程
    for (int i = 0; i < 2; ++i) {
        writers[i] = std::thread(writer, i + 1);
    }

    // 启动读者线程
    for (int i = 0; i < 4; ++i) {
        readers[i] = std::thread(reader);
    }

    // 等待所有线程完成
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }
    for (int i = 0; i < 4; ++i) {
        readers[i].join();
    }

    return 0;
}
```
在这个示例中，有两个写者线程和四个读者线程。写者线程使用 `std::unique_lock` 来获取独占访问权，而读者线程使用 `std::shared_lock` 来获取共享访问权。这样可以确保在写操作时不会有其他线程干扰，而在读取时则可以并发执行。

共享锁即读锁，对应std::shared_lock<std::shared_mutex>；排他锁即写锁，对应std::lock_guard <std::shared_mutex>和std::unique_lock<std::shared_mutex> 
