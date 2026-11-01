@echo off
setlocal
cd /d "%~dp0"
gcc -std=c11 -Wall -Wextra -Wpedantic main_qa.c -o nhiemvu.exe
if errorlevel 1 (
    echo Bien dich that bai. Kiem tra GCC va README.
    pause
    exit /b 1
)
nhiemvu.exe < docs\demo-input.txt
 echo.
 echo Demo da chay xong. Co the cuon len de chup bang va thong ke.
 pause
