/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"
#include <limits>
#include <iostream>

using namespace std;


size_t PageTable::get_present_page_count() const {
  size_t x = 0;
  for(Row r : rows){
    if(r.present == true)
      x +=1;
  }
  return x;
}


size_t PageTable::get_oldest_page() const {
  size_t index = 0;
  size_t oldest = numeric_limits<size_t>::max();
  for(unsigned int i = 0; i < rows.size(); i++){
    if(rows[i].loaded_at < oldest && rows[i].present == true){
      oldest = rows[i].loaded_at;
      index = i;
    }
  }

  return index;
}


size_t PageTable::get_least_recently_used_page() const {
  size_t i = 0;
  size_t index =0;
  size_t oldest = numeric_limits<size_t>::max();
  for(Row r : rows){
    if(r.last_accessed_at < oldest && r.present == true){
      index = i;
      oldest = r.last_accessed_at;
    }
    i++;
  }
  return index;
}
