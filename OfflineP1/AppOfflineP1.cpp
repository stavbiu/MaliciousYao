#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <MaliciousYao/include/primitives/CommunicationConfig.hpp>
#include <MaliciousYao/include/primitives/CryptoPrimitives.hpp>
#include <libscapi/include/circuits/GarbledCircuitFactory.hpp>

using namespace std;

//party number
const int PARTY = 1;

//home directory path for all files
const  string HOME_DIR = "C:/Users/stav/Documents/Visual Studio 2015/Projects/MaliciousYao/MaliciousYao";

//files path
const string CIRCUIT_FILENAME = HOME_DIR + string("/assets/circuits/AES/NigelAes.txt");
const string CIRCUIT_INPUT_FILENAME = HOME_DIR + string("/assets/circuits/AES/AESPartyOneInputs.txt");
const string COMM_CONFIG_FILENAME = HOME_DIR + string("/assets/conf/PartiesConfig.txt");
const string CIRCUIT_CHEATING_RECOVERY = HOME_DIR + string("/assets/circuits/CheatingRecovery/UnlockP1Input.txt");
const string BUCKETS_PREFIX_MAIN = HOME_DIR + string("/data/P1/aes");
const string BUCKETS_PREFIX_CR = HOME_DIR + string("/data/P1/cr");

//file for dlog
const string NISTEC_FILE_NAME = "C:/Users/stav/libscapi/include/configFiles/NISTEC.txt";



/*************************************************************************
								MAIN
**************************************************************************/
int main(int argc, char* argv[]) {
	//set io_service for peer to peer communication
	boost::asio::io_service io_service;
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

	//read config file data and set communication config to make sockets.
	CommunicationConfig  * commConfig = new CommunicationConfig(COMM_CONFIG_FILENAME, PARTY, io_service);
	CommParty * commParty = commConfig->getCommParty();
	
	//make connection
	//commParty->join(500, 5000);

	//set crypto primitives
	CryptoPrimitives primitives(NISTEC_FILE_NAME);

	//make circuit
	GarbledBooleanCircuit* mainCircuit = GarbledCircuitFactory::createCircuit(CIRCUIT_INPUT_FILENAME,
		GarbledCircuitFactory::CircuitType::FIXED_KEY_FREE_XOR_HALF_GATES, true);
	//cheating recovery circuit



	//end commenication
	io_service.stop();
	t.join();

	//release memory
	//delete mainCircuit;

	return 0;
}