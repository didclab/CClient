#!/bin/bash
THIS_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
set -e

cd ${THIS_DIR}/../pages
doxygen ../docs/Doxyfile