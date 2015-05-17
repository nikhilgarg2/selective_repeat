#include <iostream>
#include <stdio.h>
#include <pthread.h>
using namespace std;

// bool RequestToSend = false;
bool ArrivalNotificationSenderSide = false;
// bool TimeOut = false;
// bool ArrivalNotificationReceiverSide = false;

// int Sw = pow(2, m-1);
// int Sf = 0;
// int Sn = 0;


int Rn = 0;
bool NakSent = false;
bool AckNeeded = false;

//ssh test

int scount = 0;
int rcount = 0;

void * sending(void* arg){
	//spawn three event threads
	while(true){
		scount++;
		printf("sending.....%d\n",scount);
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
	}
}

bool corrupted(char frame)
{
	return true;
}
void * waitforevent(void * argv){
if(data successfully received)
	ArrivalNotificationReceiverSide=true;
}

void * receiving(void *arg){
	pthread_t receivertestthread;
	pthread_create(&receivertestthread,NULL,waitforevent,NULL);

	while(true){
		rcount++;

		printf("receiving.....%d\n",rcount);
		if(ArrivalNotificationReceiverSide == true){
			ArrivalNotificationReceiverSide=false;
			Receive(Frame);
			if(corrupted(Frame) && (! NakSent)){
				SendNAK(Rn);
				NakSent = true;
				//sleep();
			}
			if((seqNo != Rn){

				if(! NakSent){ 
					SendNAK(Rn);
					NakSent = true;
				}
				if((seqNo in  window) && (!Marked(seqNo))){
					StoreFrame(seqNo);
					Marked(seqNo) = true;	}
			}
			else{
				Marked(Rn)=true;
				while(Marked(Rn)){
					DeliverData(Rn);
					Purge(Rn);
					Rn = Rn + 1;
					AckNeeded = true;
				}
				if(AckNeeded == true){
					sendAck(Rn);
					AckNeeded = false;
					NakSent = false;
				}
			}
		}
	}
	pthread_join(receivertestthread,NULL);
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