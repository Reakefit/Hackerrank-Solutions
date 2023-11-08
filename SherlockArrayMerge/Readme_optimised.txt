So I'm assuming it fails for large input sizes.

One optimisation I can think of is using dicts to condense ones that have first 3 cols similar and just add the ways
Because the output number won't need to differentiate between:
1   2
3
and
1
3   2
Both are same to it.

And on submission we get all except one case :D let's work on it once done with the rest!
From first glance to get the remaining one as well I assume the best case scenario would be avoid queues
and use ordereddicts. would remove the need for condensing in itself but overall time complexity wise this seems to be the best.

Initial time complexity = O(3^n) assuming worst case it adds 3 to queue
now time complexity = complicated but seems like O(n^2*k)? (Needs to be checked)
