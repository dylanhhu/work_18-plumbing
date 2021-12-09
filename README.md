# work_18-plumbing
Dylan Hu - Work 18: Plumbing

## Description
This program opens two pipes, and then forks. The parent continually reads from stdin, and then writes the recieved string to the pipe for the child to process. The child reverses the string recieved, and then writes to the pipe for the parent to print out again.

## Compilation and Execution
To compile, use `make`. To run the program, use `make run`. To exit, use `ctrl+c`, since the parent doesn't know when to quit based on input.

`make run` actually recompiles before running as well, so you can use `make run` on its own, without `make` beforehand.
