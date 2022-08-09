#pragma once
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMPlugin.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "structTypeDefs.h"

#define BUF_SIZE 64

TCHAR IMU_Mapping[] = TEXT("IMU");
HANDLE IMU_Handle;
LPCTSTR IMU_Buf;
Str_IMU_Datarefs IMU_Datarefs;
Str_IMU IMU;

TCHAR Angles_real_Mapping[] = TEXT("Angles_real");
HANDLE Angles_real_Handle;
LPCTSTR Angles_real_Buf;
Str_Angles_real_Datarefs Angles_real_Datarefs;
Str_Angles_real Angles_real;

TCHAR GPS_Mapping[] = TEXT("GPS");
HANDLE GPS_Handle;
LPCTSTR GPS_Buf;
Str_GPS_Datarefs GPS_Datarefs;
Str_GPS GPS;

TCHAR Gravity_Mapping[] = TEXT("Gravity");
HANDLE Gravity_Handle;
LPCTSTR Gravity_Buf;
Str_Gravity_Datarefs Gravity_Datarefs;
Str_Gravity Gravity;


XPLMFlightLoopID loopDataref;
XPLMFlightLoopID loopFlightData;

#include "Simulink_plugin_functions.h"