/**************************************************
Name: Kevin Newell
Date: 9/2/18
Class: cs3800B
Instr: Wilkerson
Desc: Create a Linux terminal emulator supporting
the commands: ls, ls -l, cd, pwd, mkdir, rmdir, rm
chmod, touch, and exit/quit
**************************************************/

#include"filesys.h"

using namespace std;

//Breaks input into vector elements
vector<string> parse(string input);

int main(){
  string cmd = "";
  string user;
  vector<string> item;

  //Get user name
  cout << "Machine login: ";
  getline(cin, user);

  fs fsys(user);
 
  //Main loop
  while(cmd != "exit" && cmd != "quit"){
    cout << "\n" << fsys.muser << "@Machine" << '(' << fsys.pwd() << ")$ ";
    getline(cin, cmd);

    //Command execution structure
    item = parse(cmd);

    if(item[0] == "exit" || item[0] == "quit"){
      cout << "Shutting down... Have a good day" << endl;
      break;

      //ls
    }else if(item[0] == "ls"){
      if(item.size() < 2)
        item.push_back("");
      cout << fsys.ls(item[1]);

      //mkdir
    }else if(item[0] == "mkdir"){
      if(item.size() < 2){
        cout << "No name specified\n";
	continue;
      }
      fsys.mkdir(item[1]);

      //pwd
    }else if(item[0] == "pwd"){
      cout << fsys.pwd();

      //cd
    }else if(item[0] == "cd"){
      if(item.size() < 2){
        cout << "No dir specified\n";
	continue;
      }
      fsys.cd(item[1]);

      //rmdir
    }else if(item[0] == "rmdir"){
      if(item.size() < 2){
        cout << "No dir specified\n";
	continue;
      }
      fsys.rmdir(item[1]);

      //touch
    }else if(item[0] == "touch"){
      if(item.size() < 2){
        cout << "No file specified\n";
	continue;
      }
      fsys.touch(item[1]);

      //rm
    }else if(item[0] == "rm"){
      if(item.size() < 2){
        cout << "No file specified\n";
	continue;
      }
      fsys.rm(item[1]);

    }else if(item[0] == "chmod"){
      if(item.size() < 3){
        cout << "Invalid input\nMust be in the form: chmod <permission code> <entity name>\n";
	continue;
      }

      fsys.chmod(item[1], item[2]);
    }else{
      cout << "Unrecognized command\n";
    }
  }
  
  return 0;
}

vector<string> parse(string input){
  vector<string> out;
  string seg = "";

  for(int i = 0; i < input.length(); i++){
    if(input[i] == ' '){
      out.push_back(seg);
      seg = "";
    }else{
      seg += input[i];
    }
  }

  if(seg != "")
    out.push_back(seg);

  return out;
}
