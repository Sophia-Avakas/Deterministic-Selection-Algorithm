# Deterministic Selection Algorithm
#	Theoretical Analysis: DSelect with groups of 7 would yield a linear-time algorithm
<br> (1) Dividing the data into groups of seven, We need T(n/7) to find the median of the n/7 medians, by running Quickselect on them.
<br> (2) At least half of the n/7 blocks having two elements (n/7 * 1/2 * 4) are discarded at the interation, therefore the time for the actual Quickselect recursion is T(5n/7) in the worst case.
<br> (3) For the partitioning work to create the two sides, each of which the Quickselect will recurse, we need O(n) time.
So we have the following recurrence 
<br>
<br>T(n)≤T(n/7)+T(5n/7)+cn
<br>In this case, n/7 + 5n/7 = 6n/7, 6/7 < 1, so it can yield a linear-time algorithm.
