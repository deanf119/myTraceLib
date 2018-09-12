

void trace_start(char* filename){
  ofstream file;
  file.open ("filename.txt");
  file << "[\n";
  file.close();
  return 0;
}


void trace_event_start(char* name, char* categories, char* arguments){

}
void trace_event_end(char* arguments){

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
    
}
