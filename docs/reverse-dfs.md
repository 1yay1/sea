Reverse Depth-First Search
===
When a depth-first search can be completed in a given time *t* and a space consumption *s*, we can also complete a reverse DFS in the same time and working space.

This space-efficient reverse DFS
- splits the runtime of a DFS into log(n) intervals
- steps through the intervals in reverse and simulates each interval from start to finish
- returns the occurring user calls through an iterator:
    - *init()*: initializes the reverse DFS (runs a forward DFS in O(n log(log(n))) bits and make the intervals)
    - *more()*: returns true if there are more user calls
    - *next()*: gets the next user call from the simulated interval (some parts are mixed in "on the fly" where possible)

## Efficiency
- Time: O(n+m)
- Space: O(n log(log(n))) bits

## Example
```cpp
#include "sealib/iterator/reversedfs.h"
#include "sealib/graph/graphcreator.h"

int main() {
    Sealib::DirectedGraph g = Sealib::GraphCreator::kOutdegree(1024, 16);

    Sealib::ReverseDFS d(g);
    d.init();
    while (d.more()) {
        UserCall c=d.next();
        // do something with the user call
    }
}
```