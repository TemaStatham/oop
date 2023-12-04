@echo off
chcp 65001
set PROGRAM="%~1"

set OUTPUT="%TEMP%\output.txt"

::������� ����
%PROGRAM% test1.txt output.txt a b > %OUTPUT% || goto err
fc output.txt test1-output.txt || goto err
echo Test 1 passed

::������ ����
%PROGRAM% test2.txt output.txt a b > %OUTPUT% || goto err
fc output.txt test2-output.txt || goto err
echo Test 2 passed

::::�������� �� ������������ ������
%PROGRAM% test3.txt output.txt a b > %OUTPUT% || goto err
fc output.txt test3-output.txt || goto err
echo Test 3 passed

::�������� �� ����� ������� ������ ������ ������
%PROGRAM% test4.txt output.txt hellohi hello > %OUTPUT% || goto err
fc output.txt test4-output.txt || goto err
echo Test 4 passed

::�������� ������� ����������
%PROGRAM%  > %OUTPUT% || goto err
fc %OUTPUT% test5-output.txt || goto err
echo Test 5 passed

::�������� ������� ������
%PROGRAM%  a a a a > %OUTPUT% || goto err
fc %OUTPUT% test6-output.txt || goto err
echo Test 6 passed

echo All tests passed
exit /B 0

:err 
echo Program test failed
exit /B 1