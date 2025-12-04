Algorithm Sort_Tasks_Descending(Tasks[1..n], n)

    For i ← 1 to n-1 do
        For j ← i+1 to n do
            If Tasks[j].time > Tasks[i].time then
                Swap Tasks[i] and Tasks[j]
            End If
        End For
    End For

End Algorithm

