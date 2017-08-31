#pragma once

#define NUM 256	//总节点数
#define BNUM 1000	//磁盘块数
#define BSIZE 512 //块大小
#define FSIZE 2048	//超级块大小
#define SSIZE 1046528 //存储空间大小
#define NAMESIZE 16	//文件名长度
#define DIRSIZE 16	//目录大小
#define DIRNUM 32	//目录个数
#define FREEBYTE 1021888 //空间总大小
#define DIRMODE 0 //目录类型
#define FILEMODE 1	//文件类型

// 返回状态
enum STATUS
{
	SUCCESS, ERR_PATH_FAIL, ERR_FILE_EXIST, ERR_FILE_NOT_EXIST, ERR_FILE_FAIL
};
// 超级块
struct superblock
{
	unsigned int s_size;	//总大小
	unsigned int s_itsize;	//inode表大小
	unsigned int s_freeinodesize;	//空闲i节点的数量
	unsigned int s_nextfreeinode;	//下一个空闲i节点
	unsigned int s_freeinode[NUM];	//空闲i节点数组 0/1
	unsigned int s_freeblocksize;	//空闲块的数量          
	unsigned int s_nextfreeblock;	//下一个空闲块
	unsigned char s_freeblock[BNUM];	//空闲块数组0/1  
};

//一次间接寻址
struct atime
{
	int fi_addr[128];
};
//二次间接寻址
struct mtime
{
	struct atime* atime_addr[128];
};

// 文件节点
struct finode
{
	int fi_mode;	//类型：文件/目录
	int fi_nlink;		//链接数，当链接数为0，意味着被删除
	int dir_no;		//目录号
	long int fi_size;	//文件大小
	long int fi_addr[10];	//文件块一级指针，并未实现多级指针
	struct atime  *fi_atime_unused;	//二级寻址
	struct mtime  *fi_mtime_unused;	//多级寻址
};

//目录项结构
struct direct
{
	char d_name[NAMESIZE];        //文件或者目录的名字
	unsigned short d_ino;        //文件或者目录的i节点号
};
//目录结构
struct dire
{
	struct direct direct[DIRSIZE];    //包含的目录项数组
	unsigned short size;        //包含的目录项大小
};

// 磁盘
struct storage
{
	struct superblock root;
	struct finode fnode[NUM];
	struct dire dir[DIRNUM];
	char free[FREEBYTE];
};
//全局磁盘变量
extern struct storage *root;
// 全局路径
extern char PATH[NAMESIZE*DIRNUM];