`std::shared_mutex` �� C++14 ��׼�����һ�ֻ������������ṩ��д���Ĺ��ܡ��������������߳�ͬʱ���ʹ�����Դ����д���߳�����Ҫ��ռ���ʡ��������ǳ��ʺ��ڶ���д�ٵĳ�����������߲������ܡ�

### ���ԣ�
- **��������Ȩ**������߳̿���ͬʱ��ȡ��������Ȩ������ȡ���ʣ���
- **��ռ����Ȩ**��д���߳���Ҫ��ȫ�Ķ�ռ����Ȩ����ʱ�����������̻߳�ȡ�κ����͵�����Ȩ��

### ��Ա������
- **lock()**����ȡ��ռ����Ȩ��
- **unlock()**���ͷŶ�ռ����Ȩ��
- **lock_shared()**����ȡ��������Ȩ��
- **unlock_shared()**���ͷŹ�������Ȩ��
- **try_lock()**�����Ի�ȡ��ռ����Ȩ�����ʧ�����������ء�
- **try_lock_for()**��������ָ����ʱ���ڻ�ȡ��ռ����Ȩ��
- **try_lock_until()**��������ָ����ʱ���ǰ��ȡ��ռ����Ȩ��
- **try_lock_shared()**�����Ի�ȡ��������Ȩ�����ʧ�����������ء�
- **try_lock_shared_for()**��������ָ����ʱ���ڻ�ȡ��������Ȩ��
- **try_lock_shared_until()**��������ָ����ʱ���ǰ��ȡ��������Ȩ��

### ʹ�ó�����
��һ����Դ������߳�Ƶ����ȡ����д���������ʱ��ʹ�� `std::shared_mutex` ������߳���Ĳ������ܡ����磬����ϵͳ��������Ϣ�ķ��ʡ�

### ʾ�����룺
```cpp
#include <iostream>
#include <shared_mutex>
#include <thread>

std::shared_mutex rw_mutex;
int shared_data = 0;

void reader() {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);
    // ��ȡ shared_data
    std::cout << "Read data: " << shared_data << std::endl;
}

void writer(int value) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);
    // д�� shared_data
    shared_data = value;
    std::cout << "Wrote data: " << shared_data << std::endl;
}

int main() {
    std::thread writers[2], readers[4];

    // ����д���߳�
    for (int i = 0; i < 2; ++i) {
        writers[i] = std::thread(writer, i + 1);
    }

    // ���������߳�
    for (int i = 0; i < 4; ++i) {
        readers[i] = std::thread(reader);
    }

    // �ȴ������߳����
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }
    for (int i = 0; i < 4; ++i) {
        readers[i].join();
    }

    return 0;
}
```
�����ʾ���У�������д���̺߳��ĸ������̡߳�д���߳�ʹ�� `std::unique_lock` ����ȡ��ռ����Ȩ���������߳�ʹ�� `std::shared_lock` ����ȡ�������Ȩ����������ȷ����д����ʱ�����������̸߳��ţ����ڶ�ȡʱ����Բ���ִ�С�

����������������Ӧstd::shared_lock<std::shared_mutex>����������д������Ӧstd::lock_guard <std::shared_mutex>��std::unique_lock<std::shared_mutex> 
