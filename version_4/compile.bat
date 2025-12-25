@echo off
chcp 65001 > nul
echo 正在编译进出校审核管理系统 (Version 4 - 模块化版本)...
echo.

gcc main.c data_management.c user_auth.c student_operations.c advisor_operations.c application_handling.c -o school_management.exe

if %errorlevel% equ 0 (
    echo 编译成功^! 生成的可执行文件: school_management.exe
    echo.
    echo 运行程序命令: school_management.exe
) else (
    echo 编译失败^! 请检查错误信息。
)

pause
