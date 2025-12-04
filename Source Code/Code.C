#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int id;
    int load; // how much work this server has so far
} Server;

typedef struct
{
    int id;
    int time; // how long this task takes
} Task;

// make all servers ready, set their load to zero
Server *initializeServers(int m)
{
    Server *servers = (Server *)malloc(sizeof(Server) * m);
    for (int i = 0; i < m; i++)
    {
        servers[i].id = i + 1;
        servers[i].load = 0;
    }
    return servers;
}

// find the server that's working the hardest
int getMakespan(Server *servers, int m)
{
    int max = servers[0].load;
    for (int i = 1; i < m; i++)
        if (servers[i].load > max)
            max = servers[i].load;
    return max;
}

// just print out how much work each server ended up with
void printServerLoads(Server *servers, int m)
{
    printf("\nFinal Server Loads:\n");
    for (int i = 0; i < m; i++)
        printf("Server %d => Load: %d\n", servers[i].id, servers[i].load);
}

// assign each task to the server with the least work so far
void greedySchedule(Task *tasks, int n, Server *servers, int m)
{
    printf("\n--- Greedy Algorithm Scheduling ---\n");
    for (int i = 0; i < n; i++)
    {
        int minIndex = 0;
        for (int j = 1; j < m; j++)
            if (servers[j].load < servers[minIndex].load)
                minIndex = j;

        servers[minIndex].load += tasks[i].time;
        printf("Task %d (%d units) → Server %d | New Load = %d\n",
               tasks[i].id, tasks[i].time, servers[minIndex].id, servers[minIndex].load);
    }
}

// sort tasks so the big ones go first
void sortTasksDescending(Task *tasks, int n)
{
    Task temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tasks[j].time > tasks[i].time)
            {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
}

// do LPT: biggest task first, then greedy assignment
void divideAndConquerSchedule(Task *tasks, int n, Server *servers, int m)
{
    printf("\n--- Divide & Conquer (LPT) Scheduling ---\n");
    sortTasksDescending(tasks, n); // biggest tasks first

    for (int i = 0; i < n; i++)
    {
        int minIndex = 0;
        for (int j = 1; j < m; j++)
            if (servers[j].load < servers[minIndex].load)
                minIndex = j;

        servers[minIndex].load += tasks[i].time;
        printf("Task %d (%d units) → Server %d | New Load = %d\n",
               tasks[i].id, tasks[i].time, servers[minIndex].id, servers[minIndex].load);
    }
}

int main()
{
    int n, m;

    printf("====== Cloud Task Load Balancer ======\n");
    printf("\nEnter number of servers: ");
    scanf("%d", &m);
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task *tasks = (Task *)malloc(sizeof(Task) * n);

    printf("\nEnter execution time for each task:\n");
    for (int i = 0; i < n; i++)
    {
        tasks[i].id = i + 1;
        printf("Task %d time: ", i + 1);
        scanf("%d", &tasks[i].time);
    }

    // let's see how greedy does it
    Server *serversGreedy = initializeServers(m);
    greedySchedule(tasks, n, serversGreedy, m);
    int greedyMakespan = getMakespan(serversGreedy, m);
    printServerLoads(serversGreedy, m);

    // now LPT for a smarter distribution
    Server *serversDC = initializeServers(m);
    divideAndConquerSchedule(tasks, n, serversDC, m);
    int dcMakespan = getMakespan(serversDC, m);
    printServerLoads(serversDC, m);

    // quick summary of who did better
    printf("\n==============================");
    printf("\n       PERFORMANCE SUMMARY");
    printf("\n==============================");
    printf("\nGreedy Makespan        : %d", greedyMakespan);
    printf("\nDivide & Conquer LPT   : %d", dcMakespan);

    printf("\n\nBest Algorithm: ");
    if (greedyMakespan < dcMakespan)
        printf("Greedy");
    else if (dcMakespan < greedyMakespan)
        printf("Divide & Conquer (LPT)");
    else
        printf("Both are equal");
    printf("\n==============================\n");

    free(tasks);
    free(serversGreedy);
    free(serversDC);

    return 0;
}
