#pragma once
#include "guest_room.h" 
#include<map> 
#include<string> 
class GuestRoomManager      //����ͷ������� 
{
public:
	GuestRoomManager();      //���캯�� 
	bool check_in(const string);    //���ҿͷ� 
	void add_room(const GuestRoom room);   //��ӿͷ� 
	bool remove_data(const string);    //ɾ���ͷ����� 
	void set_room_state(string number);  //���ÿͷ�״̬ 
private:
	map<string, GuestRoom> m_room_list;  //map���� 
};
