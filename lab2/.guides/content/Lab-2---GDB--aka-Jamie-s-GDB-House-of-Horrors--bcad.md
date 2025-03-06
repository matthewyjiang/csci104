---

**Due: At the end of the lab section you registered for**

You are expected to show your work to any CP/TA to get checked off during the lab section you registered for.

---

# Jamie's GDB House of Horrors

Can you survive the maze of segfaults, and banish a battery of blatantly bad behavior, all in the name of improving your GDB skills?
This lab will guide you through hunting down the kind of bugs that keep programmers awake at night.
Do you dare take it on?

![Title](.guides/img/gdb_house_of_horrors.png)

## Lab Checkoff Policies

Unlike a homework, you are not submitting anything for a lab. Instead, you need to demonstrate your working code to a CP/TA 
**during the lab section you registered for**. Thus, we encourage you to get help as soon as possible during the lab when you feel that you
are stuck.

## Lab Materials

The files we'll be using for this lab are all under the `lab2` directory (remember to do `cd lab2` before you run any other commands!).

In the `lab2` directory you should see the following files:

1. `answers.txt`
2. `game_of_pointers_student1.cpp`
3. `game_of_pointers_student2.cpp`
4. `input1.txt`
5. `input2.txt`
6. `input3.txt`
7. `Makefile`
8. `output1.check`
9. `output2.check`
10. `output3.check`

If you wish to work on this lab locally (i.e. on your PC/Mac/ or in a docker container), you can do so by doing `Project | Export as zip` in Codio. You are free
to demonstrate your work in either Codio or your local environment.

## What is a debugger?

At its core, a debugger is a tool used to inspect a program while it is running.
You run it on the command line, passing an executable as an argument, and it interposes itself between the program and the system and monitors everything that the program does.
It runs through a program until it hits a preset point, called a *breakpoint*, which tells it to pause the program.
When paused, you can ask it to evaluate variables, call functions, and examine the call stack.
You can then resume your program, or step through it line-by-line.

Debuggers are critical tools in any programmer's debugging arsenal, and are best when you need to trace the flow of your code through a complex process or algorithm.
Today, we will be illustrating how to use one!
But first, let's go over some common tips and tricks for debugging.

### Identify the Issue

The most common two ways your code will terminate (besides a successful execution) is by a Segmentation Fault (`SIGSEGV`) or by an Abort (`SIGABRT`).
These will automatically trigger the debugger to break, so you don't have to.

- **Segfault**: when a program tries to read or write outside the memory that is allocated for it, or to write memory that can only be read. 
- **Abort**: indicates an error detected by the program itself.

The other issues could be:

- **Infinite loop or recursion**: caused by faulty logic or base case.
- **Logic**: `2 + 2 == 5`? code is correct but the logic is faulty.
- **Translation error**: the logic is correct but it was just coded incorrectly.

### Isolate the Problem

In order to successfully find the issue, you need to be able to answer a few questions:

1. What line is the problem occurring on?
    - Read through long standard library backtraces.
      Often, a segfault or exception will happen deep inside C++ standard library code, and you will get a backtrace with several frames of obscurely named and templated functions at the top.
      Just ignore those, and find the highest frame that mentions your code.
      That is usually where the actual error is.
    - Use Valgrind as well.
      If all you need is the backtrace for a segfault, Valgrind can give that to you without any hassle.
      Also, note that GDB will always stop on the first memory error.
      Valgrind, on the other hand, will keep continuing the program until there's an unrecoverable error.
      This can help you see the bigger picture for certain memory issues.
    - You can also use break points and `cerr` statements to find what line the problem is occurring on.

2. When does this bug occur? 
    - Are their certain situations where the issue presents itself? 
    - Is it only when I am using a certain function or trying to do a specific action.

3. Can I reliably produce this bug over and over again? 
    - Create a separate test case to make the problem clear.

### Why is the Issue Occurring?

The main question to ask is, "is the problem conceptual, logical, or coding error?"
To answer, understand what your function/code is trying to and then use `cerr` statements or GDB in order to identify what the values of variables are to determine if they are correct or not.

- Carefully place breakpoints.
  You want to break at the start of the area where the problem might be occurring, not before and not after.
  If you have to step a long distance through the code, you might accidentally step through something important.
  If your error is happening on the 12,000th loop through a giant algorithm, you might want to refactor your code to give you someplace to put a breakpoint.
- Print important variables.
  Use the `print` GDB command to check the values of any suspicious variables.
  Don't forget that by calling print with a struct or class, it will print out all the member variables of that class. 
- Use `cerr` statements.
  For localizing a fault to a specific area of the code, or tracing the flow of an entire program, it's invaluable to just print out important values and messages throughout your program.
  Remember to use `cerr` rather than `cout` so your output is guaranteed to be flushed to the terminal before the program terminates.

### The General Workflow for Using with GDB

If you are using Codio, you need to start a terminal first by clicking `Tools | Terminal`.

Assume you want to compile and debug your program coded in `example.cpp`. The first thing you need to do is to compile your program:

```c++
g++ -g example.cpp -o example
```

Notice that we add a `-g` flag to the command. This tells the compiler to generate information needed for the debugger while compiling.
This is a necessary step, and if you remove the flag the debugger would tell you that debugging symbols are missing.

Then, you run gdb and supply the program to debug.

```shell
gdb ./example
```

Notice that the argument you pass to gdb is file name of the executable (i.e. `./example`), not the source file (i.e. `./example.cpp`).

Then, you may type `run` to run your program. If you wish to run your program with more command-line arguments (i.e. `./example 12`),
you just put the arguments after the `run` command (i.e. `run 12`).

For more commands you could use in GDB, check the cheatsheet below. We will also run through the most common ones in the [Game of Pointers](#markdown-header-game-of-pointers) section.

### GDB Command Cheat Sheet

This cheatsheet is also available on the [wiki](https://bytes.usc.edu/cs104/wiki/gdb/) for future reference.

- `run/r [arguments]` runs the program with the given arguments.
- `break/b [file.cpp:line number]` puts a breakpoint at the given line number in the given file.
  Note that if you only have one file, just break `[line number]` will suffice.
- `break/b [function name]` places a breakpoint at the start of the given function.
- `clear [file.cpp:line number]` clears a breakpoint at the given line number in the given file.
  Note that if you only have one file, just clear `[line number]` will suffice.
- `clear [function name]` removes the breakpoint on the given function.
  Note: function breakpoints will not work on functions that take strings as arguments (it's complicated) on your course VM due to an incompatibility between GCC and GDB.
  However, this will work properly on newer systems.
- `layout next` From the begining of GDB, entering 'layout next' once the program is running will show you source code around your current location in the program. 
  This view can be helpful to those who are new to gdb, and especially helpful when working with source code you are not farmiliar with. 
  Repeating 'layout next' shows your program in assembly language.
- `layout prev` Takes you back to the previous layout mode. 
- `bt` shows the function call stack, every function that you've run through since the line you've arrived at.
- `frame [number]` goes to the selected frame in the call stack.
- `continue/c` continues the program after being stopped by a breakpoint.
- `print/p [variable]` prints out the variable value.
  If you pass it a class/struct instance, it will print all the data members in the class.
- `display/d [variable]` is like print, but reprints the information after every instruction.
- `next/n` executes the current source line and moves it to the next one.
  Will skip over any function calls.
  If you were to have the line `x = getValue(y)` and used `n`, you would go to the next line in the current function call, ignoring what happens in `getValue(y)`.
  Useful for when you're testing out a function and you KNOW your helper functions work.
- `step/s` executes the current source line and moves it to the next one.
  Will step INTO any function calls.
  If you were to have the line `x = getValue(y)` and used `s`, you would go into the `getValue(y)` function.
- `finish/f` executes the rest of the current function.
  Will step OUT of the current function.
- `l/list` prints the area around the current line in the current source file.
- `where` displays the current line and the function stack of calls that got you there.
- `quit` exits GDB.

## Game of Pointers

The code we will be debugging today is a student assignment from a past iteration of the class.
The details are not super important, but essentially it is a simulator for a battle between two armies, the protectors and the invaders.
The members of one row/column of each army duel in each skirmish, and the battle ends either when there is a gap in the ranks of the protectors, or when the protectors are able to last through every round of the fight.
The twist is that one of the armies is laid out sideways, so row `i` of the invaders duels column `i` of the protectors.
Think of it like matrix multiplication, but with more violence!

![game_of_pointers](.guides/img/game_of_pointers.png)

Two students (whose names have been omitted to protect the guilty) attempted this problem, but didn't get it quite right.
We're now going to find the bugs in their programs with GDB.  

### Directions

For each problem below, answer in `answers.txt` with:

- The line number where the error was.
- A **short** explanation of the nature of the error (one or two sentences).
- A **short** explanation of what you did to fix the error.


## Problem 1 (Guided)

Okay, so let's check out the first student's program.
Open a terminal in the assignment directory, and run the simulation with `make test_game1`. 

If you are using Docker, please first move the `lab2` directory into the directory you mounted to the Docker container in Lab 0, if it is not already in there. Remember to open a shell before proceeding (ie, by running `ch shell csci104`). If you don't have a container running yet, remember to run `ch start csci104` before opening a shell!

You should get something like:

```
******************************************************************
                   Testing Student 1's Game
******************************************************************
./game_student1 input1.txt output1-stu1.txt
Makefile:15: recipe for target 'test_game1' failed
make: *** [test_game1] Segmentation fault (core dumped)
```

* Run `make test_game1`.

Uh-oh.
That's not good.
In the past, you might have ran screaming from an error like this, but now we have tools to attack it!
Run GDB on the program with the terminal command `gdb ./game_student1`.
You should now have a terminal prompt that looks like:

```
(gdb)
```

* Start `gdb` with the newly compiled `game_student1`.

The program has not been started yet, and GDB is now awaiting your commands.
Just to practice, let's set a breakpoint at the start of the program so it will stop right away.
Run the command `break main`.
You should get:

```
(gdb) break main
Breakpoint 1 at 0x401d81: file game_of_pointers_student1.cpp, line 198.
```

* Set a breakpoint on `main`.

Now, let's start the program, supplying the command line arguments for its input and output files: `run input1.txt output1-stu1.txt`.
You should get:

```
(gdb) run input1.txt output1-stu1.txt
Starting program: ./game_student1 input1.txt output1-stu1.txt

Breakpoint 1, main (argc=3, argv=0x7fffffffdc58)
    at game_of_pointers_student1.cpp:198
198	{
```

* Run the program with input and output files.

GDB has now started your program, and it stopped on the breakpoint we set earlier.
You can set these breakpoints on any function name or source line in your code, and GDB will stop there.

If you enter the `n` command a few times, you can now step through the main function one line at a time.
Cool, right?
However, it would take forever to search through the entire program this way.
Instead, let's just head straight to the segfault.
Luckily, GDB automatically breaks on segfaults, so we don't have to worry about breakpoint positioning right now.
Enter `c` to continue straight to the issue.
You should get: 

```
(gdb) c
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x0000000000402050 in main (argc=<optimized out>, argv=<optimized out>)
    at game_of_pointers_student1.cpp:252
252	            invaders[invaderRow][invaderCol]->power = invaderRow * 10 + (invaderCol + 1) * 10;
```

* Use `continue` to get to our error.

GDB is now at the point of the segfault, ready for you to analyze what's wrong.
Since the segfault is occurring on this line, we already have a pretty big clue on what's wrong.
There's only one pointer being dereferenced here.
Let's check out its value: `print invaders[invaderRow][invaderCol]`

```
(gdb) print invaders[invaderRow][invaderCol]
$1 = (Warrior *) 0x0
```

* Check the value of the dereferenced pointer.

GDB is telling us it's a null pointer!
Fantastic!
We now know where the problem is, and that's usually more than half the battle in debugging.
But we still have to figure out *why* it's null.
Open `game_of_pointers_student1.cpp` and look at what allocates `invaders[invaderRow][invaderCol]`, on line 249:

```cpp
invaders[invaderRow][invaderRow] = new Warrior();
```

See anything suspicious on that line?
Perhaps, with the array indices of `invaders`? 
Compare the indices on that line to the ones used on line 252.
The issue should be fairly clear.  

* Fix the mistake and describe your solution in `answers.txt` as outlined above.

## Problem 2 (Semi-Guided)

When you run `make test_game1` again, you should see that the segfault is fixed, but the program fails its first test case.
The output file should be

```
Invader killed
Duel ends in draw
Winner: protectors
```
but instead it's

```
Invader killed
Invader killed
Winner: protectors
```

Clearly there is some sort of logic error affecting the result of the second duel.
To debug this, we will need to trace the issue back through the code.
It looks like `"Invader killed"` is being output inside skirmish() at line 135:

```cpp
else if (result == result_protector)
{
	output << "Invader killed" << std::endl;
	delete invader;
	invader = nullptr;
}
```

`result`, meanwhile, comes from the call to `getDuelResult()` on line 99.

That if statement looks like a good place to start our investigation. 
We can check if the result really is set wrong, or if there is some sort of logic error causing `result` to be interpreted incorrectly.

Again, run GDB on the `game_student1` executable.  
Since we want to investigate the if statement in skirmish, let's set a breakpoint on line 101: `break game_of_pointers_student1.cpp:101`
Next, run the program from GDB like you did in Problem 1.

```
(gdb) run input1.txt output1-stu1.txt
Starting program: ./game_student1 input1.txt output1-stu1.txt

Breakpoint 1, skirmish (protectors=protectors@entry=0x61a0a0, 
    invaders=invaders@entry=0x61a0c0, skirmish_col=0, rows=2, columns=3, 
    reserves=@0x7fffffffd724: 1, output=...)
    at game_of_pointers_student1.cpp:101
101			if (result == result_invader)
```

* Rerun `gdb` with `game_student1`.
* Set the breakpoint and run the program.

Now, the program ran until it hit the breakpoint.
However, only the second duel is producing an incorrect result, so we want to wait until the second time this code runs.
Continue the program once with `c`.

```
(gdb) c
Continuing.

Breakpoint 1, skirmish (protectors=protectors@entry=0x61a0a0, 
    invaders=invaders@entry=0x61a0c0, skirmish_col=0, rows=2, columns=3, 
    reserves=@0x7fffffffd724: 1, output=...)
    at game_of_pointers_student1.cpp:101
101			if (result == result_invader)
```

Now, we're at the second skirmish.
Check the value of `result` with `print result`.

```
(gdb) print result
$1 = "protector"
```

* Continue to the second skirmish.
* Print the value of `result`.

Now we have some useful information.
Clearly result is being set wrong in `getDuelResult()`.
_Your_ job is to figure out why.
Set a breakpoint wherever you think is appropriate, restart the program using the same run command as you used before, and figure out what the issue is inside `getDuelResult()`.
Describe your solution and your fix in `answers.txt`.

* Figure out what's going wrong in `getDuelResult()`.
* Write up the answer in `answers.txt`.

## Problem 3 (Semi-Guided)

Run `make test_game1` in terminal, and you should see the first test pass!
Unfortunately, the second test gets stuck in an infinite loop.
Luckily, GDB lets us debug infinite loops easily!
We may not be able to catch the issue with a breakpoint since we don't know where the loop is, but there is another strategy that works great here.

First, load the program into GDB and run it without setting any breakpoints.
Don't forget to use the second input and output files in this run command!

* Load the program into `gdb`.
* Run the program with the second input and output files.

Like you can cancel a program on the command line, GDB lets you use `ctrl-c` to stop a program wherever it currently is.
Hit `ctrl-c` now to break the infinite loop.

```
(gdb) run input2.txt output2-stu1.txt
Starting program: ./game_student1 input2.txt output2-stu1.txt
^C
Program received signal SIGINT, Interrupt.
0x000000000040142f in findOpenInvaderPos (invaders=invaders@entry=0x61a0c0, 
    numRows=numRows@entry=5, numCols=numCols@entry=2)
    at game_of_pointers_student1.cpp:64
64				if (invaders[rowIdx][colIdx] == nullptr)
```

* Use `ctrl-c` to send a `SIGINT` interrupt.

So, the code is stopped at some point within the infinite loop, but we don't really know where in the program we are.
To find out, use the backtrace command: `bt`

```
(gdb) bt
#0  0x000000000040142f in findOpenInvaderPos (invaders=invaders@entry=0x61a0c0, numRows=numRows@entry=5, numCols=numCols@entry=2) 
    at game_of_pointers_student1.cpp:64
#1  0x0000000000401a55 in skirmish (protectors=protectors@entry=0x61a0a0, invaders=invaders@entry=0x61a0c0, skirmish_col=1, rows=2, columns=5, reserves=@0x7fffffffd724: 1, output=...)
    at game_of_pointers_student1.cpp:103
#2  0x0000000000402112 in main (argc=<optimized out>, argv=<optimized out>)
    at game_of_pointers_student1.cpp:284
```

* Backtrace to figure out where you are.

This backtrace contains a wealth of useful information.
Each numbered paragraph represents one frame in the current call stack of the program.
Frame `#0` is always the current function, and we see frames going up to the `main()` function of the program.
The first hexadecimal number is the address of the function in memory (not really important right now).
Next, we have the name of the function and the arguments it was called with, and finally the file and line number.
The backtrace is an extremely useful tool since it lets you get a quick glance at which functions were called to bring the program to its current state.

We are also able to move around through the backtrace and inspect the environment at each stack frame.
Let's switch to frame 1 with the command `frame 1`.

```
(gdb) frame 1
#1  0x0000000000401a55 in skirmish (protectors=protectors@entry=0x61a0a0, invaders=invaders@entry=0x61a0c0, skirmish_col=1, rows=2, columns=5, reserves=@0x7fffffffd724: 1, output=...)
    at game_of_pointers_student1.cpp:103
103				Warrior **firstOpenInvaderPos = findOpenInvaderPos(invaders, columns, rows);
```

* Switch to frame 1.

The program is in skirmish() at line 103.
Let's check out the values of `columns` and `rows`.

```
(gdb) print columns
$1 = 5
(gdb) print rows
$2 = 2
```

* Check `columns` and `rows`.

Those numbers match the dimensions in input2.txt, so they seem legitimate.
Your job, now, is to figure out why the code is getting in a loop.
I highly suggest changing back to frame 0 and stepping the code forward with `n` to figure out where exactly it is looping. 

* Figure out the cause of the loop and describe your solution in `answers.txt`.

## Problem 4

Now, run the second student's program by running `make test_game2` in the terminal.
You'll find that the code won't finish executing because of a segmentation fault. 

When debugging this error, keep in mind that the invader and protector arrays are different sizes.
Try to find out what those sizes are, and determine whether they're used consistently in the `AllocateWarriors` and `DeallocateWarriors` functions.

* Fix the mistake, and describe your solution in `answers.txt`.

After you've fixed it, you should be passing two of the three tests. 

## Problem 5

A common use case of GDB is to figure out which code path is executing.
In cases where there are many conditional statements, GDB can be a much quicker tool to use than print statements.
Student 2's code contains a logical error: some duels aren't turning out as they should.
Run `make test_game2` and use your test output along with GDB to figure out exactly what went wrong.

You will probably want to break the code inside `Skirmish()` and observe how the logic in there is behaving.
The most straightforward way to do this is to set a breakpoint on the first `if` statement in that function.
Once GDB breaks there, you will be on the first call to `Skirmish()`.
If you want to go to the next call, just resume the program with the `c` command and wait for it to hit the breakpoint again.
Think, which call to `Skirmish()` does the program output the wrong thing on?  Go to the correct iteration and step through the logic, and the issue should show itself.

* Fix the mistake, and describe your solution in `answers.txt`.

### That's it!

You have stood fast in the face of overwhelming peril, and banished the bugs back to whence they came!
<del>The world</del> <del>the town</del> your computer is safe once again!

* Show a CP or TA  `answers.txt` to get checked off!!
