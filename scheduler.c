 /*
 * Brandon Sinjakovic
 * 
 * 09/28/07
 *
 * CS 441/541: CPU Scheduler (Project 2)
 */
#include "scheduler.h"

void read_file(char *file_name) {
    FILE *fd = NULL;
    char line[1024];
    char * token;
    file = strdup(file_name);


    fd = fopen(file_name, "r");

    fgets(line,1024,fd);


    num_processes = atoi(line);
    processes = calloc(num_processes, sizeof(struct process *));

    int i;
    for(i = 0; i < num_processes; i++) {
        fgets(line,1014,fd);
        processes[i] = calloc(1,sizeof(struct process));
        token = strtok(line, " ");
        processes[i]->identifier = atoi(token);

        token = strtok(NULL, " ");
        processes[i]->length = atoi(token);
        processes[i]->time_left = atoi(token);

        token = strtok(NULL, " ");
        processes[i]->priority = atoi(token);

    }

    fclose(fd);
}

void process_cmdline(int argc, char **argv) {
    int i;
    for(i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-s") == 0) {
            if((i+1) < argc) {
                i++;
                has_s = true;
                int order = atoi(argv[i]);

                if(order == 1) {
                    scheduler = strdup("1 FCFS");
                    quantum = 0;
                }
                else if(order == 2) {
                    scheduler = strdup("2 SJF");
                    quantum = 0;
                }
                else if(order == 3) {
                    scheduler = strdup("3 Priority");
                    quantum = 0;
                }
                else if(order == 4) {
                    scheduler = strdup("4 RR");
                    needs_q = true;
                }
                else {
                    is_valid = false;
                    printf("Error: unknown order number\n"); 
                }
            }
        }
        else if(strcmp(argv[i],"-q") == 0) {
            has_q = true;
            if(i+1 < argc) {
                i++;
                quantum = atoi(argv[i]);
                if(quantum <= 0) {
                    is_valid = false;
                    printf("Error: Quantum must be a positive number greater than 0\n");
                }
            }
        }
        else {
            read_file(argv[i]);
        }
    }
}

int compare_burst(const void *first, const void *sec) {

    struct process *job1 = *(struct process**)first;
    struct process *job2 = *(struct process**)sec;

    return (job1->length - job2->length);
}

int compare_priority(const void *first, const void *sec) {
    struct process *job1 = *(struct process**)first;
    struct process *job2 = *(struct process**)sec;

    return (job1->priority - job2->priority);
}


void order_processes() {
    if(strcmp(scheduler,"2 SJF") == 0) {
        qsort((void*)processes, num_processes, sizeof(struct process *), compare_burst);
    }
    else if(strcmp(scheduler,"3 Priority") == 0) {
        qsort((void*)processes, num_processes, sizeof(struct process *), compare_priority);
    }
   
}

void calculate_time() {
    int i;
    int t=0;
    int total_wait = 0;
    int total_turn = 0;
    printf("##################################################\n");
    printf("#  #\tCPU\tPri\t  W\t  T\n");
    if(strcmp(scheduler,"4 RR") == 0) {
        int completed = 0;
        i = 0;

        while(completed < num_processes) {
            if(processes[i%num_processes]->time_left > 0){    


                if(quantum >= processes[i%num_processes]->time_left) {
                    t += processes[i%num_processes]->time_left; 
                    processes[i%num_processes]->time_left = 0; 
                    processes[i%num_processes]->time = t; 
                    processes[i%num_processes]->wait_time = t - processes[i%num_processes]->length;
                    
                    completed++;
                }
                else {
                    processes[i%num_processes]->time_left -= quantum; 
                    t += quantum;
                }
            }
            i++;
        }
        for(i = 0; i < num_processes; i++){
            total_wait += processes[i]->wait_time;

            total_turn += processes[i]->time;
            
            printf("# %2d\t%3d\t%3d\t%3d\t%3d\n", processes[i]->identifier, 
            processes[i]->length, processes[i]->priority, processes[i]->wait_time, processes[i]->time);

        }
    } 
    else {
        for(i = 0; i < num_processes; i++){
            processes[i]->wait_time = t;
            total_wait += processes[i]->wait_time;

            t += processes[i]->length;
            total_turn += t;

            processes[i]->time = t;

        }
        for(i = 0; i < num_processes; i++){
            printf("# %2d\t%3d\t%3d\t%3d\t%3d\n", original_processes[i]->identifier, 
            original_processes[i]->length, original_processes[i]->priority, original_processes[i]->wait_time, original_processes[i]->time);

        }
    }
    printf("##################################################\n");
    printf("# Avg. Waiting Time   : %6.2f\n", ((double)total_wait/(double)num_processes));
    printf("# Avg. Turnaround Time: %6.2f\n", ((double)total_turn/(double)num_processes));
    printf("##################################################\n");
}

int main(int argc, char **argv) {

    process_cmdline(argc, argv);
    if(!is_valid) {
        return 0;
    }
    if(!has_s) {
        printf("Error: -s # is required\n");
        return 0;
    }
    if(needs_q && has_q == false) {
        printf("Error: -s 4 requires a quantum\n");
        return 0;
    }
    printf("Scheduler   :  %s\n",scheduler);
    printf("Quantum     :%3d\n",quantum);
    printf("Sch. File   : %s\n",file);
    printf("-------------------------------\n");
    printf("Arrival Order:");
    
    int i;
    for(i = 0; i < num_processes; i++) {
        printf(" %2d", processes[i]->identifier);

        if(i+1<num_processes) {
            printf(",");
        }
        else {
            printf("\n");
        }
    }
    original_processes = calloc(num_processes, sizeof(struct process*)); //free this at the end
    printf("Process Information:\n");
    for(i = 0; i < num_processes; i++) {
        printf("%2d\t%3d\t%3d\n", processes[i]->identifier, processes[i]->length, processes[i]->priority);
        original_processes[i] = processes[i];
    }
    printf("-------------------------------\n");
    printf("Running...\n");
        


    
    order_processes();
    calculate_time();

    if(scheduler) {
        free(scheduler);
    }
    if(file) {
        free(file);
    }
    for(i = 0; i < num_processes; i++) {
        free(processes[i]);
    }
    free(original_processes);
    free(processes);

    return 0;
}