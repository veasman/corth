# Corth

**This language is a work in progress**

[Forth](https://en.wikipedia.org/wiki/Forth_(programming_language)) but written in [C++](https://www.cplusplus.com/). The language is stack-based (like forth), meaning you can push numbers to, and pop numbers off the "stack" (similar to [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)), aswell as having basic operations. It's not the *same* as Forth, but it's close enough, right?

## Goals

- [x] Compiled
- [ ] Interpreted
- [x] Stack-based
- [x] [Turing-complete](https://github.com/veasman/corth/blob/master/examples/ifelse.corth)

## Build
```bash
git clone https://github.com/veasman/corth.git
cd corth
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./corth file.corth
```

## Examples

You can check out [examples](https://github.com/veasman/corth/blob/master/examples/) for some small programs written in corth. Otherwise, here is a small example of conditionals in corth
``` c
// If 100 + 20 > 20
if 100 20 + 20 > do
    // Print 9 squared
    9 dup * print
// Corth requires if statements to also have an else
else end
```

## How to contribute

### Issues

Feel free to submit issues and enhancement requests.

### Contributing

Please refer to each project's style and contribution guidelines for submitting patches and additions. In general, I follow the "fork-and-pull" Git workflow.

 1. **Fork** the repo on GitHub
 2. **Clone** the project to your own machine
 3. **Commit** changes to a new branch
 4. **Push** your work back up to your fork
 5. Submit a **Pull request** so that I can review your changes

NOTE: Be sure to merge the latest from "upstream" before making a pull request!

## License

This project uses the [GNU General Public License](https://github.com/veasman/corth/blob/master/LICENSE).
