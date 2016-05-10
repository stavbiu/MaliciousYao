#include "../../include/primitives/CommunicationConfig.hpp"
/*
	Read configuration properties and set party and OT sockets.
	Set communication between the two partys.
	inputs:
			config_file - configuration file name.
			thisPartyNum - number of current party (1 or 2).
*/
CommunicationConfig::CommunicationConfig(string config_file, int thisPartyNum, boost::asio::io_service& io_service)
{
	//set party number
	this->partyNum = thisPartyNum;

	//open file
	ConfigFile cf(config_file);
	//get partys IPs and ports data
	int party_1_port = stoi(cf.Value("", "party_1_port"));
	int party_2_port = stoi(cf.Value("", "party_2_port"));
	string party_1_ip = cf.Value("", "party_1_ip");
	string party_2_ip = cf.Value("", "party_2_ip");

	//set partys IPs and ports to SockectPartyData
	if (this->partyNum == 1) {
		this->me = new SocketPartyData(IpAdress::from_string(party_1_ip), party_1_port);
		this->otherParty = new SocketPartyData(IpAdress::from_string(party_2_ip), party_2_port);
	}
	else {
		this->me = new SocketPartyData(IpAdress::from_string(party_2_ip), party_2_port);
		this->otherParty = new SocketPartyData(IpAdress::from_string(party_1_ip), party_1_port);
	}

	//set communication between the two partys
	this->commParty = new CommPartyTCPSynced(io_service, *(this->me), *(this->otherParty));

	//get OT IP and port
	int malicious_OT_port = stoi(cf.Value("", "malicious_OT_port"));
	string malicious_OT_address = cf.Value("", "malicious_OT_address");
	//set to SockectPartyData
	this->maliciousOTServer = new SocketPartyData(IpAdress::from_string(malicious_OT_address), malicious_OT_port);
}

CommunicationConfig::~CommunicationConfig()
{
	delete this->me;
	delete this->otherParty;
	delete this->maliciousOTServer;
	delete this->commParty;
}
