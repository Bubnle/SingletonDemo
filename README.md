# SingletonDemo

这是一个用于演示和验证单例模式线程安全性的 C++ 项目，重点关注“多个线程同时获取单例实例时，是否会创建多个对象”。

## 1. 项目内容

本项目包含以下实现：

- 饿汉式单例：EagerSingleton
- 懒汉式单例：LazySingleton
- Meyers 单例：MeyersSingleton
- 安全对照单例：SafeSingleton

其中，`SafeSingleton` 是用于对照测试的线程安全版本，用于说明在多线程环境下如何保证实例唯一。

## 2. 项目结构

- `include/`：头文件声明
- `src/`：实现文件和测试入口
- `CMakeLists.txt`：构建配置文件
- `README.md`：项目说明

## 3. 编译方法

### 方式一：CMake

在项目根目录执行：

```bash
cmake -S . -B build
cmake --build build
```

### 方式二：直接使用 g++

```bash
g++ -std=c++17 src/main.cpp src/EagerSingleton.cpp src/LazySingleton.cpp src/MeyersSingleton.cpp src/SageSingleton.cpp -Iinclude -o app.exe
```

## 4. 运行方式

Linux / macOS：

```bash
./app.exe
```

Windows PowerShell：

```powershell
.\app.exe
```

## 5. 测试重点

程序入口在 `src/main.cpp`，测试内容包括：

1. 饿汉式单例是否始终返回同一个对象
2. 饿汉式单例在多线程下是否安全
3. 懒汉式单例无锁版本在多线程下的行为
4. 安全对照单例是否能保证线程安全
5. Meyers 单例在多线程下是否仍保持唯一实例

## 6. 线程安全说明

本实验关注的核心问题不是 `mdata` 这类成员变量的原子性，而是：

- 多个线程同时获取单例实例时，是否会创建多个对象
- 是否仍然满足单例模式的唯一性要求

因此，测试的核心判断依据是：不同线程拿到的实例地址是否相同。

如果两个线程得到的地址相同，则说明实现保持了单例；如果不同，则说明存在线程安全问题。

## 7. 结论

- 饿汉式单例：线程安全
- Meyers 单例：线程安全
- 无锁懒汉式：存在竞态条件，不安全
- 安全对照单例（SafeSingleton）：线程安全，适合作为对照实现
