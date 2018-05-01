/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <string>
#include <bitset>

using namespace std;


string PhysicalAddress::to_string() const {
  string str1;
  string str2;
  // string temp;
  // PhysicalAddress adr;
  str1 = bitset<FRAME_BITS>(frame).to_string();
  str2 = bitset<OFFSET_BITS>(offset).to_string();
  return str1 + str2;
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  return out << address.to_string() + " [frame: " + to_string(address.frame) + "; offset: " + to_string(address.offset) + "]";
}
