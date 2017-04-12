/*
 * ComSender.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: ee
 */

#include "ComSender.h"

ComSender::ComSender() {
	// TODO Auto-generated constructor stub

}

ComSender::~ComSender() {
	// TODO Auto-generated destructor stub
}

ComSender::SendThis(std::string str){

	//HANDSHAKE IS SUCCESSFULL

		std::cout << "Sending..." << std::endl;

		// read from the input file

		std::vector<int32_t> fileContents = client::getFileContents("3");
	//	 for(int i = 0; i <= fileContents.size(); i++) {
	//		 std::cout << fileContents[i] << std::endl;
	//	 }
		// keep track of where we are in the data
		uint32_t filePointer = 0;

	   int packetAmount = ceil((float)fileContents.size() / DATASIZE);

	   int numberOfPacketsMax = ceil((float)CASHSIZE / DATASIZE);

	   int boxSize = numberOfPacketsMax;
	   if(boxSize > packetAmount){
		   boxSize = packetAmount;
	   }
	   int rows = packetAmount;

	   std::vector<std::vector<int32_t>> dynamicArray(packetAmount);


	   int waitTo = boxSize;
	   std::cout << "boxSize: " << waitTo << std::endl;
	   std::cout << "numberOfPacketsMax: " << numberOfPacketsMax << std::endl;
	   std::cout << "packetAmount: " << packetAmount << std::endl;

	   for(int i = 0; i < packetAmount; i++) {




				uint32_t datalen = std::min(DATASIZE, (uint32_t)fileContents.size() - (DATASIZE*i));

				//dynamicArray[i] = (datalen + HEADERSIZE);

				//int datalen = sizeof dynamicArray[i];

				std::cout << datalen << std::endl;
	//					std::vector<int32_t> pkt = std::vector<int32_t>(HEADERSIZE + datalen);

				dynamicArray[i].push_back(toBinary(packetAmount)[1]);
				dynamicArray[i].push_back(toBinary(packetAmount)[0]);
				//Current packet 2


				dynamicArray[i].push_back(toBinary(i+1)[1]);
				dynamicArray[i].push_back(toBinary(i+1)[0]);

				//Last sent 2
				dynamicArray[i].push_back(toBinary(boxSize)[1]);
				dynamicArray[i].push_back(toBinary(boxSize)[0]);

				std::string hashStr;
				hashStr = "";
				uint32_t filePointerL = filePointer;

				for (uint32_t j = 0; j < datalen; j++) {
					int val1;

					 val1 = fileContents[filePointer] & 0xFF;

					hashStr = hashStr + std::to_string(val1);

					filePointer++;
				}

				unsigned long long int hashInt = hash(&hashStr);

				std::cout  << hashInt << " here" << "\n";
				std::vector<int32_t> array = to10Bytes(hashInt);

				//bit8IntTo32BitInt(array);
				for (int j = 9; j >= 0 ; j--) {
					dynamicArray[i].push_back(array[j]);
				}
	////
				filePointer = filePointerL;

				for (uint32_t j = HEADERSIZE; j < HEADERSIZE + datalen; j++) {
					dynamicArray[i].push_back(fileContents[filePointer]);
					filePointer++;
				}
	std::cout << i << std::endl;
			//	uint32_t test=dynamicArray[0][3];


				if(i == packetAmount -1 ){
					std::vector<int32_t> packet;
					std::vector<int32_t> oldpacket;

						for(int u = 0; u < boxSize; u++){

								//std::cout << "------------" << u <<"\n"; //actially - 1
	//								std::cout << dynamicArray[u][0] << "\n";
	//								std::cout << dynamicArray[u][1] << "\n";
	//								std::cout << "--Total--" << "\n";
	//								std::cout << dynamicArray[u][2] << "\n";
	//								std::cout << dynamicArray[u][3] << "\n";
	//								std::cout << "--Current--" << "\n";
	//								std::cout << dynamicArray[u][4] << "\n";
	//								std::cout << dynamicArray[u][5] << "\n";
	//								std::cout << "--box--" << "\n";
								networkLayer->sendPacket(dynamicArray[u]);


						}
						int counter = 0;
						do{

							bool stop = false;

							while (!stop) {

								if (networkLayer->receivePacket(&packet)) {

										std::cout << "Troubleshooting: received packet, length=" << packet.size() << "  first byte=" << packet[0] <<  std::endl; // tell the user

										stop=true; // and let's just hope the file is now complete

									} else {
										// sleep for ~10ms (or however long the OS makes us wait)
										::usleep(10);
									}
								}
							int sizeOfLostPackets = packet.size();
							int ulocal = 0;
							int size = sizeOfLostPackets;
							if(sizeOfLostPackets > boxSize){
								size = boxSize;
							}
							counter++;
							if(packet != oldpacket || counter > 6){
								counter = 0;
								for(int u = 0; u < size; u++){
	//								if(packet[u] == 255 && packet[u+1] == 0)	{
	//									break;
	//								}
									if(packet[u] > packet[u+1] )
									{
										break;
									}
									std::cout << "------------" << u <<"\n";
										std::cout << "------------" << packet[u] <<"\n"; //actially - 1

	//										std::cout << dynamicArray[packet[u]-1][0] << "\n";
	//										std::cout << dynamicArray[packet[u]-1][1] << "\n";
	//										std::cout << "--Total--" << "\n";
	//										std::cout << dynamicArray[packet[u]-1][2] << "\n";
	//										std::cout << dynamicArray[packet[u]-1][3] << "\n";
	//										std::cout << "--Current--" << "\n";
	//										std::cout << dynamicArray[packet[u]-1][4] << "\n";
	//										std::cout << dynamicArray[packet[u]-1][5] << "\n";
	//										std::cout << "--box--" << "\n";
										networkLayer->sendPacket(dynamicArray[packet[u]-1]);
										ulocal++;

								}
							}
							oldpacket = packet;
							::usleep(1000);
					}while(packet[0] != 1 && packet[1] != 1 && packet[2] != 1 && packet[3] != 1);
	std::cout << "Done" << std::endl;

				}


			}



		}
}
