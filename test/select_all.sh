#!/bin/bash

SCRIPT_DIR=$( dirname -- "$0"; )

sqlite3 $SCRIPT_DIR/test.db "SELECT * FROM TEST_TABLE;"
