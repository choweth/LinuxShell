/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  size_t num_bytes = 0;
  Page* p;
  vector<Page*> pages;
  while((p = Page::read_from_input(in)) != nullptr){
    pages.push_back(p);
    num_bytes += p->size();
  }
  Process* proc = new Process(num_bytes, pages);
  return proc;
}


size_t Process::size() const {
  return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  return (index < pages.size() && pages[index]);
}


size_t Process::get_rss() const {
  return page_table.get_present_page_count();
}


double Process::get_fault_percent() const {
  if(memory_accesses > 0){return (double)page_faults / memory_accesses * 100;}
  else return 0;
}
