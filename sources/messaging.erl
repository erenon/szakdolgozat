-module(messaging).
-compile(export_all).

taskProcessor() ->
    receive
        {Data, Pred} ->
            Pred(Data),
            taskProcessor();
        {quit} ->
            true;
        _ ->
            taskProcessor()
    end.
    
main() ->
    TaskProcessor = spawn(messaging, taskProcessor, []),
    TaskProcessor ! {1, fun(X) -> io:format("Task data: ~w~n", [X]) end},
    TaskProcessor ! {quit}.

