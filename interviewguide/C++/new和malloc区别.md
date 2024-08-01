# 1.&nbsp;new/delete和malloc/free
都用于内存的动态申请和释放
new/delete支持重载，malloc和free支持覆盖
重载new和delete
```c++
    // 重载全局 new 运算符
    void* operator new(size_t size) {
        void* ptr = std::malloc(size);
        std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
        return ptr;
    }

    // 重载全局 delete 运算符
    void operator delete(void* ptr) noexcept {
        std::cout << "Freeing memory at " << ptr << std::endl;
        std::free(ptr);
    }

    int main() {
        // 使用重载的 new 和 delete
        int* ptr = new int(10);
        std::cout << "Value: " << *ptr << std::endl;

        delete ptr;

        return 0;
    }
```

覆盖malloc和free
```c++
    // 覆盖 malloc 函数
    void* malloc(size_t size) {
        void* ptr = (void*)malloc(size);
        printf("Allocated %zu bytes at %p\n", size, ptr);
        return ptr;
    }

    // 覆盖 free 函数
    void free(void* ptr) {
        printf("Freeing memory at %p\n", ptr);
        free(ptr);
    }

    int main() {
        // 使用自定义的 malloc 和 free
        int* ptr = (int*)malloc(sizeof(int) * 10);
        if (ptr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        for (int i = 0; i < 10; i++) {
            ptr[i] = i;
        }

        free(ptr);

        return 0;
    }
```
## new/delete

### new
new是类型安全的，不需要库文件支持
**new是封装了malloc，直接free不会报错，但是这只是释放内存，不会析构对象**
new用户内存的动态申请，自动计算需要分配空间的大小，new会调用operator new的标准库函数，在内存中开辟一块足够大的空间，同时会调用对象的构造函数
**new的实现过程：首先调用名为operator new的标准库函数，分配足够大的原始的类型化的内存，以保存指定类型的一个对象；接下来运行该类型的一个构造函数，用指定初始化构造对象；最后返回指向新分配并构造后的对象的指针**

### delete
**delete的实现过程：对指针指向的对象运行适当的析构函数；然后调用名为operator delete的标准库函数释放该对象所用内存**

```c++
    class Myclass
    {
        Myclass(){}
        ~Myclass(){}
    };

    int main()
    {
        Myclass *mc = new Myclass();
        delete mc;
        return 0;
    }

```

## malloc/free
malloc不是类型安全的，并且分配的内存需要自己计算
malloc和free返回的都是void类型的指针，必须自己进行类型转换

```c++
    int main() {
        // 使用 malloc 分配内存
        int* ptr = (int*)malloc(sizeof(int) * 10);
        if (ptr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        // 使用分配的内存
        for (int i = 0; i < 10; i++) {
            ptr[i] = i;
        }

        // 释放内存
        free(ptr);

        return 0;
    }
```

## 为什么有了malloc/free还需要new/delete
在对非基本数据类型的对象使用的时候，对象创建的时候还需要执行构造函数，销毁的时候要执行析构函数，而malloc和free是库函数，是已编译的代码，不能把构造函数和析构函数的功能强加给malloc和free

## 