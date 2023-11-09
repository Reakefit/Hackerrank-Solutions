Ramblings:

Okay so the problem is super straightforward if we look at the brute force dfs store distances and use it:
Basically we create the graph tree and store connections and do dfs till we reach max length and then add
But this is going to take forever we need some ways to minimize this.

So looking at this we can see that the preferred path is obviously going to be the longest.
So we can find the longest path (diameter of tree) and nodes involved and then we just take one step to
reach one of these nodes (which ever is longer) and remaining will be this path involved*(steps-1).

First submission failed but increasing recurrsion depth fixed the issue. Best case solution.
Again simple diameter of tree problem, nothing too great about it. O(N+V)