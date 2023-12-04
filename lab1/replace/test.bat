@echo off
chcp 65001
set PROGRAM="%~1"

set OUTPUT="%TEMP%\output.txt"

::обычный тест
%PROGRAM% test1.txt output.txt a b > %OUTPUT% || goto err
fc output.txt test1-output.txt || goto err
echo Test 1 passed

::пустой файл
%PROGRAM% test2.txt output.txt a b > %OUTPUT% || goto err
fc output.txt test2-output.txt || goto err
echo Test 2 passed

::::проверка на переполнение строки
%PROGRAM% test3.txt output.txt a b > %OUTPUT% || goto err
fc output.txt test3-output.txt || goto err
echo Test 3 passed

::проверка на поиск искомой строки внутри другой
%PROGRAM% test4.txt output.txt hellohi hello > %OUTPUT% || goto err
fc output.txt test4-output.txt || goto err
echo Test 4 passed

::проверка наличия аргументов
%PROGRAM%  > %OUTPUT% || goto err
fc %OUTPUT% test5-output.txt || goto err
echo Test 5 passed

::проверка наличия файлов
%PROGRAM%  a a a a > %OUTPUT% || goto err
fc %OUTPUT% test6-output.txt || goto err
echo Test 6 passed

echo All tests passed
exit /B 0

:err 
echo Program test failed
exit /B 1