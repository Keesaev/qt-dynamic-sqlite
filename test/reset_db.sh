#!/bin/bash

SCRIPT_DIR=$( dirname -- "$0"; )

#rm $SCRIPT_DIR/test.db
sqlite3 $SCRIPT_DIR/test.db "CREATE TABLE TEST_TABLE (ID INT NOT NULL, NAME TEXT NOT NULL, CODE INT NOT NULL);"

insert(){
    sqlite3 $SCRIPT_DIR/test.db "INSERT INTO TEST_TABLE (ID, NAME, CODE) VALUES ($1, 'NAME$1', $1);"
}

for ROW in {1..60000}
do
    insert "$ROW"
done

echo Done
