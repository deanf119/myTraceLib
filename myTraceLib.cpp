#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
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

string line[1000];
int linecounter= 0;
int eventcounter=0;
//string pid[1000];


int main(){

    trace_start("greeting");

    trace_event_start("Task 1", "Task 1", "Task 1");
    trace_event_start("Task 2", "Task 2", "Task 2");
    trace_event_start("Task 3", "Task 3", "Task 3");
    trace_event_start("Task 4", "Task 4", "Task 4");
    trace_event_end("Task 1");
    trace_event_end("Task 2");
    trace_event_end("Task 3");
    trace_event_end("Task 4");

    trace_flush();
    trace_end();

    return 0;
}


void trace_start(char* filename){
  file.open (filename, ios::out|ios::app);
  file << "[ \n";
}

void trace_event_start(char* name, char* categories, char* arguments){
    auto finish = std::chrono::high_resolution_clock::now();
    auto BeginTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    auto thetimeb= BeginTime/1000;
    if (linecounter== 1000)
    {
        trace_flush();
    }
    else{
    eventcounter=eventcounter+1;
    ostringstream oss;
    oss << "{ \"name\" : \""<< name << "\", \"cat\" : \"" <<categories<< "\", \"pid\" : \"1\", \"tid\" : \"1\", \"ph\" : \"B\", \"ts\" : \""<<thetimeb<<"\" },\n";
    string var = oss.str();
    line[linecounter]= var;
    linecounter= linecounter +1;
    cout<< "The value of the linecounter is " <<linecounter<<endl;
     }
}



void trace_event_end(char* arguments){
    auto finish = std::chrono::high_resolution_clock::now();
    auto EndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    auto thetimee= EndTime/1000;
    if (linecounter== 1000)
    {
        trace_flush();
    }
    else{
   eventcounter=eventcounter-1;
               if (eventcounter== 0)
                    {
                        ostringstream oss;
                        oss <<"{ \"pid\" : \"1\", \"tid\" : \"1\", \"ph\" : \"E\", \"ts\" : \""<< thetimee << "\" }\n";
                        string var = oss.str();
                        line[linecounter]=var;
                        linecounter= linecounter +1;
                        cout<< "The value of the linecounter is " <<linecounter<<endl;
                    }
                else
                    {
                        ostringstream oss;
                        oss <<"{ \"pid\" : \"1\", \"tid\" : \"1\", \"ph\" : \"E\", \"ts\" : \""<< thetimee << "\" },\n";
                        string var = oss.str();
                        line[linecounter]=var;
                        linecounter= linecounter +1;
                        cout<< "The value of the linecounter is " <<linecounter<<endl;
                    }
     }
     //testing bro
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

    for (int i=0; i<1000;i++)
    {
        file << line[i];
    }
    //reset the string array to be empty ""
    for (int i=0; i<1000;i++)
    {
       line[i]="";
    }
    // reset the linecounter to zero so that now we can start counting the next 1000 lines
    linecounter= 0;
    cout<< "Flush was just called, the value of linecounter is reset to " << linecounter<<endl;
}
void trace_end(){
  file << "]";
  file.close();
}
