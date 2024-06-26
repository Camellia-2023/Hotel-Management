#include "room_manager.h" 
#include "guest_room.h" 
#include<iostream> 
using namespace std;

// ���캯��ʵ�� 
GuestRoomManager::GuestRoomManager()
{
    GuestRoom().read_data(); // ��ȡ�ͷ�����  
}

// ���ҿͷ� 
bool GuestRoomManager::check_in(const string number)
{
    // ��ȡ�ļ��е����ݵ������� 
    GuestRoom grm;
    m_room_list = grm.read_data();
    // �������в��ҿͷ� 
    if (m_room_list.find(number) == m_room_list.end())
    {
        return false;
    }
    return true;
}

// ��ӿͷ� 
void GuestRoomManager::add_room(GuestRoom room)
{
    // �жϿͷ�����Ƿ���� 
    if (check_in(room.get_num()))
    {
        cout << "�������Ѵ���" << endl;
        return;
    }
    // ���ͷ���ӵ������� 
    m_room_list.insert(make_pair(room.get_num(), room));
    // �������е����ݴ�ŵ��ļ��� 
    GuestRoom().save_data(m_room_list);
}

// ɾ���ͷ����� 
bool GuestRoomManager::remove_data(const string number)
{
    // �жϿͷ�����Ƿ���� 
    if (!check_in(number))
    {
        cout << "�����Ų�����" << endl;
        return false;
    }
    // ɾ�� 
    m_room_list = GuestRoom().read_data();
    m_room_list.erase(number);
    // �����ļ� 
    GuestRoom().save_data(m_room_list);
    return true;
}

// ���ÿͷ�״̬ 
void GuestRoomManager::set_room_state(string number)
{
    if (!check_in(number))
    {
        cout << "�����Ų�����" << endl;
        return;
    }
    else
    {
        // ���ļ��еĿͷ����ݶ�ȡ���ļ��� 
        m_room_list = GuestRoom().read_data();
        // ����Ϊ��ס״̬ 
        m_room_list[number].set_state();
        // �����ݱ��浽�ļ��� 
        GuestRoom().save_data(m_room_list);
    }
}
