#include "stdafx.h"
#include "MotorNM.h"
#include "Motor.h"
#include "Player.h"
#include "CentrifugeTest.h"
#include "Motion.h"
#include "Operation.h"
#include "Subject.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void TestMotionStateMachine()
{
	// Motion motionInstance;
	// ParameterData *data = new ParameterData();
	// data->paramData.position = 1.1;
	// data->paramData.velocity = 2.2;
	// data->paramData.acceleration = 3.3;
	// data->paramData.jerk = 4.4;

	// motionInstance.Commit(data);

	// motionInstance.Start();
	// motionInstance.ResourceAcquired();

	// // Event that cannot happen.
	// // data->paramData.jerk = 5.5;
	// // motionInstance.Commit(data);

	// motionInstance.Interrupt();
}

void TestOperationOnSubject()
{
	bool done, aborted, busy, active;

	Operation op1(111);
	Operation op2(222);
	Subject sub(300);

	PseudoData testParamData;
	testParamData.value = 654;
	ParameterData *pParam = new ParameterData();
	pParam->pseudoData = testParamData;

	op1.Commit(pParam);

	// op1.candidateParameter.value = 888;
	SubjectData *pSubData = new SubjectData();
	pSubData->TargetSubject = &sub;
	op1.Start(pSubData);

	// Wait for a while so that the operation can do some work.
	// std::this_thread::sleep_for(std::chrono::seconds(3));
	// op1.Interrupt();

	// simulate another operation is acquiring the subject.
	// PseudoData testParamData2;
	// testParamData2.value = 789;
	// ParameterData *pParam2 = new ParameterData();
	// pParam2->pseudoData = testParamData2;
	// op2.Commit(pParam2);
	// SubjectData *pSubData2 = new SubjectData();
	// pSubData2->TargetSubject = &sub;
	// op2.Start(pSubData2);

	system("pause");
}

int main(void)
{
	TestOperationOnSubject();
}

int main1(void)
{
	// Create MotorNM (No Macro) test object
	MotorNM motorNM;

	// @see StateMachine.h comments
#if EXTERNAL_EVENT_NO_HEAP_DATA
	MotorNMData dataNM;
	dataNM.speed = 100;
	motorNM.SetSpeed(&dataNM);

	MotorNMData dataNM2;
	dataNM2.speed = 200;
	motorNM.SetSpeed(&dataNM2);

	motorNM.Halt();
	motorNM.Halt();

	// Create Motor object with macro support
	Motor motor;

	MotorData data;
	data.speed = 100;
	motor.SetSpeed(&data);

	MotorData data2;
	data2.speed = 200;
	motor.SetSpeed(&data2);

	motor.Halt();
	motor.Halt();
#else
	MotorNMData *dataNM = new MotorNMData();
	dataNM->speed = 100;
	motorNM.SetSpeed(dataNM);

	MotorNMData *dataNM2 = new MotorNMData();
	dataNM2->speed = 200;
	motorNM.SetSpeed(dataNM2);

	motorNM.Halt();
	motorNM.Halt();

	// Create Motor object with macro support
	Motor motor;

	MotorData *data = new MotorData();
	data->speed = 100;
	motor.SetSpeed(data);

	MotorData *data2 = new MotorData();
	data2->speed = 200;
	motor.SetSpeed(data2);

	motor.Halt();
	motor.Halt();
#endif

	// Create Player instance and call external event functions
	Player player;
	player.OpenClose();
	player.OpenClose();
	player.Play();
	player.Pause();
	player.EndPause();
	player.Stop();
	player.Play();
	player.Play();
	player.OpenClose();

	// Create CentrifugeTest and start test
	CentrifugeTest test;
	test.Cancel();
	test.Start();
	while (test.IsPollActive())
		test.Poll();

	return 0;
}
