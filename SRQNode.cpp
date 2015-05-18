#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <cmath>
#include <unistd.h>		//for usleep 
using namespace std;

// bool RequestToSend = false;
// bool ArrivalNotificationSenderSide = false;
// bool TimeOut = false;
// bool ArrivalNotificationReceiverSide = false;

// int Sw = pow(2, m-1);
// int Sf = 0;
// int Sn = 0;


// int Rn = 0;
// bool NakSent = false;
// AckNeeded = false;

//ssh test

int scount = 0;
int rcount = 0;

int m = 4;
int Sw = pow(2, m-1);
int Sf = 0;
int Sn = 0;

string messages[3] = {"I", "am", "Rohit"};
string message;
int messageNo = 0;
int i = 0;

void * upperLayer(void * arg){
	if(i == 0){
		usleep(3000);
		if(messageNo < 2){
			message = message[messageNo++];
			requestToSend = true;
		}else{
			requestToSend = false;
		}
	}
}



class Frame{
public:
	char seqNo;
	char value;
	char crcRemainder;
};

char GetData(){
	char data;
	if(i < message.length()){
		data = message[i++];
	}else if(i == message.length()){
		requestToSend = false;
		data = message[i];
		i = 0;
	}
	return data;
}

Frame MakeFrame(char data, int Sn ){
	Frame newFrame = new Frame();
}

void * requestToSendHandler(void * arg){
	vector<Frame> frameBuffer;
	while(true){
		 if(RequestToSend == true){
			if(Sn -Sf >= Sw){
				usleep(2000);
			}
			if(Sn - Sf < Sw){
				char data = GetData();
				MakeFrame(data, Sn);
				StoreFrame(Sn);
				SendFrame(Sn);
				Sn = Sn + 1;
				StartTimer(Sn);
			}
		}
	}
}


void * sending(void* arg){
	//spawn three event threads
	pthread_t requestToSendThread;
	pthread_create(&requestToSendThread, NULL, requestToSendHandler,NULL);
	pthread_join(requestToSendThread, NULL);

	// while(true){
	// 	scount++;
	// 	printf("sending.....%d\n",scount);
		// if(RequestToSend == true){
		// 	if(Sn -Sf >= Sw){
		// 		Sleep();
		// 	}
		// 	if(Sn - Sf < Sw){
		// 		GetData();
		// 		MakeFrame(Sn);
		// 		StoreFrame(Sn);
		// 		SendFrame(Sn);
		// 		Sn = Sn + 1;
		// 		StartTimer(Sn);
		// 	}
		// }
		// if(ArrivalNotificationSenderSide == true){
		// 	Receive(frame);
		// 	if(corrupted(frame))
		// 		Sleep();
		// 	else{
		// 		if(FrameType == NAK){
		// 			if(nakNo >= Sf && nakNo <= Sn){
		// 				resend(nakNo);
		// 				StartTimer(nakNo);
		// 			}
		// 		}
		// 		if(FrameType == ACK){
		// 			if(ackNo >= Sf && ackNo <= Sn){
		// 				while(Sf < ackNo){
		// 					Purge(Sf);
		// 					StopTimer(Sf);
		// 					Sf = Sf + 1;
		// 				}
		// 			}
		// 		}	
		// 	}
		// }
		// if(TimeOut == true){
		// 	StartTimer(t);
		// 	SendFrame(t)
		// }
	// }
}

void * receiving(void *arg){
	//spawn the single thread
	// while(true){
	// 	rcount++;
	// 	printf("receiving.....%d\n",rcount);
		// if(ArrivalNotificationReceiverSide == true){
		// 	Receive(Frame);
		// 	if(corrupted(Frame) && (! NakSent)){
		// 		SendNAK(Rn);
		// 		NakSent = true;
		// 		Sleep();
		// 	}
		// 	if((seqNo < Rn || seqNo > Rn) && (! NakSent){
		// 		SendNAK(Rn);
		// 		NakSent = true;
		// 		if((seqNo in  window) && (!Marked(seqNo))){
		// 			StoreFrame(seqNo);
		// 			Marked(seqNo) = true;
		// 			while(Marked(Rn)){
		// 				DeliverData(Rn);
		// 				Purge(Rn);
		// 				Rn = Rn + 1;
		// 				AckNeeded = true;
		// 			}
		// 			if(AckNeeded == ture){
		// 				sendAck(Rn);
		// 				AckNeeded = false;
		// 				NakSent = false;
		// 			}
		// 		}
		// 	}
		// }
	// }
}



int main(){
	//Spawn two threads which do the 
	//sending and receiving
	pthread_t sendingThread, receivingThread;

	pthread_create(&sendingThread, NULL, sending, NULL);
	pthread_create(&receivingThread, NULL, receiving, NULL);

	pthread_join(sendingThread, NULL);
	pthread_join(receivingThread, NULL);
	
	pthread_exit(NULL);
	return 0;
}