/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "flag_parser/flag_parser.h"
#include "virtual_address/virtual_address.h"
#include "simulation/simulation.h"
#include "frame/frame.h"
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <deque>

/**
 * Class responsible for running the memory simulation.
 */
class Simulation {
// PUBLIC CONSTANTS
public:
  /**
   * The maximum number of frames in the simulated system (512).
   */
  static const size_t NUM_FRAMES = 1 << 9;
  FlagOptions flags;

// PUBLIC API METHODS
  public:
  
  /**
   * Runs the simulation.
   */
  void run(const std::string& filename);

// PRIVATE METHODS
private:

  /**
   * Performs a memory access for the given virtual address, translating it to
   * a physical address and loading the page into memory if needed. Returns the
   * byte at the given address.
   */
  char perform_memory_access(const VirtualAddress& address);

  /**
   * Handles a page fault, attempting to load the given page for the given
   * process into memory.
   */
  void handle_page_fault(Process* process, size_t page);

// INSTANCE VARIABLES
private:
  std::map<int,Process*> myMap;
  std::vector<VirtualAddress> myVec;
  Frame frames[512];
  std::deque<size_t> free_frames;
};
