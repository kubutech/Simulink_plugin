#pragma once

typedef struct {
	XPLMDataRef p;
	XPLMDataRef q;
	XPLMDataRef r;
	XPLMDataRef axial_acceleration;
	XPLMDataRef normal_acceleration;
	XPLMDataRef side_acceleration;
}Str_IMU_Datarefs;

typedef struct {
	float p;
	float q;
	float r;
	float axial_acceleration;
	float normal_acceleration;
	float side_acceleration;
	int active;
}Str_IMU;

typedef struct {
	XPLMDataRef pitch;
	XPLMDataRef true_heading;
	XPLMDataRef roll;
}Str_Angles_real_Datarefs;

typedef struct {
	float pitch;
	float true_heading;
	float roll;
	int active;
}Str_Angles_real;

typedef struct {
	XPLMDataRef lat;
	XPLMDataRef lon;
	XPLMDataRef elevation;
}Str_GPS_Datarefs;

typedef struct {
	double lat;
	double lon;
	double elevation;
	int active;
}Str_GPS;

typedef struct {
	XPLMDataRef g;
}Str_Gravity_Datarefs;

typedef struct {
	float g;
	int active;
}Str_Gravity;

