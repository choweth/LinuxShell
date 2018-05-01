/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"
#include <string>
#include <bitset>

using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  string str1 = address.substr(0,PAGE_BITS);
  string str2 = address.substr(PAGE_BITS, OFFSET_BITS);
  int x1 = stoi(str1,nullptr,2);
  int x2 = stoi(str2,nullptr,2);
  return VirtualAddress(process_id, x1, x2);
}


string VirtualAddress::to_string() const {
  string str1 = bitset<PAGE_BITS>(page).to_string();
  string str2 = bitset<OFFSET_BITS>(offset).to_string();
  return str1 + str2;
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  return out << "PID " + to_string(address.process_id) + " @ " + address.to_string() + " [page: " + to_string(address.page) + "; offset: " + to_string(address.offset) + "]";
}
