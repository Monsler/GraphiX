Example:

```c
#include "graphix/graphix.h"

int main()
{
    GraphixInit();

    GraphixDrawRect(10, 10, 50, 50, 0xFF0000);

    GraphixExitKey('q');

    GraphixMainLoop();

    GraphixEnd();

    return 1;
}

```
