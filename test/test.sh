#!/bin/bash
make test/test
if ./test/test; then
  echo "Tests passed!"
fi
