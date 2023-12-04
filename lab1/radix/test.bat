@echo off
chcp 65001
set PROGRAM="%~1"

set OUT="%TEMP%\output.txt"

%PROGRAM% 10 2 10 > %OUT% || goto err
fc test1_out.txt %OUT% || goto err
echo Test 1 passed

%PROGRAM% 10 10 1 > %OUT% || goto err
fc test2_out.txt %OUT% || goto err
echo Test 2 passed

%PROGRAM% 10 16 10 > %OUT% || goto err
fc test3_out.txt %OUT% || goto err
echo Test 3 passed

%PROGRAM% 2 > %OUT% || goto err
fc test4_out.txt %OUT% || goto err
echo Test 4 passed

%PROGRAM% 10 10 > %OUT% || goto err
fc test5_out.txt %OUT% || goto err
echo Test 5 passed

%PROGRAM% > %OUT% || goto err
fc test6_out.txt %OUT% || goto err
echo Test 6 passed

%PROGRAM% 37 38 1 > %OUT% || goto err
fc test7_out.txt %OUT% || goto err
echo Test 7 passed

%PROGRAM% 16 36 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF> %OUT% || goto err
fc test8_out.txt %OUT% || goto err
echo Test 8 passed


echo All tests passed
exit /B 0

:err 
echo Program testing failed
exit /B 1
