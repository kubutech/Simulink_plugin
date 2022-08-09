#pragma once

float IMU_loop(float inElapsedSinceLastCall,
	float inElapsedTimeSinceLastFlightLoop,
	int inCounter,
	void* time)
{
	IMU.p = XPLMGetDataf(IMU_Datarefs.p);
	IMU.q = XPLMGetDataf(IMU_Datarefs.q);
	IMU.r = XPLMGetDataf(IMU_Datarefs.r);
	IMU.axial_acceleration = XPLMGetDataf(IMU_Datarefs.axial_acceleration);
	IMU.normal_acceleration = XPLMGetDataf(IMU_Datarefs.normal_acceleration);
	IMU.side_acceleration = XPLMGetDataf(IMU_Datarefs.side_acceleration);

	memcpy(PVOID(IMU_Buf), &IMU, sizeof(IMU));

	return 0.01;
}

float Angles_real_loop(float inElapsedSinceLastCall,
	float inElapsedTimeSinceLastFlightLoop,
	int inCounter,
	void* time)
{
	Angles_real.pitch = XPLMGetDataf(Angles_real_Datarefs.pitch);
	Angles_real.true_heading = XPLMGetDataf(Angles_real_Datarefs.true_heading);
	Angles_real.roll = XPLMGetDataf(Angles_real_Datarefs.roll);

	memcpy(PVOID(Angles_real_Buf), &Angles_real, sizeof(Angles_real));

	return 0.01;
}

float GPS_loop(float inElapsedSinceLastCall,
	float inElapsedTimeSinceLastFlightLoop,
	int inCounter,
	void* time)
{
	GPS.lat = XPLMGetDatad(GPS_Datarefs.lat);
	GPS.lon = XPLMGetDatad(GPS_Datarefs.lon);
	GPS.elevation = XPLMGetDatad(GPS_Datarefs.elevation);

	memcpy(PVOID(GPS_Buf), &GPS, sizeof(GPS));

	return 0.01;
}

float Gravity_loop(float inElapsedSinceLastCall,
	float inElapsedTimeSinceLastFlightLoop,
	int inCounter,
	void* time)
{
	Gravity.g = XPLMGetDataf(Gravity_Datarefs.g);

	memcpy(PVOID(Gravity_Buf), &Gravity, sizeof(Gravity));

	return 0.01;
}

void findDataRefs()
{
	IMU_Datarefs.p = XPLMFindDataRef("sim/flightmodel/position/Prad");
	IMU_Datarefs.q = XPLMFindDataRef("sim/flightmodel/position/Qrad");
	IMU_Datarefs.r = XPLMFindDataRef("sim/flightmodel/position/Rrad");
	IMU_Datarefs.axial_acceleration = XPLMFindDataRef("sim/flightmodel/forces/g_axil");
	IMU_Datarefs.normal_acceleration = XPLMFindDataRef("sim/flightmodel/forces/g_nrml");
	IMU_Datarefs.side_acceleration = XPLMFindDataRef("sim/flightmodel/forces/g_side");

	Angles_real_Datarefs.pitch = XPLMFindDataRef("sim/cockpit/gyros/the_ind_ahars_pilot_deg");
	Angles_real_Datarefs.true_heading = XPLMFindDataRef("sim/flightmodel/position/psi");
	Angles_real_Datarefs.roll = XPLMFindDataRef("sim/cockpit/gyros/phi_ind_ahars_pilot_deg");

	GPS_Datarefs.lat = XPLMFindDataRef("sim/flightmodel/position/latitude");
	GPS_Datarefs.lon = XPLMFindDataRef("sim/flightmodel/position/longitude");
	GPS_Datarefs.elevation = XPLMFindDataRef("sim/flightmodel/position/elevation");

	Gravity_Datarefs.g = XPLMFindDataRef("sim/weather/gravity_mss");

}

void setupSharedMem()
{
	IMU_Handle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		IMU_Mapping);

    IMU_Buf = (LPTSTR)MapViewOfFile(IMU_Handle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);

	Angles_real_Handle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		Angles_real_Mapping);

    Angles_real_Buf = (LPTSTR)MapViewOfFile(Angles_real_Handle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);

	GPS_Handle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		GPS_Mapping);

    GPS_Buf = (LPTSTR)MapViewOfFile(GPS_Handle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);

	Gravity_Handle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		Gravity_Mapping);

    Gravity_Buf = (LPTSTR)MapViewOfFile(Gravity_Handle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);

}

void closeSharedMem()
{
	UnmapViewOfFile(IMU_Buf);
	CloseHandle(IMU_Handle);

	UnmapViewOfFile(Angles_real_Buf);
	CloseHandle(Angles_real_Handle);

	UnmapViewOfFile(GPS_Buf);
	CloseHandle(GPS_Handle);

	UnmapViewOfFile(Gravity_Buf);
	CloseHandle(Gravity_Handle);

}

void initializeFlightLoops()
{
	XPLMRegisterFlightLoopCallback(IMU_loop, 0.2, NULL);
	XPLMRegisterFlightLoopCallback(Angles_real_loop, 0.2, NULL);
	XPLMRegisterFlightLoopCallback(GPS_loop, 0.2, NULL);
	XPLMRegisterFlightLoopCallback(Gravity_loop, 0.2, NULL);
}

void closeFlightLoops()
{
	XPLMUnregisterFlightLoopCallback(IMU_loop, NULL);
	XPLMUnregisterFlightLoopCallback(Angles_real_loop, NULL);
	XPLMUnregisterFlightLoopCallback(GPS_loop, NULL);
	XPLMUnregisterFlightLoopCallback(Gravity_loop, NULL);
}