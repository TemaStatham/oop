@echo off
set PROGRAM="%~1"

set OUT="%TEMP%\output.txt"

::проверка входных параметров командной строки
%PROGRAM% > %OUT% && goto err
fc test1_out.txt %OUT% || goto err

%PROGRAM% crypt > %OUT% && goto err
fc test1_out.txt %OUT% || goto err

%PROGRAM% crypt test1.txt > %OUT% && goto err
fc test1_out.txt %OUT% || goto err

%PROGRAM% crypt test1.txt test2.txt > %OUT% && goto err
fc test1_out.txt %OUT% || goto err

echo Test 1 passed

::проверка валидности ключа 
%PROGRAM% crypt test.txt output.txt a > %OUT% && goto err
fc test2_out.txt %OUT% || goto err

%PROGRAM% crypt test.txt output.txt -1 > %OUT% && goto err
fc test2_out.txt %OUT% || goto err

%PROGRAM% crypt test.txt output.txt 256 > %OUT% && goto err
fc test2_out_sec.txt %OUT% || goto err

echo Test 2 passed

::проверка crypt
%PROGRAM% crypt test.txt test3_out.txt 1 > %OUT% || goto err
fc test3_out.txt test_out.txt || goto err

echo Test 3 passed

::проверка decrypt
%PROGRAM% decrypt test_out.txt test4_out.txt 1 > %OUT% || goto err
fc test.txt test4_out.txt || goto err

echo Test 4 passed

echo All tests passed
exit /B 0

:err 
echo Program testing failed
exit /B 1
