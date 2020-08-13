#!/bin/bash
THIS_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
set -e

cd ${THIS_DIR}/../
mkdir -p html
cd html
doxygen ../doxygen/Doxyfile