call %QTDIR%/bin/qtenv2.bat

cd /D "%~dp0"

echo %cd%

rmdir /S /Q qfi_example

mkdir qfi_example
copy /y bin\*.exe qfi_example
copy LICENSE qfi_example

call "%QTDIR%\bin\windeployqt.exe" --release qfi_example\qfi_example1.exe

rm qfi_example_0.2_win64.zip
"C:\Program Files\7-Zip\7z.exe" a qfi_example_0.2_win64.zip -r qfi_example\

pause
