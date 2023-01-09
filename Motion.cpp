#include "Motion.h"
#include <iostream>

Motion::Motion() : StateMachine(ST_MAX_STATES, ST_IDLE)
{
}

Motion::~Motion()
{
}

// state machine sits here when Motion is not running
STATE_DEFINE(Motion, Idle, NoEventData)
{
	std::cout << "Motion::ST_Idle" << std::endl;
}

STATE_DEFINE(Motion, ParametersCommited, ParameterData)
{
	std::cout << "Motion::ST_PARAMETERS_COMMITED" << std::endl;

	this->current_parameter = data->paramData;
	std::cout << " ================ ST_PARAMETERS_COMMITED ===================" << std::endl;
	std::cout << "Target Position: " << this->current_parameter.position << std::endl;
	std::cout << "Velocity: " << this->current_parameter.velocity << std::endl;
	std::cout << "Acceleration: " << this->current_parameter.acceleration << std::endl;
	std::cout << "Jerk: " << this->current_parameter.jerk << std::endl;
	std::cout << " ==================================================== " << std::endl;
	// data->paramData
}

STATE_DEFINE(Motion, PendingExecute, NoEventData)
{
	std::cout << "Motion::ST_PENDING_EXECUTE" << std::endl;
}

STATE_DEFINE(Motion, Running, NoEventData)
{
	std::cout << "Motion::ST_RUNNING" << std::endl;
	std::cout << " ========= Running with current kinetic parameters ======= " << std::endl;
	std::cout << "Target Position: " << this->current_parameter.position << std::endl;
	std::cout << "Velocity: " << this->current_parameter.velocity << std::endl;
	std::cout << "Acceleration: " << this->current_parameter.acceleration << std::endl;
	std::cout << "Jerk: " << this->current_parameter.jerk << std::endl;
	std::cout << " ==================================================== " << std::endl;
}

STATE_DEFINE(Motion, Aborted, NoEventData)
{
	std::cout << "Motion::ST_ABORTED" << std::endl;
	InternalEvent(ST_IDLE);
}

STATE_DEFINE(Motion, Done, NoEventData)
{
	std::cout << "Motion::ST_DONE" << std::endl;
	InternalEvent(ST_IDLE);
}

void Motion::Commit(ParameterData *param)
{
	BEGIN_TRANSITION_MAP						 // - Current State -
	TRANSITION_MAP_ENTRY(ST_PARAMETERS_COMMITED) // ST_IDLE
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)		 // ST_PARAMETERS_COMMITED
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)		 // ST_PENDING_EXECUTE
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)		 // ST_RUNNING
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)		 // ST_ABORTED
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)		 // ST_DONE
		END_TRANSITION_MAP(param)
}

void Motion::Start()
{
	BEGIN_TRANSITION_MAP					// - Current State -
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_IDLE
		TRANSITION_MAP_ENTRY(ST_RUNNING)	// ST_PARAMETERS_COMMITED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_PENDING_EXECUTE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_RUNNING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORTED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
		END_TRANSITION_MAP(nullptr)
}

void Motion::ResourceAcquired()
{
	BEGIN_TRANSITION_MAP					// - Current State -
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_IDLE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_PARAMETERS_COMMITED
		TRANSITION_MAP_ENTRY(ST_RUNNING)	// ST_PENDING_EXECUTE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_RUNNING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORTED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
		END_TRANSITION_MAP(nullptr)
}

void Motion::TrajectoryCompleted()
{
	BEGIN_TRANSITION_MAP					// - Current State -
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_IDLE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_PARAMETERS_COMMITED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_PENDING_EXECUTE
		TRANSITION_MAP_ENTRY(ST_DONE)		// ST_RUNNING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORTED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
		END_TRANSITION_MAP(nullptr)
}

void Motion::Interrupt()
{
	BEGIN_TRANSITION_MAP					// - Current State -
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_IDLE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_PARAMETERS_COMMITED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_PENDING_EXECUTE
		TRANSITION_MAP_ENTRY(ST_ABORTED)	// ST_RUNNING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORTED
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
		END_TRANSITION_MAP(nullptr)
}
