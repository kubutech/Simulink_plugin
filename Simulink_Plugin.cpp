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

	//Create shared memory pools
	setupSharedMem();

	//Find datarefs requires for plugin
	findDataRefs();

	//register loops for updating variables
	initializeFlightLoops();

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	//unregister active FlightLoops
	closeFlightLoops();

	//Close shared memory pools
	closeSharedMem();
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }
