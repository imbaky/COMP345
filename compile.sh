#!/bin/bash

for d in */ ; do
    ( cd $d && make )
done
