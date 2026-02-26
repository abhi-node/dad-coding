"""
- Problem: Car Reservations

Reservations
{
int id;
int start;
int end;
}

Objective:
Find minimum amount of cars necessary to take care of reservations
Return all car assignments - which reservations to which car

[[1, 2], [1, 4], [3, 5], [5, 7]]

example output:
car1: [1, 2], [3, 5], [5,7]
car2: [1, 4]

Brute force:
- sort reservations array by leading time - O(nlog(n))
- go through each reservation
- check all available cars end time - if available, then push - if no cars available, then continue - O(n^2)

Priority queue (minheap):
- maintains order of queue in log(n) time
- for tuples, it sorts by first element, then second element.

Optimized:
- map for storing car ids - maps id to list of tuples, which are our intervals (return map)
- {
1: [(1, 2), (3, 5), (5, 7)]
2: [(1, 4)]
}
- We can use a priority queue/min heap to track the interval with the lowest end time (end_time, id)
- loop through the reservations array - O(n)
- for the current reservation, check if the reservation's start time is higher than the top of the queue's end time
- if available:
-   pop top element of queue, and get its id + end time - O(log(n))
-   push the element's id with its new end time (new_end_time, popped_id) - O(log(n))
-   update the map's list with that new interval - map[popped_id].append((new_start, new_end)) - O(1)
-   we are reserving the available car
- if not available:
-   increment current amount of cars (i++) - O(1)
-   create new list in map with the interval map[i] = [(start, end)] - O(1)
-   pqueue.push((end, i)) - O(log(n))
-   reserve a new car

- At the end, we can loop through the map and return the values, or return the map O(n)
- total - O(nlog(n))


"""

import heapq


def solve(res):
    map = {}
    q = []

    i = 0
    res.sort()
    for j in res:
        if i > 0 and j[0] > q[0][0]:
            end, id = heapq.heappop(q)
            heapq.heappush(q, (j[1], id))
            map[id].append((j[0], j[1]))
        else:
            i += 1
            map[i] = [(j[0], j[1])]
            heapq.heappush(q, (j[1], i))

    print(map)


def main():
    res = [(1, 2), (1, 4), (3, 5), (5, 7)]
    solve(res)


main()
