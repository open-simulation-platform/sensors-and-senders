# sensors-and-senders

This repository contains source code for FMUs for generating NMEA sensor data for GPS, wind, gyro and vru sensors as well as an FMU for sending NMEA telegrams. These FMUs are used in the [virtual commissioning](https://opensimulationplatform.com/use-cases/#commissioning) use case, where they are used as network FMUs for communicating with the control systems, and in the [sensors-and-senders](https://github.com/open-simulation-platform/demo-cases/tree/master/sensors-and-senders) demo case.

**Table 1:** *List of Sensor and Sender FMUS.

| FMU          |
| ------------------|
| Wind Sensor Model
| GPS Sensor Model
| VRU Sensor Model
| Gyro Sensor Model 
| Nmea Sender


## Nmea Sender

The Nmea is an FMU capable of encoding NMEA telegrams and sending them over UDP to a specific host and port. The library itself comes with no input variables or configured telegrams and must be manually, or automatically, configured to generate telegrams. The FMU interface is configured through the modelDescription.xml file. Adding a new entry to the ModelVariables node will cause that variable to appear in the FMU interface. This is possible because the FMU reads its own modelDescription file at instantiation time. 

The telegrams are configured through the NmeaConfig.json file which must be put in the fmu's resources folder. The files defines a list of telegrams with fields where each field is name mapped to a ModelVariable in the modelDescription.xml file. The repository comes with a set of examples for gps, vru and wind sensors.

The remote host ip and port is set through FMU parameters.