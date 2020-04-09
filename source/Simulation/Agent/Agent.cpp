#include "Simulation/Agent/Agent.h"
#include "Simulation/Jobs/Base/Job.h"

Agent::Agent(Job* job)
	: AgentJob(job){
}

Agent::~Agent() {
}

void Agent::Begin() {
}

void Agent::Update(float dt) {
}

