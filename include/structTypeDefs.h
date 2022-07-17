#pragma once

typedef struct {
	XPLMDataRef p;
	XPLMDataRef q;
	XPLMDataRef r;
	XPLMDataRef ax;
	XPLMDataRef ay;
	XPLMDataRef az;
	XPLMDataRef verticalSpeed;
}Str_IMU_Datarefs;

typedef struct {
	float p;
	float q;
	float r;
	float ax;
	float ay;
	float az;
	float verticalSpeed;
	int active;
}Str_IMU;

typedef struct {
	XPLMDataRef pitch;
	XPLMDataRef yaw;
	XPLMDataRef roll;
	XPLMDataRef throttle;
}Str_steeringPlane_Datarefs;

typedef struct {
	float pitch;
	float yaw;
	float roll;
	float throttle;
	int active;
}Str_steeringPlane;

typedef struct {
	XPLMDataRef pitch;
}Str_pitch_Datarefs;

typedef struct {
	float pitch;
	int active;
}Str_pitch;

