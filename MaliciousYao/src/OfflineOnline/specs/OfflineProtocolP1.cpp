#include "../../../include/OfflineOnline/specs/OfflineProtocolP1.hpp"
OfflineProtocolP1::OfflineProtocolP1(shared_ptr<ExecutionParameters> mainExecution, shared_ptr<ExecutionParameters> crExecution, shared_ptr<CryptoPrimitives> primitives, shared_ptr<CommunicationConfig> communication, shared_ptr<OTExtensionMaliciousSender> maliciousOtSender)
{
	this->mainExecution = mainExecution;
	this->crExecution = crExecution;
	this->primitives = primitives;
	this->channel = communication->getCommParty();
	this->maliciousOtSender = maliciousOtSender;
}
