This seems very straightforward too, I doubt there are optimizations since we have to check probability everytime.

Okay turns out that was wrong, I tried generating a simulation and tried everything possible to optimise it to the max in the time limit including multithreading etc, but it's not yet quite in the 10^-6 accuracy they wanted even with caching etc. It was close but simulating all possibilities seems to not work. If it was in 10^-3 or 10^-4 we can go with this.
So I move onto alternative solutions, I researched a bit online about infinite possibility movement in a maze and came across something called as the Markov Decision Process (https://www.geeksforgeeks.org/markov-decision-process/)

This seems very similar with slight modifications, gotta take care of mines, walls and tunnels.
So I implement it and see how it goes. 
We create a state, probability, and transition matrix for each state.
And then we yoink the code and theory which I found for Markov Chain Convergence in some stanford lecture. It shows how we can do approximations for this since we need to do infinite matrix multiplication. There is something in scipy.linalg as well but since it isn't allowed I'll pick this up.

