#define _CRT_SECURE_NO_WARNINGS 
#include "guest_room.h" 
#include <time.h> 
#include <iostream> 
#include <fstream> 
using namespace std;

// 定义字符指针，指向一个文件 
const char* const room_data_file = "room.dat";

// GuestRoom构造函数实现 
GuestRoom::GuestRoom(string name, int price, int bed_num, int area, ROOM_STATE state = FREE)
{
    this->m_name = name;
    this->m_price = price;
    this->m_bed_number = bed_num;
    this->m_area = area;
    this->m_number = generate_number();
    this->m_state = state;
}

// 生成客房编号 
string GuestRoom::generate_number()
{
    // 本地时间转字符串 
    time_t my_time = time(NULL);
    struct tm* my_tm = localtime(&my_time);
    char tim_buff[128] = { 0 };
    sprintf(tim_buff, "%d%d", my_tm->tm_yday, my_tm->tm_sec);
    // 生成随机数 
    int rand_num = rand() % 50;
    char buf[128] = { 0 };
    sprintf(buf, "%d", rand_num);
    // 拼接字符串作为房间编号 
    return string(tim_buff) + string(buf);
}

// 显示客房状态 
string GuestRoom::show_state()
{
    if (m_state == FREE)
        return "空闲";
    if (m_state == CHECK_IN)
        return "入住";
}

// 保存数据（map容器，key:客房编号，value:客房对象） 
bool GuestRoom::save_data(map<string, GuestRoom>& room_list)
{
    // 1. 打开文件 
    ofstream ofs(room_data_file, ios::out);
    if (!ofs)
    {
        return false;
    }
    // 2. 写入对象数据 
    for (auto& room : room_list)
    {
        // 写入m_name成员变量所占内存大小及其值 
        size_t name_len = room.second.m_name.size();
        ofs.write(reinterpret_cast<const char*>(&name_len), sizeof(size_t));
        ofs.write(room.second.m_name.c_str(), name_len);
        // 写入m_price 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_price), sizeof(int));
        // 写入m_area 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_area), sizeof(int));
        // 写入m_bed_number 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_bed_number), sizeof(int));
        // 写入m_state 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_state), sizeof(enum ROOM_STATE));
        // 写入m_number成员变量所占内存大小及其值 
        size_t number_len = room.second.m_number.size();
        ofs.write(reinterpret_cast<const char*>(&number_len), sizeof(size_t));
        ofs.write(room.second.m_number.c_str(), number_len);
    }
    // 3. 关闭文件  
    ofs.close();
    return true;
}

// 读取数据 
map<string, GuestRoom> GuestRoom::read_data()
{
    // 1. 打开文件 
    map<string, GuestRoom> room_list;
    ifstream ifs(room_data_file, ios::in);
    if (!ifs)
    {
        return room_list;
    }
    // 2. 写入对象数据 
    while (ifs.peek() != EOF)
    {
        GuestRoom room;
        // 读入m_name成员变量所占内存大小及其值 
        size_t name_len = 0;
        ifs.read(reinterpret_cast<char*>(&name_len), sizeof(size_t));
        char name_buffer[128] = { 0 };
        ifs.read(name_buffer, name_len);
        room.m_name = name_buffer;
        // 写入m_price 
        ifs.read(reinterpret_cast<char*>(&room.m_price), sizeof(int));
        // 写入m_area 
        ifs.read(reinterpret_cast<char*>(&room.m_area), sizeof(int));
        // 写入 bed_number 
        ifs.read(reinterpret_cast<char*>(&room.m_bed_number), sizeof(int));
        // 写入 state 
        ifs.read(reinterpret_cast<char*>(&room.m_state), sizeof(enum ROOM_STATE));
        // 写入m_number成员变量所占内存大小及其值 
        size_t number_len = 0;
        ifs.read(reinterpret_cast<char*>(&number_len), sizeof(size_t));
        char number_buffer[128] = { 0 };
        ifs.read(number_buffer, number_len);
        room.m_number = number_buffer;
        // 将数据存储到map容器中 
        room_list.insert(make_pair(room.m_number, room));
    }
    // 3. 关闭文件  
    ifs.close();
    return room_list;
}

// 获取客房编号 
string GuestRoom::get_num()
{
    return m_number;
}

// 设置客房状态 
void GuestRoom::set_state()
{
    m_state = CHECK_IN;
}

// 获取客房名称 
string GuestRoom::get_name()
{
    return m_name;
}

// 获取客房价格 
int GuestRoom::get_price()
{
    return m_price;
}

// 获取客房面积 
int GuestRoom::get_area()
{
    return m_area;
}

// 获取客房床位数量 
int GuestRoom::get_bed_num()
{
    return m_bed_number;
}
