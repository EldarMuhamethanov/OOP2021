@echo off
SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% tests-data/input1.txt "%TEMP%\fill.txt" || goto err
fc "%TEMP%\fill.txt" tests-data/output1.txt || goto err 

%MyProgram% tests-data/input2.txt "%TEMP%\fill.txt" || goto err
fc "%TEMP%\fill.txt" tests-data/output2.txt || goto err 

%MyProgram% tests-data/input3.txt "%TEMP%\fill.txt" || goto err
fc "%TEMP%\fill.txt" tests-data/output3.txt || goto err 

%MyProgram% tests-data/input3.txt
if NOT ERRORLEVEL 1 goto err

%MyProgram% non-existing-file-name.txt "%TEMP%\non-existing-file-name.txt" > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%MyProgram% multiline.txt %MyProgram% > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err


REM Успешно
exit /B 0

REM Тест провален
:err
echo Test failed
exit /B 1