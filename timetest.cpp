//Kevin Newell
//A test file for getting the time from OS

#include<iostream>
#include<ctime>

using namespace std;

int main(){
  time_t t = time(0); //Gets time now
  struct tm * now = localtime(&t);

  cout << asctime(now);

  return 0;
}
