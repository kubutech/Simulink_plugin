#include "Simulink_Plugin.h"

#if IBM
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#elif __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifndef XPLM301
#error This is made to be compiled against the XPLM301 SDK
#endif


PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	strcpy(outName, "Simulink_Plugin");
	strcpy(outSig, "kuba.projects.Simulink_plugin");
	strcpy(outDesc, "Przesyla i odbiera dane z bloków Simulink");

	setupSharedMem();

	//loop for updating message
	XPLMCreateFlightLoop_t flightDataLoopParams;
	flightDataLoopParams.structSize = sizeof(flightDataLoopParams);
	flightDataLoopParams.callbackFunc = UpdateFlightData;
	flightDataLoopParams.phase = 1;
	flightDataLoopParams.refcon = NULL;

	loopFlightData = XPLMCreateFlightLoop(&flightDataLoopParams);

	XPLMScheduleFlightLoop(loopFlightData, 0.5, 2);

	FindDataRefs();

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	XPLMDestroyFlightLoop(loopFlightData);
	XPLMDestroyFlightLoop(loopDataref);
	closeSharedMem();
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }
