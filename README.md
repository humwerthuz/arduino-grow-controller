# Arduino Grow Controller [DRAFT]

## The What
Arduino Grow Controller is a Diy project intended to build a fully customizable
Grow Room Controller with live dashboards (leveraging Grafana's power). The basic idea is to handle temperature, 
lighting, CO2 and _fertigating_ while exposing historic and current parameters in a dashboard.

## The How
In the guts is an ESP32 (NodeMCU version) with I/O to handle
* Analog inputs
* RS232 Comms (for MH-Z19b CO2 sensor, sensor is 5vTTL but more on this later)
* Digital Inputs (Needed for OneWire Protocol, RTC, etc.)
* Digital Outputs to handle isolated relays (Needed to control fans, CO2 valves, AC, etc.)

The ESP32 sinks sensor readings to a REST API, which can be implemented using GCP CloudFunctions.
Then, in the reference design, the API stores the information in a BigQuery Table,
to finally set up grafana with bigQuery DataSource to read that table and done.



## The Why
For the fun of it!