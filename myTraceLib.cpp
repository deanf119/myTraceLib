#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void trace_start(char* filename);
void trace_event_start(char* name, char* categories, char* arguments);
void trace_event_end(char* arguments);
void trace_instant_global(char* name);
void trace_object_new(char* name, void* obj_pointer);
void trace_object_gone(char* name, void* obj_pointer);
void trace_counter(char* name, char* key, char* value);
void trace_flush();
void trace_end();


ofstream file;
//auto start = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

string line[10000];
int linecounter= 0;
int eventcounter=0;
//string pid[1000];


int main(){

    trace_start("greeting");

    trace_object_new("TaskObject", NULL);
    trace_event_start("Task 1", "Task 1", "Task 1");
    trace_event_start("Task 2", "Task 2", "Task 2");
    trace_event_start("Task 3", "Task 3", "Task 3");
    trace_event_start("Task 4", "Task 4", "Task 4");
    trace_instant_global("Task_Instant");
    trace_event_end("Task 1");
    trace_event_end("Task 2");
    trace_event_end("Task 3");
    trace_event_end("Task 4");
    trace_object_gone("TaskObject", NULL);

    trace_flush();
    trace_end();

    return 0;
}


void trace_start(char* filename){
  file.open (filename, ios::out|ios::app);
  file << "[ \n";
}


void trace_event_start(char* name, char* categories, char* arguments){
    //auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    //auto BeginTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    //auto thetimeb= BeginTime/1000;
    long int thetimeb = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    if (linecounter== 10000)
    {
      trace_flush();
    }
    else{
      eventcounter=eventcounter+1;
      ostringstream oss;
      oss << "{ \"name\" : \""<< name << "\", \"cat\" : \"" <<categories<< "\", \"pid\" : \""<<getpid()<<"\", \"tid\" : \"1\", \"ph\" : \"B\", \"ts\" : \""<<thetimeb<<"\" },\n";
      string var = oss.str();
      line[linecounter]= var;
      linecounter= linecounter +1;
      cout<< "The value of the linecounter is " <<linecounter<<endl;
    }
}


void trace_event_end(char* arguments){
  //auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  //auto EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  //auto thetimee= EndTime/1000;
  long int thetimee = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  if (linecounter== 10000)
  {
    trace_flush();
  }
  else{
    eventcounter=eventcounter-1;
    if (eventcounter== 0){
        ostringstream oss;
        oss <<"{ \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"E\", \"ts\" : \""<< thetimee << "\" }\n";
        string var = oss.str();
        line[linecounter]=var;
        linecounter= linecounter +1;
        cout<< "The value of the linecounter is " <<linecounter<<endl;
      }
    else{
        ostringstream oss;
        oss <<"{ \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"E\", \"ts\" : \""<< thetimee << "\" },\n";
        string var = oss.str();
        line[linecounter]=var;
        linecounter= linecounter +1;
        cout<< "The value of the linecounter is " <<linecounter<<endl;
      }
  }
}


void trace_instant_global(char* name){
  //auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  //auto EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  //auto thetimei= EndTime/1000;
  long int thetimei = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  if (linecounter== 10000)
  {
    trace_flush();
  }
  else{
    ostringstream oss;
    oss <<"{ \"name\" : \""<< name << "\", \"pid\" : \"" << getpid()<< "\", \"tid\" : \"1\", \"ph\" : \"i\", \"s\" : \"g\", \"ts\" : \""<<thetimei<<"\" },\n";
    string var = oss.str();
    line[linecounter]=var;
    linecounter= linecounter +1;
    cout<< "The value of the linecounter is " <<linecounter<<endl;
    /*ostringstream oss;
    oss <<"{ \"name\" : \""<< name << "\", \"pid\" : \"" << to_string(getpid()) << "\", \"tid\" : \"1\", \"ph\" : \"i\", \"s\" : \"g\", \"ts\" : \""<<thetimei<<"\" },\n";
    string var = oss.str();
    line[linecounter]=var;
    linecounter= linecounter +1;
    cout<< "The value of the linecounter is " <<linecounter<<endl; */
  }
}


void trace_object_new(char* name, void* obj_pointer){
  //auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  //auto BeginTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  //auto thetimeN= BeginTime/1000;
  long int thetimeN = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  if (linecounter== 10000){
    trace_flush();
  }
  else{
    eventcounter=eventcounter+1;
    ostringstream oss;
    oss << "{ \"name\" : \""<< name << "\", \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"N\", \"id\" : \""<< obj_pointer << "\", \"ts\" : \""<<thetimeN<<"\" },\n";
    string var = oss.str();
    line[linecounter]= var;
    linecounter= linecounter +1;
    cout<< "The value of the linecounter is " <<linecounter<<endl;
  }
}
/**
 * oss << "{ \"name\" : \""<< name << "\", \"pid\" : \"1\", \"tid\" : \"1\", \"ph\" : \"D\", \"id\" : \""<< obj_pointer << "\", \"ts\" : \""<< thetimeD <<"\" }\n";
*/

void trace_object_gone(char* name, void* obj_pointer){
  //auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  //auto EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  //auto thetimeD= EndTime/1000;
  long int thetimeD = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  if (linecounter== 10000)
  {
    trace_flush();
  }
  else{
    eventcounter=eventcounter-1;
    if (eventcounter== 0){
        ostringstream oss;
        //oss << "{ \"name\" : \""<< name << "\", \"pid\" : \"" << to_string(getpid()) << "\", \"tid\" : \"1\", \"ph\" : \"D\", \"id\" : \""<< obj_pointer << "\", \"ts\" : \""<< thetimeD <<"\" }\n";
         oss << "{ \"name\" : \""<< name << "\", \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"D\", \"id\" : \""<< obj_pointer << "\", \"ts\" : \""<< thetimeD <<"\" }\n";
        string var = oss.str();
        line[linecounter]=var;
        linecounter= linecounter +1;
        cout<< "The value of the linecounter is " <<linecounter<<endl;
      }
    else{
        ostringstream oss;
        oss << "{ \"name\" : \""<< name << "\", \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"D\", \"id\" : \""<< obj_pointer << "\", \"ts\" : \""<< thetimeD <<"\" },\n";
        string var = oss.str();
        line[linecounter]=var;
        linecounter= linecounter +1;
        cout<< "The value of the linecounter is " <<linecounter<<endl;
      }
  }
}


void trace_counter(char* name, char* key, char* value){
  //auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  //auto EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  //auto thetimeC= EndTime/1000;
  long int thetimeC = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  if (linecounter== 10000)
  {
    trace_flush();
  }
  else{
    ostringstream oss;
    oss <<"{ \"name\" : \""<< name << "\", \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"C\", \"ts\" : \""<< thetimeC <<"\",  \"args\" : {\"" << key << "\" : \"" << value << "\"} },\n";
    string var = oss.str();
    line[linecounter]=var;
    linecounter= linecounter +1;
    cout<< "The value of the linecounter is " <<linecounter<<endl;
  }
}


void trace_flush(){

    for (int i=0; i<10000;i++)
    {
      file << line[i];
    }
    //reset the string array to be empty ""
    for (int i=0; i<10000;i++)
    {
      line[i]="";
    }
    // reset the linecounter to zero so that now we can start counting the next 1000 lines
    linecounter= 0;
    cout<< "Flush was just called, the value of linecounter is reset to " << linecounter<<endl;
}


void trace_end(){
  trace_flush();
  file << "]";
  file.close();
}
