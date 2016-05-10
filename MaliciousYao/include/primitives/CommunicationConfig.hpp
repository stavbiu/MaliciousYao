#pragma once

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <libscapi/include/infra/ConfigFile.hpp>
#include <libscapi/include/comm/Comm.hpp>

using namespace std;

/*
* This class sets the communication between the parties participate in the protocol. <P>
*
* The type of communication used is native, since it provides better performance than the java implementation.
*/
class CommunicationConfig {
private:
		int partyNum;					//The current party number (1 or 2);
		SocketPartyData* me;				//The current running party.
		SocketPartyData* otherParty;		//The other party to communicate with.
		SocketPartyData* maliciousOTServer;	//The server data in the malicious OT protocol.
		CommParty * commParty;			//the connection between two parties

public:
	/*
	cons - read configuration properties and set party and OT sockets.
			Set communication between the two partys
	*/
	CommunicationConfig(string config_file, int thisPartyNum, boost::asio::io_service& io_service);

	/*
	dcons - free memory
	*/
	~CommunicationConfig();


	//get sockets
	SocketPartyData* getMe() { return this->me; }
	SocketPartyData* getOtherParty() { return this->otherParty; }
	SocketPartyData* getMaliciousOTServer() { return this->maliciousOTServer; }
	CommParty* getCommParty() { return this->commParty; }
};
