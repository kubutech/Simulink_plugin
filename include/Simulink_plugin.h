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

TCHAR steeringPlane_Mapping[] = TEXT("steeringPlane");
HANDLE steeringPlane_Handle;
LPCTSTR steeringPlane_Buf;
Str_steeringPlane_Datarefs steeringPlane_Datarefs;
Str_steeringPlane steeringPlane;

TCHAR pitch_Mapping[] = TEXT("pitch");
HANDLE pitch_Handle;
LPCTSTR pitch_Buf;
Str_pitch_Datarefs pitch_Datarefs;
Str_pitch pitch;


XPLMFlightLoopID loopDataref;
XPLMFlightLoopID loopFlightData;

#include "Simulink_plugin_functions.h"