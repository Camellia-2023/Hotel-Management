#pragma once
#pragma once 
#include <string> 
#include<map> 
using namespace std;
//定义enum ROOM_STATE枚举类型，表示客房状态：空闲、入住 
enum ROOM_STATE { FREE = 0, CHECK_IN };
//定义客房类 
class GuestRoom
{
public:
	GuestRoom() = default;       //提供默认构造函数 
	GuestRoom(string, int, int, int, ROOM_STATE);  //有参构造函数 
	string generate_number();      //生成客房编号 
	string show_state();       //显示客房状态 
	bool save_data(map<string, GuestRoom>&);   //保存数据 
	map<string, GuestRoom> read_data();    //读取数据 
public:
	string get_num();        //获取客房编号 
	string get_name();        //获取客房名称 
	int get_price();        //获取客房价格 
	int get_area();        //获取客房面积 
	int get_bed_num();        //获取客房床位数量 
	void set_state();        //设置客房状态 
private:
	string m_number;        //客房编号 
	int m_price;         //客房价格 
	int m_area;         //客房面积 
	int m_bed_number;        //客房床位数量 
	string m_name;         //客房名称 
	enum  ROOM_STATE m_state;      //客房状态 
};