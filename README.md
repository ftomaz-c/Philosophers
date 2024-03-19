# Philosophers

> One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table...

## Overview

1. [Project Description](#project-description)
	- [Setting](#setting)
	- [Actions](#actions)
	- [Eating Requirement](#eating-requirement)
	- [Objective](#objective)
	- [Challenge](#challenge)
2. [Usage](#2-usage)
3. [Features to implement](#3-features-to-implement)
	- [Concurrency](#concurrency)
 	- [Problem Solution](#problem-solution)
4. [External functions](#4-external-functions)
	- [Memory and Output Functions](#memory-and-output-functions)
	- [Time Function](#time-function)
	- [Thread Functions](#thread-functions)
	- [Mutex Functions](#mutex-functions)
	- [Best Practices](#best-practices)
5. [Resources](#5-resources)

## 1. Project Description

#### Setting
Several philosophers are seated around a round table with a bowl of spaghetti at the center. Each philosopher has a fork to their left and right, equaling the number of philosophers.

#### Actions
Philosophers alternate between eating, thinking, and sleeping. They cannot eat, think, or sleep simultaneously.

#### Eating Requirement
To eat, a philosopher must use two forks (the one on their right and the one on their left). After eating, they put the forks back on the table, sleep, then wake up to think.

#### Objective
The goal is to ensure all philosophers can eat without starving to death, noting they can't communicate or know if another is close to death.

#### Challenge
The simulation ends if any philosopher dies from starvation. The task is to develop a strategy preventing any philosopher from dying.

This problem illustrates challenges in concurrency, specifically around resource allocation, to prevent deadlock (where no progress is made because everyone is waiting on each other) and starvation (where a philosopher never gets to eat).

## 2. Usage

````
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
````

- **number_of_philosophers**: The number of philosophers and also the number
of forks.
- **time_to_die** (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the sim-
ulation, they die.
- **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat** (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

example: `./philo 5 800 200 200`

## 3. Features to Implement

**Thread Creation and Management**: Each philosopher is represented as a thread. Efficient creation, execution, and termination of these threads are crucial.

**Mutexes for Resource Management**: Use mutexes to manage forks. Each fork is a shared resource among philosophers (threads), and mutexes ensure that no two philosophers can hold the same fork simultaneously.

**Deadlock Avoidance**: Implement a strategy to prevent deadlocks, ensuring that philosophers don't end up in a state where they're waiting on each other indefinitely.

**Starvation Avoidance**: All philosophers should get a chance to eat, avoiding scenarios where any philosopher starves.

**State Monitoring**: Log state changes (thinking, eating, sleeping, taking forks, and dying) with precise timing to monitor and debug the simulation's behavior.

**Parameters Handling**: There are specific arguments to implement also (number of philosophers, times to eat, sleep, die, and optional times each must eat) and behave accordingly.

**Clean Shutdown**: Ensure the program can terminate cleanly without leaving any resources (e.g., threads or mutexes) hanging.

### Concurrency
- Concurrency in computer science is the concept of running multiple parts of a program, algorithm, or problem simultaneously to make the whole process faster and more efficient. This is particularly beneficial on computers with multiple processors or cores, where tasks can be spread out and executed in parallel.

- Involves decomposing a program, algorithm, or problem into components that can either be executed out of order or in partial order, without affecting the final outcome. This decomposition allows for parallel execution of these components, leveraging multi-processor and multi-core systems to enhance performance.

- Concurrency is not just about doing things faster; it's also about designing programs that can handle multiple tasks at once, making them more responsive and efficient. In the world of software development, mastering concurrency is essential for building high-performance applications that make the most of the underlying hardware.

### Problem Solution

The Chandy/Misra solution (1980s) modernizes the Dining Philosophers Problem by introducing a method that allows any number of philosophers to dine together without a central authority dictating their actions. Unlike the original approach (Dijkstra) where philosophers silently try to eat without coordinating, this solution involves direct communication between philosophers through message passing:

- Decentralized System: Each philosopher operates independently, making the solution scalable to any number of participants and resources.
- Communication for Coordination: Philosophers send and receive requests for forks, coordinating with each other to ensure everyone can eat.
- Dirty and Clean Forks: Forks are labeled as "dirty" or "clean" to manage their use efficiently and prevent deadlock, where no philosopher can eat.
- Avoids Deadlocks and Starvation: By requiring philosophers to request forks and pass them only when not needed, the system ensures all philosophers get a chance to eat, preventing both deadlock and starvation.

This approach acknowledges the practical need for communication in solving complex concurrency issues, making it a robust solution for distributed systems where resources must be shared efficiently among multiple processes.

## 4. External functions

### Memory and Output Functions

`memset` - fills a block of memory with a specified value, typically used for initializing memory.

`printf` - outputs formatted text to stdout, invaluable for debugging and user interaction.

`malloc` - allocates a specified number of bytes in the heap memory.

`free` - deallocates previously allocated memory, preventing memory leaks.

`write` - directly writes data to a file descriptor, useful for low-level I/O operations.

### Time Function

`usleep`: Pauses the calling thread for a given number of microseconds.

````c
int usleep(useconds_t usec);
````

`usec` is the number of microseconds to sleep.

---

`gettimeofday`: Retrieves the current time with microsecond precision..

````c
int gettimeofday(struct timeval *tv, struct timezone *tz);
````

`tv` is a structure to store the current time and `tz` is a timezone structure, usually set to NULL.

### Thread Functions

**pthread_create**: Creates a new thread, starting with execution of the function provided as an argument.

````c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
````

`thread` is the variable that will hold the thread ID, `attr` specifies thread attributes (NULL for default), `start_routine` is the function the thread will start executing, and `arg` is the argument to the start routine.

---

**pthread_detach**: Marks the thread identified by `thread` as detached. When a detached thread terminates, its resources are automatically released back to the system.

````c
int pthread_detach(pthread_t thread);
````

---

**pthread_join**: Waits for the thread specified by `thread` to terminate. If that thread has already terminated, pthread_join returns immediately.

````c
int pthread_join(pthread_t thread, void **retval);
````

`retval` is a pointer to the location where the exit status of the thread will be stored.

### Mutex Functions

**pthread_mutex_init** and **pthread_mutex_destroy**: These functions initialize and destroy a mutex object, respectively. A mutex is used to prevent multiple threads from simultaneously executing critical sections of code that access shared data.

````c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
````

---

**pthread_mutex_lock** and **pthread_mutex_unlock**: These functions lock and unlock a mutex, respectively. pthread_mutex_lock will block if the mutex is already locked by another thread, preventing access to the critical section until it is unlocked.

````c
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
````

### Best Practices

**Threading**: Use pthread_join to ensure all threads have completed before exiting the main program.

**Mutexes**: Always unlock a mutex even if the protected code section encounters an error to prevent deadlocks.

## 5. Resources

Medium
- [Dining Philosophers Problem](https://medium.com/@francescofranco_39234/dining-philosophers-problem-36d0030a4459)

Youtube
- [A simple Guide to "The Dining Philosopher Problem](https://www.youtube.com/watch?v=Dt51GebwNR0&pp=ygUPcGhpbG9zb3BoZXJzIDQy)

Wikipedia
- [Concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science))
- [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
