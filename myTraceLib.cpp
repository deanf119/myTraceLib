/**
 * File: myTraceLib.cpp
 * Authors: Dean Fernandes and Sheel Soneji
 * Last Update: September 24th, 2018
 * Functionality: To check the trace time for individual processes and threads for another function.
*/

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
void trace_object_snap(char* name, void* obj_pointer, void* snap_dump);
void trace_counter(char* name, char* key, char* value);
void trace_flush();
void trace_end();




ofstream file;

std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

string line[10000];
int linecounter= 0;
int eventcounter=0;
//string pid[1000];


int main(){

    trace_start("greeting");

    trace_object_new("TaskObject", NULL);
    trace_instant_global("Task_Instant");
    trace_counter("TaskCounter", "cat" , "10");
    trace_event_start("Task 1", "Task 1", "Task 1");
    trace_event_start("Task 2", "Task 2", "Task 2");
    trace_event_start("Task 3", "Task 3", "Task 3");
    trace_event_start("Task 4", "Task 4", "Task 4");
    //trace_object_snap("TaskObject", NULL, NULL); --------> dont test, not working
    trace_event_end("Task 1");
    trace_event_end("Task 2");
    trace_event_end("Task 3");
    trace_event_end("Task 4");
    trace_object_gone("TaskObject", NULL);

    trace_end();

    return 0;
}


/**
 * Function: trace_start
 * Arguments: filename of the trace output
*/
void trace_start(char* filename){
  file.open (filename, ios::out|ios::app);
  file << "[ \n";
}


/**
 * Function: trace_event_start
 * Arguments: name, category and extra arguments of a task
*/
void trace_event_start(char* name, char* categories, char* arguments){
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
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


/**
 * Function: trace_event_end
 * Arguments: extra arguments of a task
*/
void trace_event_end(char* arguments){
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
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

/**
 * Function: trace_instant_global
 * Arguments: name of task
*/
void trace_instant_global(char* name){
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  long int thetimei = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  auto finish = std::chrono::high_resolution_clock::now();
  auto EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  auto thetimeI= EndTime/1000;
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
    cout<< "The value of the linecounter is " <<linecounter<<endl;
    oss <<"{ \"name\" : \""<< name << "\", \"pid\" : \"" << to_string(getpid()) << "\", \"tid\" : \"1\", \"ph\" : \"i\", \"s\" : \"g\", \"ts\" : \""<<thetimeI<<"\" },\n";
    string var = oss.str();
    line[linecounter]=var;
    linecounter= linecounter +1;
    cout<< "The value of the linecounter is " <<linecounter<<endl;
    */
  }
}

/**
 * Function: trace_object_new
 * Arguments: name of object and pointer to object
*/
void trace_object_new(char* name, void* obj_pointer){
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
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
 * Function: trace_object_gone
 * Arguments: name of object and pointer to object
*/
void trace_object_gone(char* name, void* obj_pointer){
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
  long int thetimeD = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  if (linecounter== 10000)
  {
    trace_flush();
  }
  else{
    eventcounter=eventcounter-1;
    if (eventcounter== 0){
        ostringstream oss;
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

/**
 * Function: trace_object_snap
 * Arguments: name of object, pointer to object and pointer to future dump file (Type of argument yet to be determined)
 * you need key and value as well as you want to rpint them out on line 235, also this isn't a part of required functions according to Karol
 * so why are we doing this lol??
*/
void trace_object_snap(char* name, void* obj_pointer, void* snap_dump){
  auto finish = std::chrono::high_resolution_clock::now();
  auto EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  auto thetimeC= EndTime/1000;
  if (linecounter== 10000)
  {
    trace_flush();
  }
  else{
    ostringstream oss;
    // it is not possible to add the value of the "key" and "value" in the oss below as key and value are not in the scope of this function.
    //oss <<"{ \"name\" : \""<< name << "\", \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"C\", \"ts\" : \""<< thetimeC <<"\",  \"args\" : {\"" << key << "\" : \"" << value << "\"} },\n";
    oss <<"{ \"name\" : \""<< name << "\", \"pid\" : \"" << getpid() << "\", \"tid\" : \"1\", \"ph\" : \"O\", \"ts\" : \""<< thetimeC <<"\",  \"args\" : {\"snapshot\": {\"" << snap_dump << "\"} },\n";
    string var = oss.str();
    line[linecounter]=var;
    linecounter= linecounter +1;
    cout<< "The value of the linecounter is " <<linecounter<<endl;
  }
}

/**
 * Function: trace_counter
 * Arguments: name of object, key and value of arguments.
*/
void trace_counter(char* name, char* key, char* value){
  std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
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

/**
 * Function: trace_flush
 * Arguments: none
*/
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

/**
 * Function: trace_end
 * Arguments: none
*/
void trace_end(){
  trace_flush();
  file << "]";
  file.close();
}
