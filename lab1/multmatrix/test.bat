@echo off
chcp 65001
set PROGRAM="%~1"

set OUT="%TEMP%\output.txt"

::���� ������������� ������
%PROGRAM% matrix1.txt matrix2.txt > %OUT% || goto err
fc test1_out.txt %OUT% || goto err
echo Test 1 passed


::�������� ������
%PROGRAM% matrix1.txt matrix3.txt > %OUT% || goto err
fc test2_out.txt %OUT% || goto err
echo Test 2 passed


::������ ����
%PROGRAM% matrix1.txt null_matrix.txt > %OUT% && goto err
fc test3_out.txt %OUT% || goto err
echo Test 3 passed


::�������� ������� ���������� ��������� ������
%PROGRAM% > %OUT% && goto err
fc test4_out.txt %OUT% || goto err
echo Test 4 passed


::�������� ������� ���������� ��������� ������
%PROGRAM% matrix1.txt > %OUT% && goto err
fc test4_out.txt %OUT% || goto err
echo Test 5 passed


::�������� ������
%PROGRAM% matrix3.txt matrix4.txt > %OUT% || goto err
fc test6_out.txt %OUT% || goto err
echo Test 6 passed


::�������� ������������ �����
%PROGRAM% matrix3.txt symbols.txt > %OUT%  && goto err
fc test7_out.txt %OUT% || goto err
echo Test 7 passed


echo All tests passed
exit /B 0

:err 
echo Program testing failed
exit /B 1
