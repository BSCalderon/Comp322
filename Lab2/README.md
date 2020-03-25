# Launch-Tube

![alt text](https://media.giphy.com/media/s6S4NpLuw8o5G/giphy.gif "launch tube")

In this lab project, we develop two programs, one called 'launch' and one called 'tube'. The launch program will use a child process to launch the program that was entered as a command line argument. The tube program will create two children and each children will execute their respective programs that will be inputted through command line arguments.

## Usage for launch

```
./launch /bin/ls

```

## Output Example for launch

```
/bin/ls: $$ = 26843
a.out foo.c
/bin/ls: $? = 0
```
## Usage for tube

```
./tube /bin/cat filename , /usr/bin/head -2
```

## Output Example for tube

```
/bin/cat: $$ = 26843
/bin/head: $$ = 26844
This is the first line
This is the second line
/bin/cat: $? = 0
/bin/head: $? = 
```