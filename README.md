# Corth

**This language is a work in progress**

[Forth](https://en.wikipedia.org/wiki/Forth_(programming_language)) but written in [C++](https://www.cplusplus.com/). The language is stack-based (like forth), meaning you can push numbers to, and pop numbers off the "stack" ([Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)), aswell as having basic operations. I'm not really sure Forth works the same way I'm making this language, but it's close enough right?

## Goals

- [ ] Compiled
- [ ] Interpreted
- [ ] Stack-based
- [ ] [Turing-complete](https://en.wikipedia.org/wiki/Turing_completeness)

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
./corth myfile.corth
```

Check out "examples" for some pre-written examples using corth
