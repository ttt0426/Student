#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <sstream>
using namespace std;

// Student类：封装学生的所有属性和行为
class Student {
private:
    string id;         // 学号（8位数字）
    string name;       // 姓名（支持包含空格）
    string gender;     // 性别（男/女/未知）
    int age;           // 年龄（6-40岁）
    string className;  // 班级
    int math;          // 数学成绩（0-100）
    int chinese;       // 语文成绩（0-100）
    int english;       // 英语成绩（0-100）
    int totalScore;    // 总分（自动计算）

    // 私有：验证学号合法性（内部使用，外部不可访问）
    bool isValidId(const string& id) const {
        // 学号必须是8位
        if (id.length() != 8) return false;
        // 学号必须全为数字
        for (char c : id) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    // 私有：验证年龄合法性
    bool isValidAge(int age) const {
        return age >= 6 && age <= 40; // 年龄范围6-40岁
    }

    // 私有：验证成绩合法性（0-100分）
    bool isValidScore(int score) const {
        return score >= 0 && score <= 100;
    }

    // 私有：验证性别合法性
    bool isValidGender(const string& gender) const {
        return gender == "男" || gender == "女" || gender == "未知";
    }

    // 私有：计算总分（内部调用，自动更新总分）
    void calculateTotal() {
        totalScore = math + chinese + english; // 总分=数学+语文+英语
    }

public:
    // 无参构造函数：初始化所有数值型成员为0
    Student() : age(0), math(0), chinese(0), english(0), totalScore(0) {}

    // 有参构造函数：初始化学生信息并计算总分
    Student(const string& id, const string& name, const string& gender, int age,
        const string& className, int math, int chinese, int english) {
        setId(id);          // 设置学号
        setName(name);      // 设置姓名
        setGender(gender);  // 设置性别
        setAge(age);        // 设置年龄
        setClassName(className); // 设置班级
        setMathScore(math); // 设置数学成绩
        setChineseScore(chinese); // 设置语文成绩
        setEnglishScore(english); // 设置英语成绩
        calculateTotal();   // 确保总分计算正确
    }

    // 公有：设置学号（带合法性验证，返回是否设置成功）
    bool setId(const string& newId) {
        if (isValidId(newId)) { // 验证通过才赋值
            id = newId;
            return true;
        }
        return false; // 验证失败返回false
    }

    // 公有：设置姓名（无验证，直接赋值）
    void setName(const string& newName) {
        name = newName;
    }

    // 公有：设置性别（带合法性验证，返回是否设置成功）
    bool setGender(const string& newGender) {
        if (isValidGender(newGender)) { // 验证通过才赋值
            gender = newGender;
            return true;
        }
        return false;
    }

    // 公有：设置年龄（带合法性验证，返回是否设置成功）
    bool setAge(int newAge) {
        if (isValidAge(newAge)) { // 验证通过才赋值
            age = newAge;
            return true;
        }
        return false;
    }

    // 公有：设置班级（无验证，直接赋值）
    void setClassName(const string& newClass) {
        className = newClass;
    }

    // 公有：设置数学成绩（带验证+更新总分，返回是否设置成功）
    bool setMathScore(int score) {
        if (isValidScore(score)) { // 成绩验证通过
            math = score;
            calculateTotal();      // 重新计算总分
            return true;
        }
        return false;
    }

    // 公有：设置语文成绩（带验证+更新总分，返回是否设置成功）
    bool setChineseScore(int score) {
        if (isValidScore(score)) {
            chinese = score;
            calculateTotal();
            return true;
        }
        return false;
    }

    // 公有：设置英语成绩（带验证+更新总分，返回是否设置成功）
    bool setEnglishScore(int score) {
        if (isValidScore(score)) {
            english = score;
            calculateTotal();
            return true;
        }
        return false;
    }

    // 公有：获取学号
    string getId() const { return id; }
    // 公有：获取姓名
    string getName() const { return name; }
    // 公有：获取性别
    string getGender() const { return gender; }
    // 公有：获取年龄
    int getAge() const { return age; }
    // 公有：获取班级
    string getClassName() const { return className; }
    // 公有：获取数学成绩
    int getMathScore() const { return math; }
    // 公有：获取语文成绩
    int getChineseScore() const { return chinese; }
    // 公有：获取英语成绩
    int getEnglishScore() const { return english; }
    // 公有：获取总分
    int getTotalScore() const { return totalScore; }

    // 公有：展示学生完整信息
    void showInfo() const {
        cout << "学号：" << id
            << " | 姓名：" << name
            << " | 性别：" << gender
            << " | 年龄：" << age
            << " | 班级：" << className
            << " | 数学：" << math
            << " | 语文：" << chinese
            << " | 英语：" << english
            << " | 总分：" << totalScore << endl;
    }

    // 公有：转换为文件存储字符串（用于写入文件）
    string toFileString() const {
        // 按空格分隔各字段，方便读取解析
        return id + " " + name + " " + gender + " " + to_string(age) + " " +
            className + " " + to_string(math) + " " + to_string(chinese) + " " +
            to_string(english) + " " + to_string(totalScore);
    }

    // 公有：从文件字符串解析为学生信息（用于读取文件）
    bool fromFileString(const string& line) {
        istringstream iss(line); // 将字符串转为输入流
        string ageStr, mathStr, chineseStr, englishStr, totalStr;
        // 按空格分割字符串并读取到对应变量
        if (!(iss >> id >> name >> gender >> ageStr >> className >> mathStr >> chineseStr >> englishStr >> totalStr)) {
            return false; // 解析失败返回false
        }
        // 字符串转数值型并验证
        int ageVal, mathVal, chineseVal, englishVal;
        try {
            // 字符串转整数（捕获转换异常）
            ageVal = stoi(ageStr);
            mathVal = stoi(mathStr);
            chineseVal = stoi(chineseStr);
            englishVal = stoi(englishStr);
        }
        catch (...) { // 转换失败返回false
            return false;
        }
        // 验证所有字段合法性
        if (!isValidId(id) || !isValidGender(gender) || !isValidAge(ageVal) ||
            !isValidScore(mathVal) || !isValidScore(chineseVal) || !isValidScore(englishVal)) {
            return false;
        }
        // 验证通过后赋值
        age = ageVal;
        math = mathVal;
        chinese = chineseVal;
        english = englishVal;
        calculateTotal(); // 重新计算总分
        return true;      // 解析成功返回true
    }
};

// 全局变量：存储所有学生信息的动态数组
vector<Student> studentList;
// 全局常量：学生信息存储文件路径
const string FILE_PATH = "studentInfo.txt";

// 工具函数：暂停程序并清空控制台（提升用户体验）
void pauseAndClear() {
    cout << "\n按任意键继续...";
    // 忽略输入缓冲区中所有字符直到换行（清空残留输入）
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); // 等待用户按键
    system("cls"); // Windows清空控制台
}

// 界面函数：显示主菜单
void showMainMenu() {
    cout << "\n============ 学生信息管理系统 ============\n";
    cout << "1. 添加学生信息\n";
    cout << "2. 查询学生信息（学号/姓名）\n";
    cout << "3. 删除学生信息（学号精确匹配）\n";
    cout << "4. 修改学生信息\n";
    cout << "5. 成绩排序（总分/单科）\n";
    cout << "6. 显示所有学生信息\n";
    cout << "7. 保存数据到文件（覆盖模式）\n";
    cout << "8. 保存数据到文件（追加模式）\n";
    cout << "9. 从文件加载数据\n";
    cout << "0. 退出系统\n";
    cout << "============================================\n";
}

// 排序比较函数：按总分降序（从高到低）
bool compareByTotalDesc(const Student& a, const Student& b) {
    return a.getTotalScore() > b.getTotalScore();
}
// 排序比较函数：按总分升序（从低到高）
bool compareByTotalAsc(const Student& a, const Student& b) {
    return a.getTotalScore() < b.getTotalScore();
}
// 排序比较函数：按数学成绩降序
bool compareByMathDesc(const Student& a, const Student& b) {
    return a.getMathScore() > b.getMathScore();
}
// 排序比较函数：按数学成绩升序
bool compareByMathAsc(const Student& a, const Student& b) {
    return a.getMathScore() < b.getMathScore();
}
// 排序比较函数：按语文成绩降序
bool compareByChineseDesc(const Student& a, const Student& b) {
    return a.getChineseScore() > b.getChineseScore();
}
// 排序比较函数：按语文成绩升序
bool compareByChineseAsc(const Student& a, const Student& b) {
    return a.getChineseScore() < b.getChineseScore();
}
// 排序比较函数：按英语成绩降序
bool compareByEnglishDesc(const Student& a, const Student& b) {
    return a.getEnglishScore() > b.getEnglishScore();
}
// 排序比较函数：按英语成绩升序
bool compareByEnglishAsc(const Student& a, const Student& b) {
    return a.getEnglishScore() < b.getEnglishScore();
}

// 功能函数：添加学生信息
void addStudent() {
    Student stu; // 创建空学生对象
    string id, name, gender, className;
    int age, math, chinese, english;
    cout << "=== 添加学生信息 ===\n";
    cin.ignore(); // 清空输入缓冲区

    // 输入学号（循环直到合法）
    do {
        cout << "学号（8位数字）：";
        getline(cin, id); // 读取整行
        if (!stu.setId(id)) { // 验证学号合法性
            cout << "学号格式不合法（必须为8位数字），请重新输入！\n";
        }
    } while (!stu.setId(id)); // 不合法则重新输入

    // 输入姓名
    cout << "姓名：";
    getline(cin, name); // 读取姓名（支持空格）
    stu.setName(name);

    // 输入性别（循环直到合法）
    do {
        cout << "性别（男/女/未知）：";
        getline(cin, gender);
        if (!stu.setGender(gender)) { // 验证性别合法性
            cout << "性别不合法，请重新输入！\n";
        }
    } while (!stu.setGender(gender));

    // 输入年龄（循环直到合法）
    do {
        cout << "年龄（6-40岁）：";
        cin >> age;
        if (!stu.setAge(age)) { // 验证年龄合法性
            cout << "年龄范围不合法，请重新输入！\n";
        }
    } while (!stu.setAge(age));
    cin.ignore(); // 清空输入缓冲区

    // 输入班级
    cout << "班级：";
    getline(cin, className);
    stu.setClassName(className);

    // 输入数学成绩
    do {
        cout << "数学成绩（0-100）：";
        cin >> math;
        if (!stu.setMathScore(math)) { // 验证成绩合法性
            cout << "成绩不合法，请重新输入！\n";
        }
    } while (!stu.setMathScore(math));

    // 输入语文成绩
    do {
        cout << "语文成绩（0-100）：";
        cin >> chinese;
        if (!stu.setChineseScore(chinese)) {
            cout << "成绩不合法，请重新输入！\n";
        }
    } while (!stu.setChineseScore(chinese));

    // 输入英语成绩
    do {
        cout << "英语成绩（0-100）：";
        cin >> english;
        if (!stu.setEnglishScore(english)) {
            cout << "成绩不合法，请重新输入！\n";
        }
    } while (!stu.setEnglishScore(english));

    // 将合法的学生对象添加到全局列表
    studentList.push_back(stu);
    cout << "学生信息添加成功！\n";
}

// 功能函数：查询学生信息（按学号/姓名模糊匹配）
void searchStudent() {
    string key; // 存储查询关键字
    cin.ignore(); // 清空输入缓冲区
    cout << "=== 查询学生信息 ===\n";
    cout << "请输入查询关键字（学号/姓名）：";
    getline(cin, key); // 读取查询关键字

    bool found = false; // 标记是否找到匹配学生
    cout << "\n查询结果：\n";
    // 遍历所有学生
    for (const auto& stu : studentList) {
        // 学号精确匹配 或 姓名包含关键字（模糊匹配）
        if (stu.getId() == key || stu.getName().find(key) != string::npos) {
            stu.showInfo(); // 显示匹配的学生信息
            found = true;
        }
    }
    if (!found) { // 未找到匹配学生
        cout << "未找到匹配的学生信息！\n";
    }
}

// 功能函数：删除学生信息（按学号精确匹配）
void deleteStudent() {
    string id; // 存储要删除的学号
    cin.ignore(); // 清空输入缓冲区
    cout << "=== 删除学生信息 ===\n";
    cout << "请输入要删除的学生学号：";
    getline(cin, id);

    bool found = false; // 标记是否找到该学生
    // 遍历学生列表（使用迭代器，支持删除操作）
    for (auto it = studentList.begin(); it != studentList.end(); ++it) {
        if (it->getId() == id) { // 找到匹配学号的学生
            // 二次确认删除
            cout << "确认删除学号为" << id << "的学生" << it->getName() << "吗？Y/N：";
            char confirm;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') { // 确认删除
                studentList.erase(it); // 从列表中删除该学生
                found = true;
                cout << "学生信息删除成功！\n";
            }
            else { // 取消删除
                cout << "取消删除操作！\n";
            }
            break; // 找到后退出循环
        }
    }
    if (!found) { // 未找到该学号的学生
        cout << "未找到学号为" << id << "的学生！\n";
    }
}

// 功能函数：修改学生信息（按学号精确匹配）
void modifyStudent() {
    string id; // 存储要修改的学生学号
    cin.ignore(); // 清空输入缓冲区
    cout << "=== 修改学生信息 ===\n";
    cout << "请输入要修改的学生学号：";
    getline(cin, id);

    // 遍历学生列表
    for (auto& stu : studentList) {
        if (stu.getId() == id) { // 找到匹配学号的学生
            cout << "找到学生：" << stu.getName() << "\n";
            string newVal;    // 存储字符串类型新值
            int newIntVal;    // 存储数值类型新值

            // 修改姓名（为空则不修改）
            cout << "新姓名（不修改请回车）：";
            getline(cin, newVal);
            if (!newVal.empty()) {
                stu.setName(newVal);
            }

            // 修改性别
            do {
                cout << "新性别（男/女/未知，不修改请回车）：";
                getline(cin, newVal);
                if (newVal.empty()) { 
                    break;
                }
                if (!stu.setGender(newVal)) { // 验证性别合法性
                    cout << "性别不合法，请重新输入！\n";
                }
            } while (!newVal.empty() && !stu.setGender(newVal));

            // 修改年龄
            cout << "新年龄（6-40岁，不修改请回车）：";
            getline(cin, newVal);
            if (!newVal.empty()) {
                newIntVal = stoi(newVal); // 字符串转整数
                // 循环直到输入合法年龄
                while (!stu.setAge(newIntVal)) {
                    cout << "年龄范围不合法，请重新输入：";
                    getline(cin, newVal);
                    newIntVal = stoi(newVal);
                }
            }

            // 修改班级
            cout << "新班级（不修改请回车）：";
            getline(cin, newVal);
            if (!newVal.empty()) {
                stu.setClassName(newVal);
            }

            // 修改数学成绩
            cout << "新数学成绩（0-100，不修改请回车）：";
            getline(cin, newVal);
            if (!newVal.empty()) {
                newIntVal = stoi(newVal);
                while (!stu.setMathScore(newIntVal)) {
                    cout << "成绩不合法，请重新输入：";
                    getline(cin, newVal);
                    newIntVal = stoi(newVal);
                }
            }

            // 修改语文成绩
            cout << "新语文成绩（0-100，不修改请回车）：";
            getline(cin, newVal);
            if (!newVal.empty()) {
                newIntVal = stoi(newVal);
                while (!stu.setChineseScore(newIntVal)) {
                    cout << "成绩不合法，请重新输入：";
                    getline(cin, newVal);
                    newIntVal = stoi(newVal);
                }
            }

            // 修改英语成绩
            cout << "新英语成绩（0-100，不修改请回车）：";
            getline(cin, newVal);
            if (!newVal.empty()) {
                newIntVal = stoi(newVal);
                while (!stu.setEnglishScore(newIntVal)) {
                    cout << "成绩不合法，请重新输入：";
                    getline(cin, newVal);
                    newIntVal = stoi(newVal);
                }
            }

            cout << "学生信息修改成功！\n";
            return; 
        }
    }
    // 未找到匹配学号的学生
    cout << "未找到学号为" << id << "的学生！\n";
}

// 功能函数：成绩排序（总分/单科，升序/降序）
void sortStudents() {
    if (studentList.empty()) { // 学生列表为空时提示
        cout << "当前系统无学生信息，无法排序！\n";
        return;
    }

    cout << "=== 成绩排序 ===\n";
    cout << "请选择排序维度：\n";
    cout << "1. 按总分排序\n";
    cout << "2. 按数学成绩排序\n";
    cout << "3. 按语文成绩排序\n";
    cout << "4. 按英语成绩排序\n";
    cout << "请输入维度序号：";
    int dimChoice; // 排序维度选择
    cin >> dimChoice;

    cout << "请选择排序顺序：\n";
    cout << "1. 升序（从小到大）\n";
    cout << "2. 降序（从大到小）\n";
    cout << "请输入顺序序号：";
    int orderChoice; // 排序顺序选择
    cin >> orderChoice;

    // 根据选择执行排序
    switch (dimChoice) {
    case 1: // 按总分排序
        if (orderChoice == 1) sort(studentList.begin(), studentList.end(), compareByTotalAsc);
        else sort(studentList.begin(), studentList.end(), compareByTotalDesc);
        break;
    case 2: // 按数学成绩排序
        if (orderChoice == 1) sort(studentList.begin(), studentList.end(), compareByMathAsc);
        else sort(studentList.begin(), studentList.end(), compareByMathDesc);
        break;
    case 3: // 按语文成绩排序
        if (orderChoice == 1) sort(studentList.begin(), studentList.end(), compareByChineseAsc);
        else sort(studentList.begin(), studentList.end(), compareByChineseDesc);
        break;
    case 4: // 按英语成绩排序
        if (orderChoice == 1) sort(studentList.begin(), studentList.end(), compareByEnglishAsc);
        else sort(studentList.begin(), studentList.end(), compareByEnglishDesc);
        break;
    default: // 无效维度选择
        cout << "排序维度选择不合法，排序失败！\n";
        return;
    }

    // 排序完成后显示结果
    cout << "排序完成，排序结果如下：\n";
    for (const auto& stu : studentList) {
        stu.showInfo();
    }
}

// 功能函数：显示所有学生信息
void showAllStudents() {
    cout << "=== 所有学生信息 ===\n";
    if (studentList.empty()) { // 列表为空时提示
        cout << "当前系统无学生信息！\n";
        return;
    }
    // 遍历并显示每个学生的信息
    for (const auto& stu : studentList) {
        stu.showInfo();
    }
}

// 功能函数：保存数据到文件（支持覆盖/追加模式）
void saveToFile(bool isAppend) {
    // 打开文件：ios::app追加模式，ios::trunc覆盖模式（默认）
    ofstream file(FILE_PATH, isAppend ? ios::app : ios::trunc);
    if (!file) { // 文件打开失败
        cout << "文件打开失败，数据保存失败！\n";
        return;
    }

    // 遍历学生列表，将每个学生信息写入文件
    for (const auto& stu : studentList) {
        file << stu.toFileString() << endl;
    }

    file.close(); // 关闭文件
    cout << "数据已保存到 " << FILE_PATH << "（" << (isAppend ? "追加模式" : "覆盖模式") << "）！\n";
}

// 功能函数：从文件加载数据
void loadFromFile() {
    ifstream file(FILE_PATH); // 打开文件（只读模式）
    if (!file) { // 文件打开失败（如文件不存在）
        cout << "文件未找到，无法读取，当前为空系统！\n";
        return;
    }

    studentList.clear(); // 清空现有学生列表
    string line;         // 存储文件中每行内容
    int validCount = 0;  // 合法记录数
    int invalidCount = 0;// 非法记录数

    // 逐行读取文件内容
    while (getline(file, line)) {
        Student stu;
        // 解析每行内容为学生信息
        if (stu.fromFileString(line)) {
            studentList.push_back(stu); // 合法记录添加到列表
            validCount++;
        }
        else { // 解析失败（非法记录）
            invalidCount++;
        }
    }

    file.close(); // 关闭文件
    // 输出加载结果
    cout << "数据加载完成，成功加载" << validCount << "条合法记录";
    if (invalidCount > 0) { // 有非法记录时提示
        cout << "，跳过" << invalidCount << "条非法数据！";
    }
    cout << "\n";
}

// 主函数：程序入口
int main() {
    loadFromFile(); // 程序启动时自动加载文件中的学生数据
    int choice;     // 存储用户菜单选择
    do {
        showMainMenu(); // 显示主菜单
        cout << "请输入功能序号：";
        if (cin >> choice) { // 输入合法（数字）
            cout << endl;
            // 根据选择执行对应功能
            switch (choice) {
            case 1: addStudent();    break;  // 添加学生
            case 2: searchStudent(); break;  // 查询学生
            case 3: deleteStudent(); break;  // 删除学生
            case 4: modifyStudent(); break;  // 修改学生
            case 5: sortStudents();  break;  // 成绩排序
            case 6: showAllStudents(); break;// 显示所有学生
            case 7: saveToFile(false); break;// 覆盖保存到文件
            case 8: saveToFile(true); break; // 追加保存到文件
            case 9: loadFromFile();   break; // 从文件加载数据
            case 0: // 退出系统
                cout << "感谢使用，程序即将退出！\n";
                saveToFile(false); // 退出前自动保存数据（覆盖模式）
                break;
            default: // 无效功能选择
                cout << "输入的序号不合法，请重新选择！\n";
            }
        }
        else { // 输入不合法
            cin.clear(); // 清空输入错误状态
            // 忽略输入缓冲区所有字符直到换行
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入格式错误，请输入数字序号！\n";
        }
        if (choice != 0) { // 非退出功能，暂停并清空控制台
            pauseAndClear();
        }
    } while (choice != 0); // 选择0时退出循环（程序结束）
    return 0; // 程序正常退出
}
