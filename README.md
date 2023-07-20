# Escape the ANSI Escape Code hellhole

This project aims to provide small, easily mantainable "libraries" allowing developers to add some flair to their CLI apps through ANSI Escape Codes (AEC) without the need to actually manage those codes.

## Languages
### Supported

  * sh &mdash; command language:
    * zsh
  * Python 3

### To be added (wishlist)

  * Bash
  * C
  * C++
  * C#
  * Delphi (Object Pascal)
  * Java
  * Kotlin
  * OCaml

## The codes

In [AEC.md](AEC.md).


## Examples

### zsh

```sh
echo "$(font bold fg_red)Fatality!$(font reset)"
```

To be used, it is recommended to place [`escape.zsh`](sh/zsh/escape.zsh) in a folder like `~/.zshrc.d` and add the following to `.zshrc`:

```sh
source ~/.zshrc.d/escape.zsh
```

*Escape* is used in the [*zshrc* project](https://github.com/ibnunes/zshrc), being directly provided by it. It can be out-of-date, however, since the two projects are independent and thus have different workflows.


### Python 3

```python
from Ansi import escape as font

print( f"{font('bold', 'fg_red')}Fatality!{font('reset')}" )
```


## License

The software is provided without warranty and as is under the [GNU General Public License version 2](LICENSE.md).


## Contribute

**Notice!** This section will be expanded as needed.

These are the current guidelines for contribution:

  1. Contributions shall be provided via forks.
  2. All [AEC descriptors](AEC.md) must be the same across supported languages as long as it is feasible or possible.
  3. Each supported language must have at least one dedicated branch.
  4. The branch `dev` is to have the current status of all supported languages.
  5. Changes to be merged to `main` are to be done exclusively through Pull Requests.


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
