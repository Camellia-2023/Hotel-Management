#pragma once
#include "guest_room.h" 
#include<map> 
#include<string> 
class GuestRoomManager      //定义客房管理类 
{
public:
	GuestRoomManager();      //构造函数 
	bool check_in(const string);    //查找客房 
	void add_room(const GuestRoom room);   //添加客房 
	bool remove_data(const string);    //删除客房数据 
	void set_room_state(string number);  //设置客房状态 
private:
	map<string, GuestRoom> m_room_list;  //map容器 
};
