#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <MaliciousYao/include/primitives/CommunicationConfig.hpp>
#include <MaliciousYao/include/primitives/CryptoPrimitives.hpp>
#include <MaliciousYao/include/primitives/CheatingRecoveryCircuitCreator.hpp>
#include <libscapi/include/circuits/GarbledCircuitFactory.hpp>
#include <libscapi/include/circuits/GarbledBooleanCircuit.h>

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
	
	cout << "\nP1 start communication\n";

	//make connection
	commParty->join(500, 5000);

	//set crypto primitives
	CryptoPrimitives primitives(NISTEC_FILE_NAME);

	//make circuit
	GarbledBooleanCircuit* mainCircuit = GarbledCircuitFactory::createCircuit(CIRCUIT_INPUT_FILENAME,
		GarbledCircuitFactory::CircuitType::FIXED_KEY_FREE_XOR_HALF_GATES, true);
	//cheating recovery circuit
	int numOfInputs = mainCircuit->getNumberOfInputs(1) + mainCircuit->getNumberOfInputs(2);
	GarbledBooleanCircuit* crCircuit = (CheatingRecoveryCircuitCreator(CIRCUIT_CHEATING_RECOVERY, numOfInputs)).create();

	//TODO - OTExtensionMaliciousSender otSender = initMaliciousOtSender(mainCircuit.getNumberOfInputs(2), commConfig);


	//			int N1 = 10;
	//			int B1 = 10;
	//			int s1 = 40;
	//			double p1 = 0.64;
	//			
	//			int N2 = 10; //32;
	//			int B2 = 10; //31;
	//			int s2 = 40;
	//			double p2 = 0.64; //0.6;


	//			int N1 = 8;
	//			int B1 = 10;
	//			int s1 = 40;
	//			double p1 = 0.59;
	//			
	//			int N2 = 8;
	//			int B2 = 74;
	//			int s2 = 40;
	//			double p2 = 0.85;

	int N1 = 32;
	int B1 = 7;
	int s1 = 40;
	double p1 = 0.62;

	int N2 = 32;
	int B2 = 20;
	int s2 = 40;
	double p2 = 0.71;

	//			int N1 = 128;
	//			int B1 = 12;
	//			int s1 = 80;
	//			double p1 = 0.77;
	//			
	//			int N2 = 128;
	//			int B2 = 28;
	//			int s2 = 80;
	//			double p2 = 0.75; 

	//			int N1 = 1024;
	//			int B1 = 4;
	//			int s1 = 40;
	//			double p1 = 0.72;
	//			
	//			int N2 = 1024;
	//			int B2 = 10;
	//			int s2 = 40;
	//			double p2 = 0.85;

	//no thread implemention
	GarbledBooleanCircuit* mainGbc = GarbledCircuitFactory::createCircuit(CIRCUIT_FILENAME,
		GarbledCircuitFactory::CircuitType::FIXED_KEY_FREE_XOR_HALF_GATES, true);
	GarbledBooleanCircuit* crGbc = GarbledCircuitFactory::createCircuit(CIRCUIT_CHEATING_RECOVERY,
		GarbledCircuitFactory::CircuitType::FIXED_KEY_FREE_XOR_HALF_GATES, true);




	//end commenication
	io_service.stop();
	t.join();

	cout << "\nP1 end communication\n";
	//enter for out
	cin.ignore();
	//release memory
	delete mainCircuit, crCircuit;

	return 0;
}