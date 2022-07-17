#pragma once

float UpdateFlightData(float inElapsedSinceLastCall,
	float inElapsedTimeSinceLastFlightLoop,
	int inCounter,
	void* time)
{
	IMU.p = XPLMGetDataf(IMU_Datarefs.p);
	IMU.q = XPLMGetDataf(IMU_Datarefs.q);
	IMU.r = XPLMGetDataf(IMU_Datarefs.r);
	IMU.ax = XPLMGetDataf(IMU_Datarefs.ax);
	IMU.ay = XPLMGetDataf(IMU_Datarefs.ay);
	IMU.az = XPLMGetDataf(IMU_Datarefs.az);
	IMU.verticalSpeed = XPLMGetDataf(IMU_Datarefs.verticalSpeed);

    memcpy(PVOID(IMU_Buf), &IMU, sizeof(IMU));

	memcpy(&steeringPlane, steeringPlane_Buf, sizeof(steeringPlane));

    if (steeringPlane.active > 0) {
		XPLMSetDataf(steeringPlane_Datarefs.pitch, steeringPlane.pitch);
		XPLMSetDataf(steeringPlane_Datarefs.yaw, steeringPlane.yaw);
		XPLMSetDataf(steeringPlane_Datarefs.roll, steeringPlane.roll);
		XPLMSetDataf(steeringPlane_Datarefs.throttle, steeringPlane.throttle);
	}

	memcpy(&pitch, pitch_Buf, sizeof(pitch));

    if (pitch.active > 0) {
		XPLMSetDataf(pitch_Datarefs.pitch, pitch.pitch);
	}

	return 0.008;
}

void FindDataRefs()
{
	IMU_Datarefs.p = XPLMFindDataRef("sim/flightmodel/position/P_rad");
	IMU_Datarefs.q = XPLMFindDataRef("sim/flightmodel/position/Q_rad");
	IMU_Datarefs.r = XPLMFindDataRef("sim/flightmodel/position/R_rad");
	IMU_Datarefs.ax = XPLMFindDataRef("sim/flightmodel/position/local_ax");
	IMU_Datarefs.ay = XPLMFindDataRef("sim/flightmodel/position/local_ay");
	IMU_Datarefs.az = XPLMFindDataRef("sim/flightmodel/position/local_az");
	IMU_Datarefs.verticalSpeed = XPLMFindDataRef("sim/cockpit2/gauges/indicators/vvi_fpm_pilot");

	steeringPlane_Datarefs.pitch = XPLMFindDataRef("sim/cockpit2/controls/yoke_pitch_ratio");
	steeringPlane_Datarefs.yaw = XPLMFindDataRef("sim/cockpit2/controls/yoke_heading_ratio");
	steeringPlane_Datarefs.roll = XPLMFindDataRef("sim/cockpit2/controls/yoke_roll_ratio");
	steeringPlane_Datarefs.throttle = XPLMFindDataRef("sim/cockpit2/engine/actuators/prop_ratio_all");

	pitch_Datarefs.pitch = XPLMFindDataRef("sim/cockpit2/controls/yoke_pitch_ratio");

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

	steeringPlane_Handle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		steeringPlane_Mapping);

    steeringPlane_Buf = (LPTSTR)MapViewOfFile(steeringPlane_Handle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);

	pitch_Handle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		pitch_Mapping);

    pitch_Buf = (LPTSTR)MapViewOfFile(pitch_Handle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BUF_SIZE);

}

void closeSharedMem()
{
	UnmapViewOfFile(IMU_Buf);
	CloseHandle(IMU_Handle);

	UnmapViewOfFile(steeringPlane_Buf);
	CloseHandle(steeringPlane_Handle);

	UnmapViewOfFile(pitch_Buf);
	CloseHandle(pitch_Handle);

}