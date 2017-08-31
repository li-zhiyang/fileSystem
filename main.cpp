/**
* 开发人员：李志杨，汤彩霞，廖伟建
*
* 任务：建立基于内存的文件系统
* 目的：深入了解文件系统结构
* 要求：首先分配一定容量的内存，建立虚拟磁盘；
*	   在该磁盘上建立相应的文件文件系统；
*	   为该文件系统设计相应的数据结构来管理目录，虚拟磁盘的空闲空间，已分配空间等；
*	   提供文件的创建、删除、移位、改名等功能；
*	   提供良好的界面，可以显示磁盘文件的状态和空间的使用情况；
*	   提供虚拟磁盘转储功能，可将信息存入磁盘，还可从磁盘读入内存。
*
* 开发环境：VS2015，windows 10
*
*/


#include<iostream>
#include"defines.h"
#include"opration.h"
#include<map>

using namespace std;
//全局磁盘变量
struct storage *root = new storage;
// 全局路径
char PATH[NAMESIZE*DIRNUM] = "";
void init()
{

	memset(root->fnode, '\0', FREEBYTE);
	root->dir[0].direct[0].d_ino = 0;
	root->dir[0].size = 1;
	strcpy(root->dir[0].direct[0].d_name, "C"); //设置根目录名
	root->fnode[0].fi_mode = DIRMODE;
	root->fnode[0].fi_nlink = 1;
	root->fnode[0].dir_no = 1;
	root->dir[1].size = 1;
	root->root.s_freeblocksize = BNUM;
	strcpy(PATH, "/C");
}

int main()
{
	map<string, int> command = {
		{"mkdir",1},
		{"create",2},
		{"read",3},
		{"vi",4},
		{"rm",5},
		{"rename",6},
		{"mv",7},
		{"cd",8},
		{"pwd",9},
		{"ls",10},
		{"free",11},
		{"writeout",12},
		{"readin",13},
		{"formate",14},
		{"help",15},
		{"exit",16},
		{"clear",17},
	};

	opration oprate;
	oprate.help();

	string s;
	char arg1[NAMESIZE] = "";
	char arg2[NAMESIZE] = "";
	char content[BSIZE*BNUM] = "";
	init();
	cout << "FileSystem>";
	bool flag = true;
	int commandNum;
	while (flag) {
		cout << PATH << ">";
		cin >> s;
		if (command.count(s) > 0) {
			commandNum = command.find(s)->second;
		}
		else {
			commandNum = 0;
		}
		switch (commandNum) 
		{
		case 1:cin >> arg1;
			oprate.mkdir(PATH, arg1);
			break;
		case 2:cin >> arg1;
			oprate.create(PATH, arg1);
			break;
		case 3:cin >> arg1;
			oprate.read(PATH, arg1);
			break;
		case 4:cin >> arg1;
			cout << endl << "请输入要写入文件的内容：" << endl;
			cin >> content;
			oprate.vi(PATH, arg1, content);
			break;
		case 5:cin >> arg1;
			oprate.rm(PATH, arg1);
			break;
		case 6:cin >> arg1 >> arg2;
			oprate.rename(PATH, arg1, arg2);
			break;
		case 7:cin >> arg1 >> arg2;
			oprate.mv(PATH, arg1, arg2);
			break;
		case 8:cin >> arg1;
			oprate.cd(arg1);
			break;
		case 9:cout << PATH << endl;
			break;
		case 10:oprate.ls(PATH);
			break;
		case 11:oprate.free();
			break;
		case 12:oprate.writeout();
			cout << "已写出到 filesystem.dat" << endl;
			break;
		case 13:oprate.readin();
			cout << "已从 filesystem.dat 中读入文件系统" << endl;
			break;
		case 14:memset(root, '\0', sizeof(struct storage));
			init();
			break;
		case 15:oprate.help();
			break;
		case 16:flag = false;
			break;
		case 17:system("cls");
			break;
		default:cout << "输入的命令有误，请重新输入" << endl;
			break;
		}
	}

	return 0;
	
}


