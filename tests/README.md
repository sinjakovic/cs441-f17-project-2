# CS441/541 Project 4 Test Suite
extra tests include:

test that dont throw errors:

./scheduler -s 1 my_test0.txt
./scheduler -s 2 my_test0.txt
./scheduler -s 3 my_test0.txt
./scheduler -s 4 -q 5 my_test0.txt

./scheduler -s 1 my_test1.txt
./scheduler -s 2 my_test1.txt
./scheduler -s 3 my_test1.txt
./scheduler -s 4 -q 10 my_test1.txt

./scheduler -s 1 my_test2.txt
./scheduler -s 2 my_test2.txt
./scheduler -s 3 my_test2.txt
./scheduler -s 4 -q 3 my_test2.txt

./scheduler -s 1 my_test3.txt
./scheduler -s 2 my_test3.txt
./scheduler -s 3 my_test3.txt
./scheduler -s 4 -q 6 my_test3.txt

./scheduler -s 1 my_test4.txt
./scheduler -s 2 my_test4.txt
./scheduler -s 3 my_test4.txt
./scheduler -s 4 -q 8 my_test4.txt

test for error checking:

./scheduler -s 5 my_test0.txt
./scheduler my_test0.txt