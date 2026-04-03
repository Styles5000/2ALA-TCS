# 1ALA-TCS
1-Axis Linear Actuator &amp; Trajectory Control System

Project Overview
This semester-long project focused on engineering an automated robotic system capable of precise ballistic targeting. The robot operates on a single-axis linear rail, utilizing image processing to identify target coordinates and inverse kinematics to calculate required launch trajectories.

Movement Optimization
To minimize the overall drive time, the control logic heavily optimizes the robot's travel path. Because the system must return to a fixed reloading station after every shot, the software dynamically sequences the targets based on their distance from the reloader. By implementing non-blocking state machines in C++, the linear positioning and reloading mechanisms operate synchronously, significantly reducing idle time during the run.
