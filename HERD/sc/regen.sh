#!/bin/bash
rm -rf *.dot *.png;
find ../tests/ -type f -iname 'X86-*.litmus' -exec herd7 -show prop -o . -model sc.cat $(basename {}) \;;
find . -type f -iname '*.dot' -exec dot -Tpng {} -o {}.png \;;
rm -rf *.dot;
