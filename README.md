# Escape the ANSI Escape Code hellhole


## Examples

### C

```c
#define __FONT_AS_ANSI_ESCAPE__
#include "escape.h"
#include <stdio.h>

int main(void) {
    printf("%s%s%s\n",
        font(BOLD, FG_RED),
        "Fatality!",
        nofont
    );
    return 0;
}
```
