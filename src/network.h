#ifndef NETWORK_H
#define NETWORK_H
#include <pebble.h>
#include "weather.h"
#include "mainwindow.h"
#include "communication.h"
#include "bluetooth.h"

int m_i_Network_RefreshTime;
bool m_b_Network_VibrationEnabled;
bool m_b_Network_ConnectionState;


void Network_Request();
void Network_Handle_Reply(Tuple *network_tuple);
void Network_Init();
void Network_DeInit();
void Network_Redraw();
#endif