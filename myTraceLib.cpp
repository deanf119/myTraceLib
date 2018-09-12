#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
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
auto start = std::chrono::high_resolution_clock::now();

int main(){

    trace_start("greeting");

    trace_event_start("Task 1", "Task 1", "Task 1");
    trace_event_start("yolo1", "yolo1", "yolo1");
    trace_event_start("yolo2", "yolo2", "yolo2");
    trace_event_start("yolo3", "yolo3", "yolo3");
    trace_event_end("yolo");
    trace_event_end("yolo");
    trace_event_end("yolo");
    trace_event_end("yolo");

    trace_end();

    return 0;
}


void trace_start(char* filename){
  file.open (filename, ios::out|ios::app);
  file << "[ \n";
}

void trace_event_start(char* name, char* categories, char* arguments){
    auto finish = std::chrono::high_resolution_clock::now();
    int BeginTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  file << " {\"name\" : \"" << name << "\","
       << " \"cat\" : \"" << categories << "\","
       << " \"pid\" : \"" << "1" << "\","
       << " \"tid\" : \"" << "1" << "\","
       << " \"ph\" : \"" << "B" << "\","
       << " \"ts\" : \"" << (BeginTime/1000) << "\"},"
       << "\n";
}



void trace_event_end(char* arguments){
    auto finish = std::chrono::high_resolution_clock::now();
    int EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  file << " {\"pid\" : \"" << "1" << "\","
       << " \"tid\" : \"" << "1" << "\","
       << " \"ph\" : \"" << "E" << "\","
       << " \"ts\" : \"" << (EndTime/1000) << "\"},"
       << "\n";
}
void trace_instant_global(char* name){

}
void trace_object_new(char* name, void* obj_pointer){

}
void trace_object_gone(char* name, void* obj_pointer){

}
void trace_counter(char* name, char* key, char* value){

}
void trace_flush(){

}
void trace_end(){
  file << "\n ]";
  file.close();
}
