Algorithm Cloud_Load_Balancer_Main()

    Display "Cloud Task Load Balancer"

    Read m
    Read n

    Create array Tasks[1..n]
    For i ← 1 to n do
        Read Tasks[i].time
        Tasks[i].id ← i
    End For

    ServersGreedy ← Initialize_Servers(m)
    Greedy_Load_Balancing(Tasks, n, ServersGreedy, m)
    GreedyMakespan ← Get_Makespan(ServersGreedy, m)
    Print_Server_Loads(ServersGreedy, m)

    ServersDC ← Initialize_Servers(m)
    LPT_Load_Balancing(Tasks, n, ServersDC, m)
    DCMakespan ← Get_Makespan(ServersDC, m)
    Print_Server_Loads(ServersDC, m)

    If GreedyMakespan < DCMakespan then
        Display "Best Algorithm: Greedy"
    Else If DCMakespan < GreedyMakespan then
        Display "Best Algorithm: Divide & Conquer (LPT)"
    Else
        Display "Both Algorithms Perform Equally"
    End If

End Algorithm
