@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% 5 2 1234 > "%TEMP%\radix.txt" || goto err
fc "%TEMP%\radix.txt" tests-data/output1.txt || goto err 

%MyProgram% 8 20 7654321 > "%TEMP%\radix.txt" || goto err
fc "%TEMP%\radix.txt" tests-data/output2.txt || goto err

%MyProgram% 20 8 ABCDEF > "%TEMP%\radix.txt" || goto err
fc "%TEMP%\radix.txt" tests-data/output3.txt || goto err

%MyProgram% 20 8 -ABCDEF > "%TEMP%\radix.txt" || goto err
fc "%TEMP%\radix.txt" tests-data/output4.txt || goto err

%MyProgram% 20 8 0 > "%TEMP%\radix.txt" || goto err
fc "%TEMP%\radix.txt" tests-data/output5.txt || goto err

%MyProgram% 5 8 12345 %MyProgram% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%MyProgram% 5 8 "" %MyProgram% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%MyProgram% 1 8 0 %MyProgram% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%MyProgram% 4 37 12345 %MyProgram% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err


REM �������
exit /B 0

REM ���� ��������
:err
echo Test failed
exit /B 1