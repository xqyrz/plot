@echo off

.\protoc\bin\protoc.exe --cpp_out=. .\message.proto

if %errorlevel% neq 0 (
    echo Generate failed
    exit /b %errorlevel%
)

echo Generate success