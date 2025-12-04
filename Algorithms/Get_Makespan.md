Algorithm Get_Makespan(Load[1..m], m)

    max ← Load[1]

    For i ← 2 to m do
        If Load[i] > max then
            max ← Load[i]
        End If
    End For

    Return max

End Algorithm
