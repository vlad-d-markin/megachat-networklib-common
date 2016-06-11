MegaChat Network Library
=================

Library used by both MegaChat client and server. Probably it will be a
static library or maybe source code will be simply included in applications.

### Building

To build project you can simply run `./run.sh build`
at the project root.

Or you can build manually
```
mkdir buld
cd build
cmake ..
make
```

### Running tests

To run tests `./run.sh run-tests`

Or launch binary at `BULD-DIR/tests/test-megachat-networklib`