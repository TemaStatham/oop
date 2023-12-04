@echo off
chcp 65001
set PROGRAM="%~1"

set OUT="%TEMP%\output.txt"

::проверка входных параметров командной строки
%PROGRAM% > %OUT% && goto err
fc test1_out.txt %OUT% || goto err

%PROGRAM% test1.txt > %OUT% && goto err
fc test1_out.txt %OUT% || goto err

%PROGRAM% test.txt out.txt > %OUT% && goto err
fc test1_sec_out.txt %OUT% || goto err

echo Test 1 passed

::тест
%PROGRAM% test2.txt out1.txt || goto err
fc out1.txt test2_out.txt || goto err

echo Test 2 passed


::выход за границы массива
%PROGRAM% test3.txt out.txt || goto err
fc out.txt test3_out.txt || goto err

echo Test 3 passed


::выход за границы массива 2
%PROGRAM% test4.txt out.txt || goto err
fc test4_out.txt out.txt || goto err

echo Test 4 passed


::выход за решетки
%PROGRAM% test5.txt out.txt || goto err
fc test5_out.txt out.txt || goto err

echo Test 5 passed


echo All tests passed
exit /B 0

:err 
echo Program testing failed
exit /B 1
