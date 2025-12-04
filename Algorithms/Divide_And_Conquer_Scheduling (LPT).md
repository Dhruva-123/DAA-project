Algorithm LPT_Load_Balancing(Tasks[1..n], n, Load[1..m], m)

    Sort_Tasks_Descending(Tasks, n)

    For i ← 1 to n do
        minIndex ← 1

        For j ← 2 to m do
            If Load[j] < Load[minIndex] then
                minIndex ← j
            End If
        End For

        Assign Task i to Server minIndex
        Load[minIndex] ← Load[minIndex] + Tasks[i].time
    End For

End Algorithm
