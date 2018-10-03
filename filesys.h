/****************************
 *  Header for filesys.cpp
 *  Kevin Newell
 *  9/2/18
 *  Defines filesys class
 ***************************/

#ifndef FILESYS_H
#define FILESYS_H

#include<iostream>
#include<string>
#include<ctime>
#include<vector>

using std::string;
using std::vector;

struct fsNode{
  string name;
  char access[10];       //Permission bits
  string owner;
  string group;
  string timestamp;
  fsNode* parent;        //Tree stuff
  vector<fsNode*> child;
};

class fs{
  public:
    //File operations
    fs();
    fs(string user);
    ~fs();
    string ls(string flags);
    void cd(string name);
    string pwd();
    void mkdir(string name);
    void rmdir(string name);
    void rm(string name);
    void chmod(string perm, string name);
    void touch(string name);

    string muser;

  private:
    //Sets default permission in access array
    void setAccessD(char access[]);
    void setAccessF(char access[]);
    fsNode* find(string name);
    string getTime();
    void clean(fsNode* n);

    fsNode* mcurr;
    fsNode* root;
    time_t t;              //Time stuff
    struct tm* now;
};

#endif
