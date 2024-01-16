``
# Philosophers

## Overview
The Philosophers project is part of the 42 school curriculum, focusing on the basics of threading a process. It involves solving the classic dining philosopher's problem using threads and mutexes. The goal is to learn about the problems of synchronization, deadlocks, and race conditions and how to solve them.

## Problem Description
- A number of philosophers are sitting at a round table doing one of three things: eating, thinking, or sleeping.
- While eating, they are not thinking or sleeping; while thinking, they are not eating or sleeping; and while sleeping, they are not eating or thinking.
- There are as many forks as philosophers.
- A philosopher needs to use two forks to eat.
- Philosophers must avoid dying of starvation.

## Usage

### Compilation
To compile the program, use:
```bash
gcc -Wall -Wextra -Werror *.c -o philosophers -lpthread
```

### Execution
Run the program with:
```bash
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters
- `number_of_philosophers`: The number of philosophers and forks.
- `time_to_die`: The maximum time a philosopher can spend without eating before dying.
- `time_to_eat`: The time it takes for a philosopher to eat.
- `time_to_sleep`: The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): If all philosophers eat at least this many times, the simulation will stop.

## Concepts
- Multithreading.
- Mutexes for resource protection.
- Avoiding deadlock and starvation.

## Notes
- Proper synchronization of threads is crucial to solve this problem effectively.
- Be mindful of potential race conditions and deadlocks.

