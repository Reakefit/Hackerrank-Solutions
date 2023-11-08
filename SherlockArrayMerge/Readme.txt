Ramblings:

Lets work our way down as we add each element and see how many possibilities we can create.
For [1, 3, 2, 4]
Let's track the steps to understand the process:

Step 1: '1': Now here [1] is our sherlock array aka M
we keep track of subsequences 1 (consider subsequence to be the vertical part considered in each arrangement)

Step 2: '3': [1, 3] is our M
3 is greater than 1 so it can be added to subsequence 1 or be a new one
therefore possibilities become:

    1               1, 3
    3

Step 3: '2': [1, 3, 2] is our M
When '2' is added it can't be in a subsequence with '3' since it is smaller, it can be added to the rest
or it can create it's own subsequence our possibilities extending from before now become:

    1               1, 2            1           1, 3, 2
    3               3               3, 2
    2
    = not possible because sorted would be 1,2,3

The second and third can be combined as (1,3) + (2) which has 2P1 ways of arranging and fourth array as [1, 3, 2]

Step 4: '4': [1, 3, 2, 4] is our M and extending on previous ideas:
We can only extend the last subsequence which is currently 2 to form (1, 3) + (2, 4) (possible cause 4 > 2)
(The reason we can't extend previous subsequence is that we need [1, 3, 2] are previous M and extending
prior subsequences inserts 4 in middle instead of in the end)
So that gives us (1, 3) + (2, 4) which has 2 ways or arranging
and also 4 creating a new subsequence in all 3, so total 5 ways.

So what do we need to monitor:
1. Length of curr subsequence
2. Max of curr subsequence
3. Length of prev subsequence (we can't insert something like 1     3) that makes no sense does it?
                                                                    2
Inserting into curr subsequence only possibile if element > Max of curr subsequence AND length < prev length
If length of curr subsequence is x, creating the new subsequence has x*number taken to reach previous possibilities ways

So let us define our rules:
1. Can extend the last subsequence if it is the greatest, if we track the last inserted which will obviously be
greatest based on this rule, we can directly compare.
3. Can always create a new subsequence (will always maintain the order)

Now we can have queues to achieve this to keep track of all states and number of ways to achieve that.
And we keep popping till we reach the end and sum up all the ways.


