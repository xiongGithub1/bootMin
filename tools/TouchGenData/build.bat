@echo off
set CSC=C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe
if not exist "%CSC%" (
    echo ERROR: csc.exe not found at %CSC%
    exit /b 1
)

"%CSC%" /nologo /optimize+ /target:winexe /r:System.Windows.Forms.dll /r:System.Drawing.dll /out:TouchGenData.exe TouchGenData.cs
if errorlevel 1 exit /b 1

echo Built: %~dp0TouchGenData.exe
