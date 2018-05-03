/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  vector<char> v;
  if(in){
    char c;
    size_t x = 0;
    while(x < PAGE_SIZE){
      if(in.get(c)){
	v.push_back(c);
      }
      x++;
    }
    if(v.empty()) return NULL;
    Page* p = new Page(v);
    return p;
  }
  return NULL;
}


size_t Page::size() const {
  return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  return (offset < bytes.size() && bytes[offset]);
}


char Page::get_byte_at_offset(size_t offset) {
  return bytes[offset];
}
