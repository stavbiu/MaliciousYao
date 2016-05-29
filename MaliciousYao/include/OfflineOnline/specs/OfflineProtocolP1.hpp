#pragma once

#include "../../../include/common/CommonMaliciousYao.hpp"
#include "../../../include/primitives/CommunicationConfig.hpp"
#include "../../../include/primitives/ExecutionParameters.hpp"
#include "../../../include/primitives/CryptoPrimitives.hpp"
#include "../../../include/primitives/KProbeResistantMatrix.hpp"

using namespace std;

/**
 This class represents the first party in the offline phase of Malicious Yao protocol. <P>

 The full protocol specification is described in "Blazing Fast 2PC in the "Offline/Online Setting with Security for
 Malicious Adversaries" paper by Yehuda Lindell and Ben Riva, page 18 - section E, "The Full Protocol Specification".
*/
class OfflineProtocolP1
{
private:
	ExecutionParameters mainExecution;		// Parameters of the main circuit.
	ExecutionParameters crExecution;		// Parameters of the cheating recovery circuit.
	CryptoPrimitives primitives;			// Contains the low level instances to use.
	CommParty * channel;						// The channel used communicate between the parties.

	KProbeResistantMatrix mainMatrix;			//The probe-resistant matrix that used to extend the main circuit's keys.
	KProbeResistantMatrix crMatrix;				//The probe-resistant matrix that used to extend the ceating recovery circuit's keys.

public:


 };