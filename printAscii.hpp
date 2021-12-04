#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#define RED "\x1b[31m";
#define GREEN "\x1b[32m";
#define BLUE "\x1b[34m";
#define WHITE "\x1b[37m";
using namespace std;


void sleep(std::chrono::duration<double> time) {
  std::this_thread::sleep_for(time);
}

void display() {
}
void printAscii(string fileName) {
  string line = "";
  ifstream infile;
  infile.open(fileName);
  if(infile.is_open())
  {
    while(getline(infile, line))
    {
      cout << line << endl;
      sleep(0.01s);
    }
  }
  infile.close(); 
}