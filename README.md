# Philosophers

A C implementation of the classic dining philosophers problem, demonstrating concurrent programming concepts and synchronization mechanisms using threads and mutexes.

## About

The Philosophers project simulates the famous dining philosophers problem where philosophers alternate between thinking and eating. Each philosopher needs two forks to eat, but there are only as many forks as philosophers. The challenge is to prevent deadlock and starvation while ensuring thread safety.

This implementation uses **POSIX threads (pthreads)** and **mutexes** to handle synchronization, showcasing fundamental concepts in concurrent programming and resource management.

## Key Features

- **Multi-threading**: Each philosopher runs in a separate thread
- **Mutex Synchronization**: Prevents race conditions when accessing shared resources (forks)
- **Deadlock Prevention**: Implements strategies to avoid deadlock situations
- **State Management**: Tracks philosopher states (thinking, eating, sleeping, died)
- **Precise Timing**: Microsecond precision for timing operations
- **Resource Cleanup**: Proper thread and mutex cleanup on program termination
- **Death Detection**: Monitors philosophers for death due to starvation

## Usage

### Compilation
```bash
make
```

### Execution
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
```

### Parameters
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in milliseconds after which a philosopher dies if not eating
- `time_to_eat`: Time in milliseconds a philosopher spends eating
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: Optional parameter to stop simulation after each philosopher eats this many times

### Examples
```bash
# Basic simulation with 5 philosophers
./philo 5 800 200 200

# Simulation that stops after each philosopher eats 3 times
./philo 4 410 200 200 3

# Test case for quick death
./philo 1 800 200 200

# Stress test with many philosophers
./philo 200 800 200 200
```

### Output Format
```
[timestamp_ms] philosopher_id is thinking
[timestamp_ms] philosopher_id has taken a fork
[timestamp_ms] philosopher_id is eating
[timestamp_ms] philosopher_id is sleeping
[timestamp_ms] philosopher_id died
```

## Technical Skills Demonstrated

- **Concurrent Programming**: Multi-threaded application design and implementation
- **Synchronization**: Mutex usage for thread-safe resource access
- **Deadlock Prevention**: Implementation of strategies to avoid deadlock scenarios
- **Race Condition Handling**: Proper synchronization to prevent data races
- **Resource Management**: Efficient allocation and cleanup of threads and mutexes
- **Timing Precision**: Microsecond-level timing operations and calculations
- **System Programming**: POSIX threads API and low-level system calls
- **Algorithm Design**: Efficient scheduling and state management algorithms
- **Memory Management**: Proper allocation and deallocation in multi-threaded environment
- **Problem Solving**: Classic computer science problem implementation
