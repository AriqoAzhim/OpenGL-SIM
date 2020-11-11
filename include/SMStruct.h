#pragma once
struct ModuleFlags
{
    unsigned char PM : 1,
        GPS : 1, Laser : 1, OpenGL : 1, Vehicle : 1, Camera : 1, Unused : 2;

};

// union uses the same memory region but casts data in different types
union ExecFlags
{
    unsigned char Status;
    ModuleFlags Flags;
};

struct ProcessManagement
{
	ExecFlags Heartbeats;
	ExecFlags PMHeartbeats;
	ExecFlags Shutdown;
	int WAIT_COUNT[6];
	int LIMIT;
};

struct Laser
{
	double x[361];
	double y[361];
	int NumPoints;
};