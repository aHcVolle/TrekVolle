#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"
#include "bluetooth.h"
#include "weather.h"
#include "network.h"
#include "time.h"

void LoadConfigFromStorage();
void SaveConfigToStorage();
void LoadDefaultConfig();

#endif