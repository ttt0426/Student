# 学生信息管理系统

C++ 面向对象课程设计项目，基于控制台的学生信息管理平台。

## 功能特性

- 学生信息的增删改查
- 多维度成绩排序（总分/单科，升序/降序）
- 数据合法性校验（学号、年龄、成绩范围等）
- 文件持久化（覆盖/追加双模式）
- 程序启动自动加载数据

## 技术要点

- 面向对象封装：Student 类封装属性与行为，私有成员+公有接口实现访问控制
- 数据一致性：修改单科成绩自动触发 calculateTotal() 重算总分
- 防御式编程：文件解析采用 istringstream + try-catch 异常捕获，自动隔离非法记录
- RAII 资源管理：文件流对象自动析构关闭，避免资源泄漏
- STL 应用：基于 std::sort + 自定义比较函数实现多维度排序

## 项目结构

当前实现（单文件）：

- 学生信息管理系统.cpp
  - Student 类：封装属性、数据校验、总分联动计算
  - 比较函数集（8个）：支持总分/单科 × 升序/降序
  - 功能函数集（9个）：增删改查、文件读写、菜单交互
  - main 函数：程序入口与流程控制
- studentInfo.txt：数据存储文件



## 核心实现

总分联动机制：

    bool setMathScore(int score) {
        if (isValidScore(score)) {
            math = score;
            calculateTotal();
            return true;
        }
        return false;
    }

文件加载：

    bool fromFileString(const string& line) {
        istringstream iss(line);
        if (!isValidId(id) || !isValidAge(ageVal)) {
            return false;
        }
    }

完整代码见 学生信息管理系统.cpp

