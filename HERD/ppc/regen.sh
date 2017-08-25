#!/bin/bash
rm -rf *.dot *.png;
find ../tests/ -type f -iname 'PPC-*.litmus' -exec herd7 -show prop -o . -model ppc.cat $(basename {}) \;;
find . -type f -iname '*.dot' -exec dot -Tpng {} -o {}.png \;;
rm -rf *.dot;
