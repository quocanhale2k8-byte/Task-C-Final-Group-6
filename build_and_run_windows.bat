@echo off
setlocal
cd /d "%~dp0"
where gcc >nul 2>nul
if errorlevel 1 (
    echo Khong tim thay GCC. Hay them thu muc bin cua MinGW vao PATH.
    pause
    exit /b 1
)
gcc -std=c11 -Wall -Wextra -Wpedantic main_qa.c -o nhiemvu.exe
if errorlevel 1 (
    echo Bien dich that bai. Xem thong bao loi phia tren.
    pause
    exit /b 1
)
nhiemvu.exe
pause
