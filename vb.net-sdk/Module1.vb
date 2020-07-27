
Module Module1

    Sub Main()

        'Creating Object of Class1
        Dim obj As Class1 = New Class1()

        'This is required enput string
        Dim input As String = "date=2020-07-25"

        Dim Out = obj.send(input)

        'Printing Result
        Console.WriteLine(Out)

        Console.WriteLine()
        Console.WriteLine()
        Console.WriteLine()
        Console.WriteLine("Please press enter key to close this console")
        Console.Read()
    End Sub

End Module
