#pragma once

#include<iostream>
#include<iomanip>
#include<string>
#include<conio.h>
#include"defines.h"

using namespace std;

class opration {
public:
	int help();

	STATUS mkdir(char *path, char *pname);
	STATUS create(char *path, char* fname);
	STATUS read(char *path, char *file);
	STATUS vi(char *path, char *file, char *cont);
	int rm(char *path, char *file);
	STATUS rename(char *path, char *cname, char *nname);
	STATUS mv(char *path, char *file, char *npath);
	STATUS cd(char *topath);

	STATUS ls(char *path);
	STATUS free();
	STATUS writeout();
	STATUS readin();

	int getnode(char *path);
};