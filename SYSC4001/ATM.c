#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 100


enum destination{
    ATM,
    EDITOR,
    SERVER;
}

struct message{
    destination dest;
    bool hasInfo;
    char[] messageType;
    int dataInt
    float dataFloat
    char[] dataChar;
}

struct message *buffer1;
struct message *buffer2;
struct message *buffer3;









//ATM SERVER SECTION OF THE CODE









//ATM SECTION OF THE CODE----------Start void ATM() to run this section
void start(){
    char[] accountNumber = inputAccountNumber();
    sendMessage(inputPIN(),accountNumber);
    wait();
    char[] reply = receiveMessage();
        int failedAttempts = 0;
        while(failedAttempts < 3 ){
            if(reply == PIN_OK){
                atmFunctions();
                return;
            }
            if(reply == PIN_WRONG){
                failedAttempts++;
                sendMessage(inputPin(), accountNumber);
            }
    
        }
}


void atmFunctions(){
    while(1){
        char[] input;
        printf("%s, Ples input ur command")
        input = requestInput();
        if(stringCompare(input,balance)){
            getBalance();
            printf(balance);
        }
        if(stringCompare(input, withdraw)){
            withDraw();
        }
        if(stringCompare(input,exit)){
            return;
        }
    }
}

void withdraw(){
    printf("%s,Requesting an Amount to withdraw: ");
    char[] input2;
    input2 = requestInput(); //amount of money
    sendMessage(_WITHDRAW, input2);
    receiveMessage();

}



char[] requestInput(){
    char[] input;
    char tmp;
    while(true){
        tmp = getChar();
        if(tmp == null){
            return input;
        }
        input = append(input,temp);   
    }   
}




void sendMessage(){

}



char[] receiveMessage(){
    char[] returnString;
    if(buffer1.hasInfo){
        if(buffer.destination == "ATM"){
            parse(buffer1);
        }
    }
    if(buffer2.hasInfo){
        if(buffer2.destination == "ATM"){
            parse(buffer1);
        }
    }
    if(buffer3.hasInfo){
        if(buffer3.destination == "ATM"){
            parse(buffer3);
        }
    }
    return returnString;
}

int inputPIN(){
    //decode whatever was inputted.
    return requestInput();
}

int inputAccountNumber(){
    printf("%s, plese inout dat numbah");
    return requestInput();
}


void *atm(void *var){
    while(1){
        start();
    }
}

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

//END OF ATM


int main(void){
    //Start and Create Thread.
    pthread_t thread_id;
    pthread_create(&thread_id, null, atm, NULL);
    pthread_join(thread_id, NULL);
    //


}

char[] parse(struct *message){
    char[] returnString;
    //Meant for DBSERVER
    if(message.messageType == "BalanceRequest"){


    }
    //Meant for ATM
    if(message.messageType == "BalanceReturn"){
        char buf[MAX];
        gcvt(message.dataFloat, 10, buf)
        return buf;
    }

    //MEANT FOR ATM
    if(message.messageType == "PIN_RETURN" ){
        if(message.dataChar == "PIN_OK"){
            return returnString = message.dataChar;
        }
        if(message.dataChar == "PIN_WRONG"){
            return returnString = message.dataChar;
        }
    }

    //MEANT FOR DBSERVER
    if(message.MessageType == "WithdrawRequest"){

    }
    //MEANT FOR ATM
    if(message.MessageType == "WithdrawReturn"){
        if(message.dataChar == "FUNDS_OK"){
            return returnString = message.dataChar;
        }
        if(message.dataChar == "NSF"){
            return returnString = message.dataChar;
        }

    }
    //MEANT FOR DBEDITOR
    if(message.MessageType == "DBEdit"){
        
    }
}
