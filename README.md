# Euler Solver 
Solver for integral-differential equations for first and second spatial moments using the Euler method.\
This app carries out experiments 14.4 and 14.6 (LawDieckmann200a.pdf: pages 13, 17), as well as experiments with custom input data.

The solver requires Python 3 and matplotlib to run.

Examples of the app:
- Main menu <br> <img width="480" height="304" alt="image" src="https://github.com/user-attachments/assets/d7958da8-eb38-49f9-870b-3c1b90df11eb" />
- Calculations process <br> <img width="640" height="573" alt="image" src="https://github.com/user-attachments/assets/ae4970f6-55ba-47c2-9320-4b197043b5a7" />
- Custom experiment input data example <br> <img width="185" height="251" alt="image" src="https://github.com/user-attachments/assets/30dfcfb7-10f7-4282-8e07-7c1ffdc20503" />
- Calculation results example <br> <img width="626" height="469" alt="image" src="https://github.com/user-attachments/assets/684848e9-cccb-4390-a841-0fd8c4ae223c" /> <br> <img width="628" height="474" alt="image" src="https://github.com/user-attachments/assets/9d4c584d-ccb6-40a4-afe8-bfa9604e3fb5" /> <br> <img width="629" height="478" alt="image" src="https://github.com/user-attachments/assets/e83d9f2e-870f-4b75-9496-5d919c7fa92c" />

Compatible with Windows 11 and Ubuntu 26.04

# __To build the solver using CMake:__
1. Clone this repository.
2. Build the app through the terminal using the following commands:
   Windows:
   ```
   cmake -S . -B build -G "MinGW Makefiles"
   cmake --build build
   ```
   Ubuntu:
   ```
   cmake -S . -B build
   cmake --build build
   ```
3. Move the 'data' directory and _Visualiser.py_ to the 'build' directory.

# __To run the solver:__

1. Download the latest release from the "Releases" section.
2. Run the _Solver_ executable.
3. Select an experiment.
4. To input run an experiment with custom model parameters, navigate to 'data/Custom/' directory and fill the _experiment.csv_ file according to the example present in the directory.
