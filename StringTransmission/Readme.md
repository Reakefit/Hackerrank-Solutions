Okay so brute force does not work where we just find all the possible patterns upto k changes and count them.
We need dp over here, lru cache does not work. Can't build up from previous step easily still takes too much time.
We need to dive deeper into combinations and periodicity.

First if a string is periodic, it's periodicity has to be a factor of it obviously. We can leverage this.
We also need a way to avoid over-counting, for example
Consider the case where we flip bits in segments of size 2 and 3. If we flip bits in segments of size 2, we might get a new binary string. Then, if we flip bits in segments of size 3 in the original string, we might get the same binary string that we got by flipping bits in segments of size 2. 
Here we are counting the string twice.

So to avoid this let's go to number theory. We can implement mobius function based on if it has even or odd number of prime factors or is a square of prime number.
So we can later subtract overcounts

*LEARNING POINT* TIL that in C++ -1 % MOD is not MOD - 1 unlike in python, spent an embarassing amount of time trying to figure out why my code isn't passing.
