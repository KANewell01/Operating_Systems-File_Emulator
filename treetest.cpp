//Kevin Newell
//Prototyping the tree file structure

#include<iostream>
#include<string>
#include<vector>

using namespace std;

/*
 * Tree structure
 */

struct node{
  node(string input);

  string data;
  node* parent;
  vector<node*> child;
};

class tree{
  public:
    tree();
    ~tree();
    void insert(string in);
    void move(string tgt);

  private:
    node* find(string name);
    void clear(node* n);

    node* curr;
    node* root;
};

node::node(string input){
  data = input;
}

/*
 * Tree implement functions
 */

tree::tree(){
  root = new node("/");
  root->parent = nullptr;

  curr = root;
}

void tree::clear(node* n){
  for(vector<node*>::iterator i = n->child.begin(); i != n->child.end(); ++i){
    if(*i != nullptr){
      clear(*i);
    }
  }

  delete n;
  n = nullptr;
  return;
}

tree::~tree(){
  clear(root);
}

void tree::insert(string in){
  curr->child.push_back(new node(in));

  node* proto = curr->child.back();
  proto->parent = curr;

  return;
}

node* tree::find(string name){
  for(vector<node*>::iterator i = curr->child.begin(); i != curr->child.end(); ++i){
    if(name == (*i)->data){
      return *i;
    }
  }

  return nullptr;
}

void tree::move(string tgt){
  if(tgt == ".."){
    curr = curr->parent;
  }else{
    node* temp = find(tgt);
    if(temp != nullptr){
      curr = temp;
    }else{
      cout << "The file was not found\n";
    }
  }

  return;
}

/*
 * Main Section
 */

int main(){
  tree files;

  files.insert("home/");
  files.insert("etc/");
  files.move("home/");
  files.insert("user/");

  return 0;
}
