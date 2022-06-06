#include <stdio.h>


struct partition
{
    int capacity;
    struct info *storedProcesses;
};

typedef enum
{
    READY,
    RUNNING,
    WAITING,
    TERMINATED,
    INVALID
} process_state_e;


struct info
{
    int id;
    int arrivalTime;  
    int totalCpuTime;
    int IOfreq;
    int IOdur;
    int IOtime;
    int currentRunTime;
    int processSize;
    process_state_e state;
    int memoryAddress;
    
};


int getProcess(struct info *proc, int entries, process_state_e state, int tick)
{
    for (int i = 0; i < entries; i++)
    {  
        if ((proc[i].state == state) && (proc[i].arrivalTime <= tick))
        {
            /* Return the line number of the process that is in the desired state */
            return i;   
        }
    }
    return INVALID_IDX;
}

int countLines(){
    FILE *fp; 
    int lines = 0;  // Line counter (result)  
    char c;  // To store a character read from file 
  
    // Get file name from user. The file should be 
    // either in current folder or complete path should be provided 

  
    // Open the file 
    fp = fopen("input.txt", "r"); 
  
    // Check if file exists 
    if (fp == NULL) 
    { 
        return 0; 
    } 
  
    // Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            lines = lines + 1; 
  
    // Close the file 
    fclose(fp);
    return lines;
}

void parseFile(int lines, struct info *proc){
    FILE *input;
    
    input = fopen("input.txt", "r");
	
    for (int i = 0; i < lines; i++) {
        fscanf(input, "%d %d %d %d %d %d", &proc[i].id,
                &proc[i].arrivalTime, &proc[i].totalCpuTime,
                &proc[i].IOfreq, &proc[i].IOdur, &proc[i].priority);

	
    fclose(input);
}
}





//Checks for a specific entry in all memory for a process.
bool checkMemory(struct partition *memory, int size, int pid){
    for(int part=0; part<4; part++){
        for(int i= 0; i<tot; i++){
            if((memory[part].storedProcesses[i].id == pid) && (memory[part].storedProcesses[i].size == size)){
                return true;
            } 
        }
    }
    return false;
}

//Checks if the new 'size' of file can fit in the partition
bool availableSpace(struct info *proc, int size,int tot){
    int count=0;
    for(int i; i<tot; i++){
        if(proc[i].state == INVALID){//THIS IS TO DEMONSTRATE THAT I WILL BE ENSURING THAT PROCESSES IN MEMORY ARE INITIALIZED
            count = proc[i].size + count;
        }   
        }
    if(count<size){
        
    }

    }




//Checks all the partition for space according to much space is remaining
int checkMemoryForSpace

void addToMemory((struct partition *memory, struct info *proc, int size, int pid,int tot){





}

void removeFromMemory((struct partition memory*){

}




int main(int argc, char *argv[]){

    struct partition  partition1;
    partition1.capacity = 500;
    partition1.storedProcesses = (struct info*)malloc(tot*sizeof(struct info));

    struct partition  partition2;
    partition2.capacity = 250;
    partition2.storedProcesses =(struct info*)malloc(tot*sizeof(struct info));

    struct partition  partition3;
    partition3.capacity = 150;
    partition3.storedProcesses =(struct info*)malloc(tot*sizeof(struct info));

    struct partition  partition4;
    partition4.capacity = 100;
    partition4.storedProcesses = (struct info*)malloc(tot*sizeof(struct info));

    struct partition *memory = (struct partition*)malloc(4*sizeof(partition1)); //Ensures theres plenty of space!
    memory[0] = partition1;
    memory[1] = partition2;
    memory[2] = partition3;
    memory[3] = partition4;


    struct info *processes = (struct info*)malloc(tot*sizeof(struct info));







}


