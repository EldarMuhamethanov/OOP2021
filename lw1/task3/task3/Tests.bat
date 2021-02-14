@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% tests-data/input1.txt > "%TEMP%\invert.txt" || goto err
fc "%TEMP%\invert.txt" tests-data/output1.txt || goto err 

%MyProgram% tests-data/input2.txt %MyProgram% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%MyProgram% tests-data/input3.txt %MyProgram% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

REM �������
exit /B 0

REM ���� ��������
:err
echo Test failed
exit /B 1