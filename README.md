# 1-Axis Linear Actuator &amp; Trajectory Control System

### Project Overview

Engineered by a 3-person team, this project features an automated targeting robot that navigates a single-axis linear rail to execute precise ballistic trajectories.
- **Data Pipeline:** Utilizes a bi-directional communication loop. Data is collected by the Arduino kinematics engine, processed in MATLAB to extract visual target coordinates, and sent back to the Arduino for execution.
- **Core Technologies:** MATLAB Image Processing, Arduino C, Inverse Kinematics, Serial Communication.

### Movement Optimization

The system was optimized for maximum speed and minimal drive time across the rail.

- **Dynamic Pathing:** The software actively sorts the engagement sequence of targets based on their spatial distance from the fixed reloading station.
-  **Synchronous Operations:** By writing non-blocking state machines in C, the system successfully runs the reloading mechanism and linear positioning simultaneously, entirely cutting out standard process delays and idle time.
