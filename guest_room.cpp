#define _CRT_SECURE_NO_WARNINGS 
#include "guest_room.h" 
#include <time.h> 
#include <iostream> 
#include <fstream> 
using namespace std;

// �����ַ�ָ�룬ָ��һ���ļ� 
const char* const room_data_file = "room.dat";

// GuestRoom���캯��ʵ�� 
GuestRoom::GuestRoom(string name, int price, int bed_num, int area, ROOM_STATE state = FREE)
{
    this->m_name = name;
    this->m_price = price;
    this->m_bed_number = bed_num;
    this->m_area = area;
    this->m_number = generate_number();
    this->m_state = state;
}

// ���ɿͷ���� 
string GuestRoom::generate_number()
{
    // ����ʱ��ת�ַ��� 
    time_t my_time = time(NULL);
    struct tm* my_tm = localtime(&my_time);
    char tim_buff[128] = { 0 };
    sprintf(tim_buff, "%d%d", my_tm->tm_yday, my_tm->tm_sec);
    // ��������� 
    int rand_num = rand() % 50;
    char buf[128] = { 0 };
    sprintf(buf, "%d", rand_num);
    // ƴ���ַ�����Ϊ������ 
    return string(tim_buff) + string(buf);
}

// ��ʾ�ͷ�״̬ 
string GuestRoom::show_state()
{
    if (m_state == FREE)
        return "����";
    if (m_state == CHECK_IN)
        return "��ס";
}

// �������ݣ�map������key:�ͷ���ţ�value:�ͷ����� 
bool GuestRoom::save_data(map<string, GuestRoom>& room_list)
{
    // 1. ���ļ� 
    ofstream ofs(room_data_file, ios::out);
    if (!ofs)
    {
        return false;
    }
    // 2. д��������� 
    for (auto& room : room_list)
    {
        // д��m_name��Ա������ռ�ڴ��С����ֵ 
        size_t name_len = room.second.m_name.size();
        ofs.write(reinterpret_cast<const char*>(&name_len), sizeof(size_t));
        ofs.write(room.second.m_name.c_str(), name_len);
        // д��m_price 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_price), sizeof(int));
        // д��m_area 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_area), sizeof(int));
        // д��m_bed_number 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_bed_number), sizeof(int));
        // д��m_state 
        ofs.write(reinterpret_cast<const char*>(&room.second.m_state), sizeof(enum ROOM_STATE));
        // д��m_number��Ա������ռ�ڴ��С����ֵ 
        size_t number_len = room.second.m_number.size();
        ofs.write(reinterpret_cast<const char*>(&number_len), sizeof(size_t));
        ofs.write(room.second.m_number.c_str(), number_len);
    }
    // 3. �ر��ļ�  
    ofs.close();
    return true;
}

// ��ȡ���� 
map<string, GuestRoom> GuestRoom::read_data()
{
    // 1. ���ļ� 
    map<string, GuestRoom> room_list;
    ifstream ifs(room_data_file, ios::in);
    if (!ifs)
    {
        return room_list;
    }
    // 2. д��������� 
    while (ifs.peek() != EOF)
    {
        GuestRoom room;
        // ����m_name��Ա������ռ�ڴ��С����ֵ 
        size_t name_len = 0;
        ifs.read(reinterpret_cast<char*>(&name_len), sizeof(size_t));
        char name_buffer[128] = { 0 };
        ifs.read(name_buffer, name_len);
        room.m_name = name_buffer;
        // д��m_price 
        ifs.read(reinterpret_cast<char*>(&room.m_price), sizeof(int));
        // д��m_area 
        ifs.read(reinterpret_cast<char*>(&room.m_area), sizeof(int));
        // д�� bed_number 
        ifs.read(reinterpret_cast<char*>(&room.m_bed_number), sizeof(int));
        // д�� state 
        ifs.read(reinterpret_cast<char*>(&room.m_state), sizeof(enum ROOM_STATE));
        // д��m_number��Ա������ռ�ڴ��С����ֵ 
        size_t number_len = 0;
        ifs.read(reinterpret_cast<char*>(&number_len), sizeof(size_t));
        char number_buffer[128] = { 0 };
        ifs.read(number_buffer, number_len);
        room.m_number = number_buffer;
        // �����ݴ洢��map������ 
        room_list.insert(make_pair(room.m_number, room));
    }
    // 3. �ر��ļ�  
    ifs.close();
    return room_list;
}

// ��ȡ�ͷ���� 
string GuestRoom::get_num()
{
    return m_number;
}

// ���ÿͷ�״̬ 
void GuestRoom::set_state()
{
    m_state = CHECK_IN;
}

// ��ȡ�ͷ����� 
string GuestRoom::get_name()
{
    return m_name;
}

// ��ȡ�ͷ��۸� 
int GuestRoom::get_price()
{
    return m_price;
}

// ��ȡ�ͷ���� 
int GuestRoom::get_area()
{
    return m_area;
}

// ��ȡ�ͷ���λ���� 
int GuestRoom::get_bed_num()
{
    return m_bed_number;
}
