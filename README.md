# SingletonDemo

这是一个 C++ 单例模式演示项目，包含三种常见实现方式：

- 饿汉式单例
- 懒汉式单例
- Meyers 单例
- 双重检查锁单例（DCL）用于对照测试

## 项目结构

- `include/`：头文件定义
- `src/`：实现文件和测试入口
- `CMakeLists.txt`：CMake 构建配置

## 编译方式

在项目根目录执行：

```bash
cmake -S . -B build
cmake --build build
```

如果使用 MinGW / GCC 直接编译，也可以执行：

```bash
g++ -std=c++17 src/main.cpp src/EagerSingleton.cpp src/LazySingleton.cpp src/MeyersSingleton.cpp -Iinclude -o app.exe
```

## 运行方式

```bash
./app.exe
```

或者在 Windows PowerShell 中：

```powershell
.\app.exe
```

## 主要测试内容

程序入口 `src/main.cpp` 中包含以下测试：

1. 饿汉式单例测试
2. 饿汉式单例多线程安全性测试
3. 懒汉式无锁多线程测试
4. 双重检查锁单例测试
5. Meyers 单例多线程安全性测试

## 结论

- 饿汉式单例：线程安全
- Meyers 单例：线程安全
- 无锁懒汉式：存在竞态条件，不建议直接使用
- 双重检查锁单例：线程安全的懒汉式实现
