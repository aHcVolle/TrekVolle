#ifndef NETWORK_H
#define NETWORK_H
#include <pebble.h>
#include "weather.h"
#include "mainwindow.h"
#include "communication.h"
#include "gbitmap_color_palette_manipulator.h"

int NetworkRefreshTime;

void RequestNetwork();
void HandleNetworkReply(Tuple *network_tuple);
void InitNetwork();
void DeInitNetwork();
void RedrawNetworkImage();
#endif