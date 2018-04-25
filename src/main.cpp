/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include "simulation/simulation.h"
#include "flag_parser/flag_parser.h"

using namespace std;

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
  FlagOptions flags;
  if(!parse_flags(argc, argv, flags)) return EXIT_FAILURE;
  // Logger logger(flags.verbose, flags.detailed);

  // Create the simulation.
  Simulation simulation;

  // Execute the simulation on the provided file.
  simulation.run(flags.filename);

  return EXIT_SUCCESS;
}
