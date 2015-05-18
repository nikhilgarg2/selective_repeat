#include <iostream>
#include <stdio.h>
#include <pthread.h>
using namespace std;

// bool RequestToSend = false;
bool ArrivalNotificationSenderSide = false;
// bool TimeOut = false;
bool ArrivalNotificationReceiverSide = false;

// int Sw = pow(2, m-1);
// int Sf = 0;
// int Sn = 0;


int Rn = 0;
bool NakSent = false;
bool AckNeeded = false;

//ssh test

int scount = 0;
int rcount = 0;

// void * sending(void* arg){
// 	//spawn three event threads
// 	while(true){
// 		// scount++;
// 		// printf("sending.....%d\n",scount);
// 		// if(RequestToSend == true){
// 		// 	if(Sn -Sf >= Sw){
// 		// 		Sleep();
// 		// 	}
// 		// 	if(Sn - Sf < Sw){
// 		// 		GetData();
// 		// 		MakeFrame(Sn);
// 		// 		StoreFrame(Sn);
// 		// 		SendFrame(Sn);
// 		// 		Sn = Sn + 1;
// 		// 		StartTimer(Sn);
// 		// 	}
// 		// }
// 		// if(ArrivalNotificationSenderSide == true){
// 		// 	Receive(frame);
// 		// 	if(corrupted(frame))
// 		// 		Sleep();
// 		// 	else{
// 		// 		if(FrameType == NAK){
// 		// 			if(nakNo >= Sf && nakNo <= Sn){
// 		// 				resend(nakNo);
// 		// 				StartTimer(nakNo);
// 		// 			}
// 		// 		}
// 		// 		if(FrameType == ACK){
// 		// 			if(ackNo >= Sf && ackNo <= Sn){
// 		// 				while(Sf < ackNo){
// 		// 					Purge(Sf);
// 		// 					StopTimer(Sf);
// 		// 					Sf = Sf + 1;
// 		// 				}
// 		// 			}
// 		// 		}	
// 		// 	}
// 		// }
// 		// if(TimeOut == true){
// 		// 	StartTimer(t);
// 		// 	SendFrame(t)
// 		// }
// 	}
// }

int Frame,seqNo,Remainder,DataReceived,DataCheck;
bool check=false;
int ReceiveIndex=0;
char data[1000];
bool Marked[8];
int TempArray[8];

bool corrupted(int a,int b)
{
	if(a%b == 0)
		return true;
	else
		return false;
}

void Receive(int n)
{
	
	printf("%d\n",Frame );
	Remainder = Frame & 15;
	Frame=Frame >> 4;
	DataReceived= Frame & 255;
	Frame=Frame >> 8;
	seqNo = Frame;
	DataCheck=0;
	DataCheck = DataCheck | DataReceived;
	DataCheck = DataCheck << 4;
	DataCheck = DataCheck | Remainder;
	printf("DataReceived %c\n",DataReceived);
	printf("seqNo %d\n", seqNo);
	printf("Remainder %d\n", Remainder);

}

void * waitforevent(void * argv){
	if(check!=true){
		Frame = 5787;
		ArrivalNotificationReceiverSide=true;
	}
}

void SendNAK(int n)
{

	int DataSend=0;//socket for sending NakSent		// 01 is sent in case it is negative ack.
	DataSend = DataSend | n;
	DataSend = DataSend << 2;
	DataSend = DataSend | 1;

}

void sendAck(int n)
{

	int DataSend=0;//socket for sending Acknowledgement  // 11 is sent at the last in case of positive acknowledgement.   
	DataSend = DataSend | n;
	DataSend = DataSend << 2;
	DataSend = DataSend | 3;


}

void DeliverData(int n)
{

	if(TempArray[n]!= 0 )
			data[ReceiveIndex++]=char(TempArray[n]);
	else
		data[ReceiveIndex++]=char(DataReceived);
	
	printf("DataReceivedHere %c\n", data[0]);
}

void Purge(int n){

	TempArray[n]=-1;
	Marked[n]=false;

}

void * receiving(void *arg){
	for(int i=0;i<8;i++)
		Marked[i]=false;
	pthread_t receivertestthread;
	pthread_create(&receivertestthread,NULL,waitforevent,NULL);

	while(true){
		if(ArrivalNotificationReceiverSide == true){
			check=true;
			Receive(Frame);
			if(corrupted(DataReceived,11) && (! NakSent)){
				SendNAK(Rn);
				NakSent = true;
				//sleep();
			}
			if(seqNo != Rn){

				if(!NakSent){ 
					SendNAK(Rn);
					NakSent = true;
				}
				if(( 0<=seqNo && seqNo<=7 ) && (!Marked[seqNo])){
					TempArray[seqNo]=DataReceived;
					Marked[seqNo] = true;
				}
			}
			else{
				Marked[Rn]=true;
				while(Marked[Rn]){
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
			check=false;
			ArrivalNotificationReceiverSide=false;
		}
		
	}
	pthread_join(receivertestthread,NULL);

}



int main(){
	//Spawn two threads which do the 
	//sending and receiving
	pthread_t sendingThread, receivingThread;

	//pthread_create(&sendingThread, NULL, sending, NULL);
	pthread_create(&receivingThread, NULL, receiving, NULL);

	//pthread_join(sendingThread, NULL);
	pthread_join(receivingThread, NULL);
	
	pthread_exit(NULL);
	return 0;
}