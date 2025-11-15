#include <bits/stdc++.h>
#include "unts.h"


int main() {
    unts::unique_array<int,10> array;
    array.add(0,1);
    array.add(1,2);
    array.add(2,3);
    array.add(3,4);
    array.for_each();

    return 0 ;
}
