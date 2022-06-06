#include <stdio.h>




int arraySize;
typedef struct process 
{
    int pid;
    int arrivalTime;
    int totalCpuTime;
    int ioFrequency;
    int ioDuration;
    String state;
    int tick;
}
struct process processArray[];

//Adds processes to the array.
void addProcess(int current,int array[]){
    processArray[current].pid = array[0];
    processArray[current].arrivalTime = array[1];
    processArray[current].totalCpuTime = array[2];
    processArray[current].ioFrequency = array[3];
    processArray[current].ioDuration = array[4];
    processArray[current].state = "ready";
}



//'ticks' for an amount of time, more ticks for long processes.
void tick(int duration){
    for(int i =0; i<duration; i++){
        for(int z=0; z>1000; z++){

        }
    }
}



int main(){
    readFile();
    //Checks length of the process array.
    int temp;
    while(processArray[temp].pid != null){
        temp++;
    }
    arraySize = temp;
        
    
    
}














void readFile(){
	char* const filename = "test.txt";
    FILE* file = fopen(filename, "r"); /* should check the result */
    char line[256];
    int current = 0;

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        
        parseString(line, current);
        current ++;
        printf("%s", line);
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

    //return 0;
}


//Takes a string and finds the values encoded in it. 
 void parseString(String line, int current){
    //Break up the entries into individual strings.

    //Traverse the Line, storing underscore then Space.
    blankSpace[];
    int j= 0;
    for(i = 0; i <strlen(line); i++){
        
        if(line[i] == ' '){
            
            blankSpace[j] = (i);//store index of the space

        }
    }
    char pidarray[];
    int pid;
    //Index 0 should be location of the underscore, 1 should be location of space.
    for (int q = 0; q < blankSpace[0]; q++){
        strccat(pidarray, line[q]);
    }
    pid = atoi(pidarray);

    char arrival[];
    int arrivalTime;
    //Index 2 and 3 should contain the start and end points of the the number
    for(int q = blankSpace[1]; q < blankSpace[2]; q++){
        strccat(arrival, line[q]);
    }
    arrivalTime =atoi(arrival);
    

    char cpu[];
    int cpuTime;
    //Index 4 and 5 should contain the start and end points of the value
    for(int q = blankSpace[3]; q < blankSpace[4]; q++){
        strccat(cpu, line[q]);
    }
    cpuTime = atoi(cpu);

    char frequency[];
    int ioFrequency;
    //Index 6 and 7 should contain the start and end points of the value
    for(int q = blankSpace[5]; q < blankSpace[6]; q++){
        strccat(frequency, line[q]);
    }
    ioFrequency = atoi(frequency);

    char duration[];
    int ioDuration;
    //Index 8 and 9 should contain the start and end points of the value
    for(int q = blankSpace[7]; q < blankSpace[8]; q++){
        strccat(duration, line[q]);
    }
    ioDuration = atoi(ioDuration);
    array[] = {pid, arrivalTime, cpuTime, ioFrequency, ioDuration};
    addProcess(current, array);

    


}



