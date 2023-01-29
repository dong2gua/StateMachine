#pragma once
#include "StateMachine.h"

struct KineticParam
{
	double position;
	double velocity;
	double acceleration;
	double jerk;
};

class MotionParameterData : public EventData
{
public:
	KineticParam paramData;
};

class Motion : public StateMachine
{
public:
	Motion();
	virtual ~Motion();

	// External event
	void Commit(MotionParameterData *param);
	void Start();
	void ResourceAcquired();
	void TrajectoryCompleted();
	void Interrupt();

private:
	KineticParam current_parameter;
	// State enumeration order must match the order of state method entries
	// in the state map.
	enum States
	{
		ST_IDLE,
		ST_PARAMETERS_COMMITED,
		ST_PENDING_EXECUTE,
		ST_RUNNING,
		ST_ABORTED,
		ST_DONE,
		ST_MAX_STATES
	};

	// Define the state machine state functions with event data type
	STATE_DECLARE(Motion, Idle, NoEventData)
	STATE_DECLARE(Motion, ParametersCommited, MotionParameterData)
	STATE_DECLARE(Motion, PendingExecute, NoEventData)
	STATE_DECLARE(Motion, Running, NoEventData)
	STATE_DECLARE(Motion, Aborted, NoEventData)
	STATE_DECLARE(Motion, Done, NoEventData)

	// State map to define state object order. Each state map entry defines a
	// state object.
	BEGIN_STATE_MAP
	STATE_MAP_ENTRY(&Idle)
	STATE_MAP_ENTRY(&ParametersCommited)
	STATE_MAP_ENTRY(&PendingExecute)
	STATE_MAP_ENTRY(&Running)
	STATE_MAP_ENTRY(&Aborted)
	STATE_MAP_ENTRY(&Done)
	END_STATE_MAP
};
