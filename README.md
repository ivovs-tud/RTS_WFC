Wind Farm Simulation Toolset
-------------------

This repository contains the python code to simulate a wind farm flow field, and the simulink code to simulation individual turbines. This repository is intended to interface with https://github.com/ivovs-tud/IEC61850ServerPLC.

OFF
---
The code in the OFF folder is a fork of the [OFF](https://github.com/TUDelft-DataDrivenControl/OFF) toolbox, that allows for sending flow field data to and receive current Ct and Yaw offsets from another application over UDP. For this to work properly, one also needs to copy the contents of the ``floris`` to your local floris installation.
Originally developed by [Áron Dömötor Kohlheb](https://github.com/arondomotorkohlheb/off_testbed/tree/main), reproduced here what was needed with modifications. 

WFSpeedgoat
-----
Contains matlab initialization scripts and Simulink files for simulation of wind turbines, including local controller, and that allows for interaction with an external flow field solver over UDP, and interaction with an external control+monitoring unit also over UDP.


This repository has been developed as part of the EU Horizon program [SUDOCO](https://sudoco.eu/).
