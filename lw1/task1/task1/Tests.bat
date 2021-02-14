SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% test-data\empty.txt "%TEMP%\fox.txt" dog cat || goto err
fc "%TEMP%\fox.txt" test-data\empty.txt || goto err

%MyProgram% test-data\fox.txt "%TEMP%\fox.txt" dog cat || goto err
fc "%TEMP%\fox.txt" test-data\fox-replaced-dog-with-cat.txt || goto err

%MyProgram% test-data\fox.txt "%TEMP%\fox.txt" fox || goto err
fc "%TEMP%\fox.txt" test-data\fox.txt || goto err

%MyProgram% test-data\multiline-fox.txt "%TEMP%\fox.txt" dog cat || goto err
fc "%TEMP%\fox.txt" test-data\multiline-fox-replaced-dog-with-cat.txt || goto err

%MyProgram% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

%MyProgram% multiline.txt %MyProgram% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

REM Успешно
exit /B 0

REM Тест провален
:err
echo Test failed
exit /B 1