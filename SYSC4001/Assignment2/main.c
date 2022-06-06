#include <stdio.h>
#define MAX_LENGTH 
#define MAX_PROCESS 
#define MAX_ID_LEN 
#define MAX_FILE_NAME 100 




typedef enum
{
    READY,
    RUNNING,
    WAITING,
    TERMINATED,
    INVALID
} process_state_e;

typedef enum 
{
    FCFS,
    EXTERNALPRIORITY,
    ROUNDROBIN
} SCHEDULING_TYPE;


int HIGHESTPRIORITY;
int LOWESTPRIORITY;
int TIMEOUT;
int i;
int INVALID_IDX = -1;
SCHEDULING_TYPE currentType;




struct info
{
    /**
     * ID of the process.
     * Provided to us via input file.
     */
    int     id;
    
    /**
     * When the process is available for processing (effectively when it moves
     * from new state to ready state). Before this, the process should never be
     * moved into the running state.
     * Provided to us via input file.
     */
    int     arrivalTime;
    
    /**
     * Total ammount of time this process must spend in the running state. This
     * does not include time spent in the waiting state (waiting on I/O).
     * Provided to us via input file.
     */
    int     totalCpuTime;
    
    /**
     * Frequency that the process must wait for I/O actions to complete.
     * Provided to us via input file.
     */
    int     IOfreq;
    
    /**
     * How long the I/O takes. The process must sit in the waiting state for the
     * length of this timer.
     * Provided to us via input file.
     */
    int     IOdur;
    
    /**
     * Running counter of how long the process has spent waiting for I/O. Once
     * this hits the IO Duration, then the process must move back into the
     * ready state.
     */
    int     IOtime;
    
    /**
     * Running counter of how long the process has spent in the running state.
     * Once this hits the Total CPU Time, then the process must move into the
     * termintated state.
     */
    int     currentRunTime;
    
    /**
     * Current state the process is in.
     */
    process_state_e state;

    /**
     * Integer priority- for processes
    **/
   int      priority;


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
//Returns the ID of the LOWEST PRIORITY task
int getLowPriority(struct info *processes, int tot, process_state_e state){
    int HIGHESTPRIORITY;
    int priorityID;
    for(int i = 0; i<tot; i++){
        if(processes[i].state == state){
            if (processes[i].priority <= LOWESTPRIORITY){
                    LOWESTPRIORITY = processes[i].priority;
                    priorityID = i;
                }
        }
    }
    return priorityID;
}


//Returns the ID of the highest priority Task
int getHighPriority(struct info *processes, int tot, process_state_e state){
    int HIGHESTPRIORITY;
    int priorityID;

    for (int i = 0; i < tot; i++)
    {
        if(processes[i].state == state){
            if ((processes[i].priority >= HIGHESTPRIORITY)){
                HIGHESTPRIORITY = processes[i].priority;
                priorityID = i;
            }       
        }
    }
    return priorityID;    
}

int getProcessPriority(struct info *proc, int entries, process_state_e state, int tick){
    for (int i = 0; i < entries; i++)
    {           
      if ((proc[i].state == state) && (proc[i].arrivalTime <= tick) && (proc[i].priority >= proc[getHighPriority(proc, entries,state)].priority) && (proc[i].totalCpuTime > proc[i].currentRunTime))
        {
            /* Return the line number of the process that is in the desired state */
            return i;   
        }
    }
    /* Nothing is in the desired state */
    return INVALID_IDX;
}

void setScheduling(int input){
    if(input == 1){
        currentType = FCFS;
    }
    if(input == 2){
       currentType = EXTERNALPRIORITY;
    }
    if(input == 3){
        currentType = ROUNDROBIN;
    }
    else{
        currentType = FCFS;
    }
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


const char* getState(struct info *proc, int entry){
    if(proc[entry].state == READY){
        return "READY";
    }
    if(proc[entry].state == RUNNING){
        return "RUNNING";
    }
    if(proc[entry].state == WAITING){
        return "WAITING";
    }
    if(proc[entry].state == TERMINATED){
        return "TERMINATED";
    }
    if(proc[entry].state == INVALID){
        return "INVALID";
    }
    else{
        return "INVALID";
    }
}

int main(int argc, char *argv[])
{
    process_state_e oldState;

    int     tot = countLines();
    int     opt;
    int     tick = 0;
    int     runningIdx = -1;
    int     readyIdx;
    int     processTerminated=0;
    
    struct info *processes = (struct info*)malloc(tot*sizeof(struct info));
	
    parseFile(tot, processes);

    for(int i = 0; i<tot; i++){
        processes[i].IOtime = 0;
        processes[i].currentRunTime = 0;
        processes[i].state = READY;
    }




    FILE *outFile;
    outFile = fopen("output.txt","w");

    setScheduling(2); //1 fcfc, 2 priority, 3 RR

    if(outFile == NULL){
        fclose(outFile);
    }


	for(int i = 0; i<tot; i++){
		printf("PID %d",processes[i].id);
        printf("arrivalTime %d",processes[i].arrivalTime);
		printf("CPUTIME %d",processes[i].totalCpuTime);
        printf("IOFREQ %d",processes[i].IOfreq);
		printf("IODUR %d",processes[i].IOdur);
        printf("STATE \n%s", getState(processes, i));

	}
    

    
    /**
     * Run in an infinite loop until all of the processes have been put into the
     * terminated state. 
     * Implements a FIRSTCOMEFIRSTSERVE algorithm.
     */
    while(1)
    {

        if(currentType == EXTERNALPRIORITY){
            //int lowPriority = getLowPriority(processes,tot, );
            //int highPriority = getHighPriority(processes,tot,);
            //Increment the priority of the lowest priority process here to prevent starvation
            //processes[lowPriority].priority++;


            processTerminated = 0;
            for(int i =0; i<tot; i++){
                if(processes[i].state == TERMINATED){
                    processTerminated++;
                }


            }

            if (processTerminated == tot)
            {
                printf("\n%s", "All processes have been Terminated");       
                free(processes);
                fclose(outFile); 
                return 0;
            }

            


            for (i = 0; i < tot; i++)
            {
                if (processes[i].state == WAITING)
            {       
                    fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    ++processes[i].IOtime;
                    if (processes[i].IOtime >= processes[i].IOdur)
                    {
                        
                        processes[i].state = READY;
                        fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    }
                }
            }
            
            runningIdx = getProcessPriority(processes, tot, RUNNING, tick);
            if (runningIdx != INVALID_IDX)
            {

                
                /**
                 * We have a process that is currently running, so we will increment
                 * its running time and wait for the next tick.
                 */
                ++processes[runningIdx].currentRunTime;
                if (processes[runningIdx].currentRunTime >= processes[runningIdx].totalCpuTime)
                {
                    /**
                     * This process has finished running, it will be marked as 
                     * terminated 
                     */
                    
                    //oldState = processes[runningIdx].state;
                    processes[runningIdx].state = TERMINATED;
                    fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[runningIdx].id,processes[runningIdx].arrivalTime, processes[runningIdx].totalCpuTime, processes[runningIdx].IOfreq, processes[runningIdx].IOdur, processes[runningIdx].IOtime, processes[runningIdx].currentRunTime, getState(processes, runningIdx), tick);
                    

        
                }
                else
                {
                    /**
                     * Check to see if it is time to interrupt the running process
                     * for I/O actions
                     */
                    if ((processes[runningIdx].currentRunTime % processes[runningIdx].IOfreq == 0) && (processes[runningIdx].IOtime <= processes[runningIdx].IOdur))
                    {
                        
                        fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[runningIdx].id,processes[runningIdx].arrivalTime, processes[runningIdx].totalCpuTime, processes[runningIdx].IOfreq, processes[runningIdx].IOdur, processes[runningIdx].IOtime, processes[runningIdx].currentRunTime, getState(processes, runningIdx), tick);
                        oldState = processes[runningIdx].state;
                        processes[runningIdx].state = WAITING;
                        fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[runningIdx].id,processes[runningIdx].arrivalTime, processes[runningIdx].totalCpuTime, processes[runningIdx].IOfreq, processes[runningIdx].IOdur, processes[runningIdx].IOtime, processes[runningIdx].currentRunTime, getState(processes, runningIdx), tick);
                      
                        
            }
                }


            }       
            else
            {
                int current = getProcessPriority(processes, tot, READY, tick);
                if (current != INVALID_IDX){
                    processes[current].state = RUNNING;
                    fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[current].id,processes[current].arrivalTime, processes[current].totalCpuTime, processes[current].IOfreq, processes[current].IOdur, processes[current].IOtime, processes[current].currentRunTime, getState(processes, current), tick);            
            }   
            current = 0;  
            }         
            

         tick++;         
    }
        if(currentType == FCFS){
            
            for (i = 0; i < tot; i++)
            {   
                if(processes[i].state == TERMINATED){
                    processTerminated++;
                }
            }
            
            if (processTerminated == tot)
            {

                free(processes);
                return 0;
            }
            
            /**
             * Check all the processes that are in the waiting state, and see if 
             * the IO they are waiting on has completed. If so, move it into the
             * ready state, otherwise increment its wait timer.
             */
            for (i = 0; i < tot; i++)
            {
                if (processes[i].state == WAITING)
                {                    
                    ++processes[i].IOtime;
 					fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    
                    if (processes[i].IOtime >= processes[i].IOdur)
                    {
                        fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                        processes[i].IOtime = 0;
                    	processes[i].state = READY;
 						fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    
                    }
                }
            }
            
            /**
             * Check all the processes that are in the running state and increment
             * their run time. If this puts them to their required run time, then
             * move the process into the terminated state. Otherwise, if it is time
             * to run I/O, then move it into the waiting state.
             * If nothing is running, then move something from ready state to 
             * running.
             */
            runningIdx = getProcess(processes, tot, RUNNING, tick);
            if (runningIdx != INVALID_IDX)
            {

                
                /**
                 * We have a process that is currently running, so we will increment
                 * its running time and wait for the next tick.
                 */
                ++processes[runningIdx].currentRunTime;
                if (processes[runningIdx].currentRunTime >= processes[runningIdx].totalCpuTime)
                {
                    /**
                     * This process has finished running, it will be marked as 
                     * terminated 
                     */
                        fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[runningIdx].id,processes[runningIdx].arrivalTime, processes[runningIdx].totalCpuTime, processes[runningIdx].IOfreq, processes[runningIdx].IOdur, processes[runningIdx].IOtime, processes[runningIdx].currentRunTime, getState(processes, runningIdx), tick);
 						//fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    
                    oldState = processes[runningIdx].state;
                    processes[runningIdx].state = TERMINATED;
 					//fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[runningIdx].id,processes[runningIdx].arrivalTime, processes[runningIdx].totalCpuTime, processes[runningIdx].IOfreq, processes[runningIdx].IOdur, processes[runningIdx].IOtime, processes[runningIdx].currentRunTime, getState(processes, runningIdx), tick);
        
            }
                else
                {
                    /**
                     * Check to see if it is time to interrupt the running process
                     * for I/O actions
                     */
                    if (processes[runningIdx].currentRunTime % processes[runningIdx].IOfreq == 0)
                    {
                        fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[runningIdx].id,processes[runningIdx].arrivalTime, processes[runningIdx].totalCpuTime, processes[runningIdx].IOfreq, processes[runningIdx].IOdur, processes[runningIdx].IOtime, processes[runningIdx].currentRunTime, getState(processes, runningIdx), tick);
						//fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    
                        oldState = processes[runningIdx].state;
                        processes[runningIdx].state = WAITING;
                        fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[runningIdx].id,processes[runningIdx].arrivalTime, processes[runningIdx].totalCpuTime, processes[runningIdx].IOfreq, processes[runningIdx].IOdur, processes[runningIdx].IOtime, processes[runningIdx].currentRunTime, getState(processes, runningIdx), tick);
 						//fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    
        
            }
                }


            }       
            else
            {
                processes[getProcess(processes, tot, READY,tick)].state = RUNNING;
                int current = getProcess(processes, tot, READY,tick);

                fprintf(outFile, "\n ID: %d arrTime %d cpuTime %d IOfreq %d IOdur %d IOtime %d runTime %d State %s Tick: %d", processes[current].id,processes[current].arrivalTime, processes[current].totalCpuTime, processes[current].IOfreq, processes[current].IOdur, processes[current].IOtime, processes[current].currentRunTime, getState(processes, current), tick);
                current = 0;
                /**
                 * There are no running processes, move something that is ready to
                 * running
                 */
                
            }

            ++tick;
        }
        if(currentType == ROUNDROBIN){
            //currently has NO implementation of IO
            //AnyCompleteProcess in the waiting state is terminated.
            for(i = 0; i<tot; i++){
                if(processes[i].state == WAITING){
                        fprintf(outFile,"\n");
                    if(processes[i].currentRunTime >= processes[i].totalCpuTime){
                        processes[i].state = TERMINATED;                       
                         fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    		fprintf(outFile,"\n");
                    }
                }
            }
                    
            for(i = 0; i<tot; i++){
                //Any Ready proccess is started then put into waiting if it has been commenced.
                if(processes[i].state == READY){
                    TIMEOUT = 0;
                    
 					fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    fprintf(outFile,"\n");
                    while((TIMEOUT <= 100) && (processes[i].currentRunTime <= processes[i].totalCpuTime)){
                            processes[i].currentRunTime++;
                            TIMEOUT++;
                }
                    processes[i].state = WAITING;
                    
 					fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    fprintf(outFile,"\n");
                }   
                
                if(processes[i].state == WAITING){
                    TIMEOUT = 0;
                      
 					fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    fprintf(outFile,"\n");
                    while((TIMEOUT <= 100) && (processes[i].currentRunTime <= processes[i].totalCpuTime)){
                        processes[i].currentRunTime++;
                        TIMEOUT++;
                    }
                    
					 fprintf(outFile, "PID: %d ArrivalTime %d totalCpuTime %d IOfreq %d IOdur %d IOtime %d currrentRunTime %d State %s Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    	fprintf(outFile,"\n");
                }
        }
        tick++;
        }
		
    }
    fclose(outFile);







}

        


    
