# Isaiah Stapleton

# 1. pthreads API

## The purpose of this program is to output a string of a length specified by the user, created by a number of threads also specified by the user.

## This program accepts two parameters: the first one is the amount of threads to start, the second is the desired length of the final string.

## Navigate to the directory where the program is located on your host machine. Type "make hw6" in order to compile the program and make the necessary executable. Next type ".\hw6" followed by two parameters for amount of threads to start and final string length.

# 2. Locking

## C. The final count in each case should be 30. For each of the programs: If this is not true explain why it isn't correct, If it is true explain why it is correct

### flag.s: The final count was 26. The final count is not correct because the critical section is not guarded well, this leads to the count sometimes being updated but not properly stored which messes up the count.

### test-and-set.s: The final count was 30. The final count is correct because it implements a mutex which guards the critical section well enough that only one thread can increment and store count at a time, another thread will not try to increment count until another thread has finished incrementing and storing count.

### yield.s: The final count was 30. The final count is correct because it also implements a mutex which guards the critical section well enough that only one thread can increment and store count at a time. 

## D. What is the total number of instructions executed for each program. Why do you think it varies as much as it does?

### flag.s: Total # of executions is 405. This has the least amount of executions because of the lack of locks/guards in place to properly make the program atomic.

### test-and-set.s: Total # of executions is 597. This has the highest amount of executions because of the sufficient locks/guards in place which causes the threads to execute more instructions while waiting. 

### yield.s: Total # of executions is 561. Like test-and-set.s,this has a high amount of executions because of the sufficient locks/guards in place which causes the threads to execute more instructions while waiting. However, yield uses slightly less executions than test-and-set.s because waiting threads pass instructions to other threads, decreasing the amount of total exeuctions needed.

## E. Run the programs again varying the -I parameter. For each program explain: What happens to the count value? Does the number of instructions executed change?

### flag.s: The count value changes when the -I parameter is varied. For some -I values (27, 30, 31, ...), the count value ends at 30, due to there being no chance of "bad" interrupts that cause the count value not to be properly stored. The number of instructions usually trended towards increasing the higher -I value used, however there would sometimes be signifcant drops in number of executions which would then generally trend towards increasing again until there was another drop.

### test-and-set.s: The count value stays the same, 30. Similar to flag, the amount of instructions would generally trend upwards with -I, however there would sometimes be a drop in number of instructions. 

### yield.s: The count value stays the same, 30. The amount of instructions executed change seemingly without a pattern. Some values of -I the amount of instructions increases, and for some values it decreases.