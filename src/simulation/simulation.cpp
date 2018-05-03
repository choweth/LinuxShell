/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include "physical_address/physical_address.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void Simulation::run(const std::string& filename) {
  vector<int> procIDs;
  string line, temp, proc;
  int numProcesses = 0;
  ifstream file (filename);
  if(file.is_open()){
    // while(!file.eof()){
    getline(file,line);
    numProcesses = stoi(line, 0);
    for(int i = 0; i < numProcesses; i++){
      getline(file,line);
      temp = line.substr(0,line.find(" "));
      line.erase(0, line.find(" ") + 1);
      // cout << "STR1: " << temp << "; STR2: " << line << endl;
      ifstream subFile(line);
      getline(subFile,line);
      stringstream ss(line);
      myMap[stoi(temp,0)]=Process::read_from_input(ss);
      subFile.close();
      procIDs.push_back(stoi(temp,0));
    }
    int i = 0;
    getline(file,line);
    while(!file.eof()){
      getline(file,line);
      if(line == "") continue;
      // cout << "LINE: " << line << endl;
      proc = line.substr(0,line.find(" "));
      line.erase(0,line.find(" ")+1);
      myVec.push_back(VirtualAddress::from_string(stoi(proc,0),line));
      free_frames.push_back(i);
      i++;
    }
  }
  file.close();

  for(size_t i = 0 ; i < myVec.size(); i++){
    perform_memory_access(myVec.at(i));
  } 
  
  cout << "DONE!" << endl << endl;
  int totalAccesses = 0, totalFaults = 0, freeFrames = 512;
  for(int j = 0; j < procIDs.size(); j++){
    cout << "Process " << procIDs.at(j) << ": " << 
	    "ACCESSES: " << myMap.find(procIDs.at(j))->second->memory_accesses << 
	    "     FAULT: " << myMap.find(procIDs.at(j))->second->page_faults <<
	    "     FAULT RATE: " << myMap.find(procIDs.at(j))->second->get_fault_percent() <<
	    "     RSS: " << myMap.find(procIDs.at(j))->second->get_rss() << endl;
    totalAccesses += myMap.find(procIDs.at(j))->second->memory_accesses;
    totalFaults += myMap.find(procIDs.at(j))->second->page_faults;
    freeFrames -= myMap.find(procIDs.at(j))->second->get_rss();
  }
  cout << endl;
  cout << "Total Memory Accesses: " << totalAccesses << endl;
  cout << "Total Page Faults: " << totalFaults << endl;
  cout << "Free Frames Remaining: " << freeFrames << endl;
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  Process* proc = myMap.find(address.process_id)->second;
  bool fault;
  if(!proc->page_table.rows[address.page].present){
    handle_page_fault(proc, address.page);
    fault = true;
  }
  else fault = false;

  proc->page_table.rows[address.page].last_accessed_at = proc->memory_accesses;

  if(flags.verbose){
    cout << address << endl;
    if(fault) cout << "  -> PAGE FAULT" << endl;
    else cout << "  -> IN MEMORY" << endl;

    PhysicalAddress* addr = new PhysicalAddress(proc->page_table.rows[address.page].frame, address.offset);

    cout << "  -> Physical Address " << *addr << endl;
    cout << "  -> RSS: " << proc->get_rss() << endl << endl;
  }

  proc->memory_accesses++;

  return 0;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  size_t frame = process->page_table.rows[page].frame;
  if(process->get_rss() >= flags.max_frames || free_frames.empty()){
    size_t page_to_replace = (flags.strategy == ReplacementStrategy::FIFO)
      ? process->page_table.get_oldest_page()
      : process->page_table.get_least_recently_used_page();
    auto& row = process->page_table.rows[page_to_replace];
    frame = row.frame;
    row.loaded_at = -1;
    row.present = false;
  }
  else{
    frame = free_frames.front();
    free_frames.pop_front();
  }

  process->page_table.rows[page].present = true;
  process->page_table.rows[page].frame = frame;
  process->page_table.rows[page].loaded_at = process->memory_accesses;
  frames[frame].process = process;
  frames[frame].page_number = page;
  frames[frame].contents = process->pages[page];

  process->page_faults++;

}
