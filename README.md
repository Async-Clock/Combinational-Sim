# Combinational-Sim

This repository contains the source code for a cycle based combinational digital circuit simulator. 

# Input

The program expects three command line arguments:

- A .isc file describing a combinational circuit
- A filename for storing the results of the simulation
- A file containing the test vectors for simulation

# Output

The program outputs a text file containing simulation results. For debugging purposes, the simulation file contains both the primary inputs applied and the simulated primary outputs. 

## Notation

The simulation results written to the file can have three possible values:

  0
  1
  2
  
 Both 0 and 1 represent a logical 0 or 1, while a 2 indicates a don't care (x).
