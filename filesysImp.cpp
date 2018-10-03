/****************************
 * fs implementation file
 * 
 * Kevin Newell
 * 9/5/18
 ***************************/

#include"filesys.h"

using std::cout;

//Returns a timestamp string
string fs::getTime(){
  string stamp;
  t = time(0);
  now = localtime(&t);
  stamp = asctime(now);
  stamp = stamp.substr(0, stamp.length() - 1);

  return (stamp);
}

//Sets default permissions
void fs::setAccessD(char access[]){
  access[0] = 'd';
  access[1] = 'r';
  access[2] = 'w';
  access[3] = 'x';
  access[4] = 'r';
  access[5] = '-';
  access[6] = 'x';
  access[7] = 'r';
  access[8] = '-';
  access[9] = '-';
  return;
}

//Sets default permissions
void fs::setAccessF(char access[]){
  access[0] = '-';
  access[1] = 'r';
  access[2] = 'w';
  access[3] = 'x';
  access[4] = 'r';
  access[5] = '-';
  access[6] = 'x';
  access[7] = 'r';
  access[8] = '-';
  access[9] = '-';
  return;
}

//Searches current level in search of correct node
fsNode* fs::find(string name){
  if(name == "..")
    return mcurr->parent;

  for(vector<fsNode*>::iterator i = mcurr->child.begin(); i != mcurr->child.end(); ++i){
    if(name == (*i)->name)
      return *i;
  }
  return nullptr;
}

//Recursivly deletes nodes
void fs::clean(fsNode* n){
  for(vector<fsNode*>::iterator i = n->child.begin(); i != n->child.end(); ++i){
    if(*i != nullptr)
      clean(*i);
  }

  delete n;
  n = nullptr;
  return;
}

//Default Constructor
fs::fs(){
  root = new fsNode;

  root->name = "/";
  setAccessD(root->access);
  root->owner = "root";
  root->group = "root";
  root->timestamp = getTime();
  root->parent = nullptr;

  mcurr = root;
}

//Parameter Constructor
fs::fs(string user){
  muser = user;
  root = new fsNode;

  root->name = "/";
  setAccessD(root->access);
  root->owner = "root";
  root->group = "root";
  root->timestamp = getTime();
  root->parent = nullptr;

  mcurr = root;
  mkdir("home/");
  mcurr = root->child.back();
  string home = user;
  home += "/";
  mkdir(home);
  mcurr = mcurr->child.back();
}

//Destructor
fs::~fs(){
  clean(root);
}

//Creates new directories
void fs::mkdir(string name){
  if(find(name) == nullptr){
    if(name[name.length() - 1] != '/'){
      cout << "A directory name must end with '/'!\n";
      return;
    }

    mcurr->child.push_back(new fsNode);
    fsNode* proto = mcurr->child.back();

    proto->name = name;
    setAccessD(proto->access);
    proto->owner = proto->group = muser;
    proto->timestamp = getTime();
    proto->parent = mcurr;
  }else{
    cout << "An directory with this name already exists!\n";
  }

  return;
}

//Lists all files and directories
string fs::ls(string flags){
  string files = "";

  if(flags == ""){
    for(vector<fsNode*>::iterator i = mcurr->child.begin(); i != mcurr->child.end(); ++i){
      if(*i == nullptr)
        continue;
      files += (*i)->name;
      files += '\t';
    }
  }else if(flags.find('l') < flags.length() && flags[0] == '-'){
    for(vector<fsNode*>::iterator i = mcurr->child.begin(); i != mcurr->child.end(); ++i){
      for(int j = 0; j < 10; j++)
        files += (*i)->access[j];
      files += ' ';
      files += (*i)->owner;
      files += ' ';
      files += (*i)->group;
      files += ' ';
      files += (*i)->timestamp;
      files += ' ';
      files += (*i)->name;
      files += '\n';
    }
  }

  return files;
}

//Changes directory
void fs::cd(string name){
  fsNode* dir = find(name);
  if(dir != nullptr){
    mcurr = dir;
  }else{
    cout << "Dir does not exist\n";
  }

  return;
}

//Prints the full file path from root
string fs::pwd(){
  string path = mcurr->name;
  fsNode* par = mcurr->parent;
  if(par != nullptr){
    while(par->parent != nullptr){
      path = par->name + path;
      par = par->parent;
    }
    path = par->name + path;
  }
  return path;
}

//Deletes a directory and it's children
void fs::rmdir(string name){
  if(name[name.length() - 1] != '/'){
    cout << "Direcotry names must end with '/'!\n";
    return;
  }

  fsNode* dir;
  vector<fsNode*>::iterator index;

  for(vector<fsNode*>::iterator i = mcurr->child.begin(); i != mcurr->child.end(); ++i){
    if(name == (*i)->name){
      dir = *i;
      index = i;
      break;
    }else{
      dir = nullptr;
    }
  }

  if(dir == nullptr){
    cout << "Directory not found!\n";
    return;
  }else{
    clean(dir);
    mcurr->child.erase(index);
  }

  return;
}

//updates timestamp, or creates file if it doesn't exsist
void fs::touch(string name){
  if(name[name.length() - 1]  == '/'){
    cout << "File names can not end with '/'!\n";
    return;
  }

  fsNode* file = find(name);

  if(file == nullptr){
    mcurr->child.push_back(new fsNode);
    fsNode* proto = mcurr->child.back();

    proto->name = name;
    setAccessF(proto->access);
    proto->owner = proto->group = muser;
    proto->timestamp = getTime();
    proto->parent = mcurr;
  }else{
    file->timestamp = getTime();
  }

  return;
}

//Removes a given file
void fs::rm(string name){
   if(name[name.length() - 1] == '/'){
    cout << "File names must not end with '/'!\n";
    return;
  }

  fsNode* file;
  vector<fsNode*>::iterator index;

  for(vector<fsNode*>::iterator i = mcurr->child.begin(); i != mcurr->child.end(); ++i){
    if(name == (*i)->name){
      file = *i;
      index = i;
      break;
    }else{
      file = nullptr;
    }
  }

  if(file == nullptr){
    cout << "File not found!\n";
    return;
  }else{
    clean(file);
    mcurr->child.erase(index);
  }

  return; 
}

//Edits the permissions of a given entity
void fs::chmod(string perm, string name){
  fsNode* entity = find(name);

  if(entity == nullptr){
    cout << "Nothing with that name was found\n";
    return;
  }

  for(int i = 1; i < 10; i++)
    entity->access[i] = '-';

  switch(perm[0]){
    case '7':
      entity->access[1] = 'r';
    case '4':
      entity->access[2] = 'w';
    case '1':
      entity->access[3] = 'x';
      break;
    case '6':
      entity->access[1] = 'r';
      entity->access[2] = 'w';
      break;
    case '0':
      break;
    default:
      cout << "Invalid input\nMust be in the form: chmod <permission code> <entity name>\n";
      return;
  }

  switch(perm[1]){
    case '7':
      entity->access[4] = 'r';
    case '4':
      entity->access[5] = 'w';
    case '1':
      entity->access[6] = 'x';
      break;
    case '6':
      entity->access[4] = 'r';
      entity->access[5] = 'w';
      break;
    case '0':
      break;
    default:
      cout << "Invalid input\nMust be in the form: chmod <permission code> <entity name>\n";
      return;
  }

  switch(perm[2]){
    case '7':
      entity->access[7] = 'r';
    case '4':
      entity->access[8] = 'w';
    case '1':
      entity->access[9] = 'x';
      break;
    case '6':
      entity->access[4] = 'r';
      entity->access[5] = 'w';
      break;
    case '0':
      break;
    default:
      cout << "Invalid input\nMust be in the form: chmod <permission code> <entity name>\n";
      return;
  }

  return;
}
