#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Priority (lower value means higher priority)
    int remaining;  // Remaining burst time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting;    // Waiting time
    int response;   // Response time
    int started;    // Flag to track if process has started execution
} Process;

// Basic input for arrival and burst times only
void input(Process *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].started = 0;
        p[i].priority = 0; // Default priority
    }
}

// Input for priority scheduling
void input_priority(Process *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time, burst time, and priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].pid = i + 1;
        p[i].remaining = p[i].burst;
        p[i].started = 0;
    }
}

void display(Process *p, int n, int show_priority) {
    float avg_turnaround = 0, avg_waiting = 0, avg_response = 0;
    
    if (show_priority) {
        printf("\n| PID | Arrival | Burst | Priority | Completion | Turnaround | Waiting | Response |\n");
        printf("|-----|---------|-------|----------|------------|------------|---------|----------|\n");
        
        for (int i = 0; i < n; i++) {
            printf("| P%d  | %7d | %5d | %8d | %10d | %10d | %7d | %8d |\n",
                   p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
                   p[i].completion, p[i].turnaround, p[i].waiting, p[i].response);
            
            avg_turnaround += p[i].turnaround;
            avg_waiting += p[i].waiting;
            avg_response += p[i].response;
        }
    } else {
        printf("\n| PID | Arrival | Burst | Completion | Turnaround | Waiting | Response |\n");
        printf("|-----|---------|-------|------------|------------|---------|----------|\n");
        
        for (int i = 0; i < n; i++) {
            printf("| P%d  | %7d | %5d | %10d | %10d | %7d | %8d |\n",
                   p[i].pid, p[i].arrival, p[i].burst,
                   p[i].completion, p[i].turnaround, p[i].waiting, p[i].response);
            
            avg_turnaround += p[i].turnaround;
            avg_waiting += p[i].waiting;
            avg_response += p[i].response;
        }
    }
    
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround / n);
    printf("\nAverage Waiting Time: %.2f", avg_waiting / n);
    printf("\nAverage Response Time: %.2f\n", avg_response / n);
}

// First Come First Serve
void fcfs(Process *p, int n) {
    input(p, n);
    
    // Sort processes by arrival time
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].arrival > p[j+1].arrival) {
                // Swap processes
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    
    int time = 0;
    
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;  // CPU idle until next process arrives
            
        p[i].response = time - p[i].arrival;  // Response time when process starts
        p[i].completion = time + p[i].burst;  // Completion time
        p[i].turnaround = p[i].completion - p[i].arrival;  // Turnaround time
        p[i].waiting = p[i].turnaround - p[i].burst;  // Waiting time
        
        time = p[i].completion;  // Update current time
    }
    
    display(p, n, 0);
}

// Shortest Job First (Non-preemptive)
void sjf(Process *p, int n) {
    input(p, n);
    
    int time = 0, completed = 0;
    int processed[n];
    
    // Initialize processed array
    for (int i = 0; i < n; i++) 
        processed[i] = 0;
    
    while (completed < n) {
        int min_burst = 1e9;  // Large number
        int min_index = -1;
        
        // Find process with shortest burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (!processed[i] && p[i].arrival <= time && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                min_index = i;
            }
        }
        
        // If no process is available, advance time
        if (min_index == -1) {
            time++;
            continue;
        }
        
        // Process the selected job
        processed[min_index] = 1;
        p[min_index].response = time - p[min_index].arrival;
        p[min_index].completion = time + p[min_index].burst;
        p[min_index].turnaround = p[min_index].completion - p[min_index].arrival;
        p[min_index].waiting = p[min_index].turnaround - p[min_index].burst;
        
        time = p[min_index].completion;
        completed++;
    }
    
    display(p, n, 0);
}

// Shortest Remaining Time First (Preemptive)
void srtf(Process *p, int n) {
    input(p, n);
    
    int time = 0, completed = 0;
    
    while (completed < n) {
        int min_index = -1;
        int min_remaining = 1e9;  // Large number
        
        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].remaining < min_remaining) {
                    min_remaining = p[i].remaining;
                    min_index = i;
                }
            }
        }
        
        // If no process is available, advance time
        if (min_index == -1) {
            time++;
            continue;
        }
        
        // Track response time when process first starts
        if (p[min_index].started == 0) {
            p[min_index].response = time - p[min_index].arrival;
            p[min_index].started = 1;
        }
        
        // Execute process for 1 time unit
        p[min_index].remaining--;
        time++;
        
        // If process is complete
        if (p[min_index].remaining == 0) {
            p[min_index].completion = time;
            p[min_index].turnaround = p[min_index].completion - p[min_index].arrival;
            p[min_index].waiting = p[min_index].turnaround - p[min_index].burst;
            completed++;
        }
    }
    
    display(p, n, 0);
}

// Priority Scheduling (Non-preemptive)
void priority(Process *p, int n) {
    input_priority(p, n);
    
    int time = 0, completed = 0;
    int processed[n];
    
    // Initialize processed array
    for (int i = 0; i < n; i++) 
        processed[i] = 0;
    
    while (completed < n) {
        int highest_priority = 1e9;  // Large number (lower value = higher priority)
        int selected_proc = -1;
        
        // Find process with highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (!processed[i] && p[i].arrival <= time && p[i].priority < highest_priority) {
                highest_priority = p[i].priority;
                selected_proc = i;
            }
        }
        
        // If no process is available, advance time
        if (selected_proc == -1) {
            time++;
            continue;
        }
        
        // Process the selected job
        processed[selected_proc] = 1;
        p[selected_proc].response = time - p[selected_proc].arrival;
        p[selected_proc].completion = time + p[selected_proc].burst;
        p[selected_proc].turnaround = p[selected_proc].completion - p[selected_proc].arrival;
        p[selected_proc].waiting = p[selected_proc].turnaround - p[selected_proc].burst;
        
        time = p[selected_proc].completion;
        completed++;
    }
    
    display(p, n, 1);
}

// Round Robin Scheduling
void round_robin(Process *p, int n) {
    input(p, n);
    
    int quantum;
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    int time = 0, completed = 0;
    int remaining[n];
    
    // Initialize remaining times and reset started flag
    for (int i = 0; i < n; i++) {
        remaining[i] = p[i].burst;
        p[i].started = 0;
    }
    
    // Continue until all processes are completed
    while (completed < n) {
        int flag = 0;  // Flag to check if any process was executed in this iteration
        
        // Iterate through all processes
        for (int i = 0; i < n; i++) {
            // If process has arrived and has remaining time
            if (p[i].arrival <= time && remaining[i] > 0) {
                flag = 1;  // A process was executed
                
                // Record response time for first execution
                if (p[i].started == 0) {
                    p[i].response = time - p[i].arrival;
                    p[i].started = 1;
                }
                
                // Execute for quantum or remaining time, whichever is smaller
                int exec_time = (remaining[i] < quantum) ? remaining[i] : quantum;
                remaining[i] -= exec_time;
                time += exec_time;
                
                // If process is complete
                if (remaining[i] == 0) {
                    p[i].completion = time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    completed++;
                }
            }
        }
        
        // If no process was executed in this iteration, advance time
        if (flag == 0) {
            time++;
        }
    }
    
    display(p, n, 0);
}

// Longest Job First (Non-preemptive)
void ljf(Process *p, int n) {
    input(p, n);
    
    int time = 0, completed = 0;
    int processed[n];
    
    // Initialize processed array
    for (int i = 0; i < n; i++) 
        processed[i] = 0;
    
    while (completed < n) {
        int max_burst = -1;
        int max_index = -1;
        
        // Find process with longest burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (!processed[i] && p[i].arrival <= time && p[i].burst > max_burst) {
                max_burst = p[i].burst;
                max_index = i;
            }
        }
        
        // If no process is available, advance time
        if (max_index == -1) {
            time++;
            continue;
        }
        
        // Process the selected job
        processed[max_index] = 1;
        p[max_index].response = time - p[max_index].arrival;
        p[max_index].completion = time + p[max_index].burst;
        p[max_index].turnaround = p[max_index].completion - p[max_index].arrival;
        p[max_index].waiting = p[max_index].turnaround - p[max_index].burst;
        
        time = p[max_index].completion;
        completed++;
    }
    
    display(p, n, 0);
}

int main() {
    int n, choice;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process *p = (Process *)malloc(n * sizeof(Process));
    
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS (First Come First Serve)\n");
    printf("2. SJF (Shortest Job First - Non-Preemptive)\n");
    printf("3. SRTF (Shortest Remaining Time First - Preemptive)\n");
    printf("4. Priority (Non-Preemptive)\n");
    printf("5. Round Robin\n");
    printf("6. LJF (Longest Job First - Non-Preemptive)\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            fcfs(p, n);
            break;
        case 2:
            sjf(p, n);
            break;
        case 3:
            srtf(p, n);
            break;
        case 4:
            priority(p, n);
            break;
        case 5:
            round_robin(p, n);
            break;
        case 6:
            ljf(p, n);
            break;
        default:
            printf("Invalid choice!\n");
            free(p);
            return 1;
    }
    
    free(p);
    return 0;
}
