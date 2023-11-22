//
// Created by hrojasc on 11/22/2023.
//

#ifndef GROW_CONTROLLER_NODEMCU32S_CONSTANTS_H
#define GROW_CONTROLLER_NODEMCU32S_CONSTANTS_H

// Tags
extern char const *TagTemperatureEvent;
extern char const *TagFanEvent;
extern char const *TagOn;
extern char const *TagOff;
extern char const *TagRelayEvent;


// Temperature probes
extern const uint8_t TemperatureProbeAddresses[][8];

// SSL Certs
extern const char* google_apis_root_ca;

#endif //GROW_CONTROLLER_NODEMCU32S_CONSTANTS_H
