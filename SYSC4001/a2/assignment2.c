#include <stdio.h>
#define MAX_LENGTH 
#define MAX_PROCESS 
#define MAX_ID_LEN 
#define MAX_FILE_NAME 100 
#define FILENAME "output.txt"



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

SCHEDULING_TYPE currentType = EXTERNALPRIORITY;
int HIGHESTPRIORITY;
int LOWESTPRIORITY;
int TIMEOUT;
int i;
int INVALID_IDX = -1;

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
}

int getProcessPriority(struct info *proc, int entries, process_state_e state, int tick){
    int HIGHESTPRIORITY;
    //Implements a for loop that looks for highest integer priority that is in the desired state
    for (int i = 0; i < entries; i++)
    {
        if(proc[i].state == state){
            if ((proc[i].priority >= HIGHESTPRIORITY)){
                HIGHESTPRIORITY = proc[i].priority;
            }
    }
    }
    for (int i = 0; i < entries; i++)
    {           
      if ((proc[i].state == state) && (proc[i].arrivalTime <= tick) && (proc[i].priority >= HIGHESTPRIORITY))
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
        SCHEDULING_TYPE currentType = FCFS;
    }
    if(input == 2){
        SCHEDULING_TYPE currentType = EXTERNALPRIORITY;
    }
    if(input ==3){
        SCHEDULING_TYPE currentType = ROUNDROBIN;
    }
}

int countLines(){
    FILE *fp; 
    int lines = 0;  // Line counter (result) 
    char filename[MAX_FILE_NAME]; 
    char c;  // To store a character read from file 
  
    // Get file name from user. The file should be 
    // either in current folder or complete path should be provided 
    printf("Enter file name: "); 
    scanf("%s", filename); 
  
    // Open the file 
    fp = fopen(filename, "r"); 
  
    // Check if file exists 
    if (fp == NULL) 
    { 
        printf("Could not open file %s", filename); 
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

void parseFile(int lines){
    FILE *input;
    if (fp == NULL) {
        printf("File not found\n");
    }
    fp = fopen("input.txt", "r");

    for (int i = 0; i < lines; i++) {
        fscanf(input, "%d %d %d %d %d", &processes[i].id,
                &processes[i].arrivalTime, &processes[i].totalCPU,
                &processes[i].IOfreq, &processes[i].IOdur);
    }
    fclose(input);
}

int getLowPriority(struct info *proc){
    int HIGHESTPRIORITY;
    int priorityID;
    for(int i = 0; i<tot; i++){
        if((processes[i].state != TERMINATED) || (processes[i].state != WAITING)){
            if (proc[i].priority <= LOWESTPRIORITY){
                    LOWESTPRIORITY = proc[i].priority;
                    priorityID = i;
                }
        }
    }
    return priorityID;
}

int getHighPriority(struct info *proc){
    int HIGHESTPRIORITY;
    int priorityID;

    for (int i = 0; i < tot; i++)
    {
        if((processes[i].state != TERMINATED) || (processes[i].state != WAITING)){
            if ((proc[i].priority >= HIGHESTPRIORITY)){
                HIGHESTPRIORITY = proc[i].priority;
                priorityID = i;
            }       
        }
    }
    return priorityID;    
}


char[] getState(struct info *proc, int entry){
    if(proc[entry].state == READY){
        return "READY";
    }
    if(proc[entry].state == RUNNING){
        return "RUNNING";
    }
    if(proc[entry].state = WAITING){
        return "WAITING";
    }
    if(proc[entry].state = TERMINATED){
        return "TERMINATED";
    }
    if(proc[entry].state = INVALID){
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
    int     runningIdx;
    int     readyIdx;
    int     processTerminated;
    
    struct info *processes = (struct info*)malloc(tot*sizeof(struct info));

    parseFile(tot);


    //Ready state for all the processes.
    for(i = 0; i < tot; ++i)
    {
        processes[i].state = READY;
        processes[i].currentRunTime = 0;
    }
    
    FILE *outFile;
    outfile = fopenf("output.txt","w");
    


    /**
     * Run in an infinite loop until all of the processes have been put into the
     * terminated state. 
     * Implements a FIRSTCOMEFIRSTSERVE algorithm.
     */
    while(1)
    {
        processTerminated = 0;
        tick = 0;

        if(currentType == EXTERNALPRIORITY){
            int lowPriority = getLowPriority(processes);
            int highPriority = getHighPriority(processes);
            //Increment the priority of the lowest priority process here to prevent starvation
            processes[lowPriority].priority++;


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
            for (i = 0; i < tot; i++)
            {
                if (processes[i].state == WAITING)
                {
                    ++processes[i].IOtime;
                    fprintf(outfile, "PID: %d, ArrivalTime %d, totalCpuTime %d, IOfreq %d, IOdur %d, IOtime %d, currrentRunTime %d, State %s, Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                    if (processes[i].IOtime >= processes[i].IOdur)
                    {
                        fprintf(outfile, "PID: %d, ArrivalTime %d, totalCpuTime %d, IOfreq %d, IOdur %d, IOtime %d, currrentRunTime %d, State %s, Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                        processes[i].state = READY;
                        fprintf(outfile, "PID: %d, ArrivalTime %d, totalCpuTime %d, IOfreq %d, IOdur %d, IOtime %d, currrentRunTime %d, State %s, Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i),  tick);
                    }
                }
            }
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
                    oldState = processes[runningIdx].state;
                    processes[runningIdx].state = TERMINATED;
        
            }
                else
                {
                    /**
                     * Check to see if it is time to interrupt the running process
                     * for I/O actions
                     */
                    if (processes[runningIdx].currentRunTime % processes[runningIdx].IOfreq == 0)
                    {
                        
                        fprintf(outfile, "PID: %d, ArrivalTime %d, totalCpuTime %d, IOfreq %d, IOdur %d, IOtime %d, currrentRunTime %d, State %s, Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                        oldState = processes[runningIdx].state;
                        processes[runningIdx].state = WAITING;
                        fprintf(outfile, "PID: %d, ArrivalTime %d, totalCpuTime %d, IOfreq %d, IOdur %d, IOtime %d, currrentRunTime %d, State %s, Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
        
            }
                }


            }       
            else
            {
                fprintf(outfile, "PID: %d, ArrivalTime %d, totalCpuTime %d, IOfreq %d, IOdur %d, IOtime %d, currrentRunTime %d, State %s, Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i), tick);
                processes[getProcessPriority(processes, tot, READY, tick)].state = RUNNING;
                fprintf(outfile, "PID: %d, ArrivalTime %d, totalCpuTime %d, IOfreq %d, IOdur %d, IOtime %d, currrentRunTime %d, State %s, Tick: %d", processes[i].id,processes[i].arrivalTime, processes[i].totalCpuTime, processes[i].IOfreq, processes[i].IOdur, processes[i].IOtime, processes[i].currentRunTime, getState(processes, i),tick);
            }

            ++tick;      
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
                    if (processes[i].IOtime >= processes[i].IOdur)
                    {
                        /**
                         * It is time to move the process from waiting back to ready
                         * so that it is available to be run again.
                         */
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
                    oldState = processes[runningIdx].state;
                    processes[runningIdx].state = TERMINATED;
        
            }
                else
                {
                    /**
                     * Check to see if it is time to interrupt the running process
                     * for I/O actions
                     */
                    if (processes[runningIdx].currentRunTime % processes[runningIdx].IOfreq == 0)
                    {
                        oldState = processes[runningIdx].state;
                        processes[runningIdx].state = WAITING;
        
            }
                }


            }       
            else
            {
                getProcess(processes, tot, READY,tick)
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
                    if(processes[i].currentRunTime >= processes[i].totalCpuTime){
                        processes[i].state = TERMINATED;                       
                        printf("Process %d, State %s, Tick %d", processes[i].id, processes[i].state, tick);
                    }
                }
            }
                    
            for(i = 0; i<tot; i++){
                //Any Ready proccess is started then put into waiting if it has been commenced.
                if(processes[i].state == READY){
                    TIMEOUT = 0;
                    printf("Process %D, State %S, Tick %D", processes[i].id, processes[i].state, tick);
                    while((TIMEOUT <= 100) && (processes[i].currentRunTime <= processes[i].totalCpuTime)){
                            processes[i].currentRunTime++;
                            TIMEOUT++;
                }
                    processes[i].state = WAITING;
                    printf("Process %D, State %S, Tick %D", processes[i].id, processes[i].state, tick);
            }   
                
                if(processes[i].state == WAITING){
                    TIMEOUT = 0;
                    printf("Process %D, State %S, Tick %D", processes[i].id, processes[i].state, tick);   
                    while((TIMEOUT <= 100) && (processes[i].currentRunTime <= processes[i].totalCpuTime)){
                        processes[i].currentRunTime++;
                        TIMEOUT++;
                    }
                    printf("Process %D, State %S, Tick %D", processes[i].id, processes[i].state, tick);
                }
        }
        tick++;
        }
    }








}

        


    