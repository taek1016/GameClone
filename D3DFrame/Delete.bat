rmdir /s /q "ipch"
rmdir /s /q "Debug"
rmdir /s /q "Release"
rmdir /s /q "x64"

rmdir /s /q .\Client\Default\Debug
rmdir /s /q .\Client\Default\Release
rmdir /s /q .\Client\Default\x64

rmdir /s /q .\Engine\Default\Debug
rmdir /s /q .\Engine\Default\Release
rmdir /s /q .\Engine\Default\x64

del /f /q .\Engine\Bin\*.exe
del /f /q .\Engine\Bin\*.dll
del /f /q .\Engine\Bin\*.exp
del /f /q .\Engine\Bin\*.ilk
del /f /q .\Engine\Bin\*.lib
del /f /q .\Engine\Bin\*.pdb
del /f /q .\Engine\Bin\*.iobj
del /f /q .\Engine\Bin\*.ipdb

del /f /q .\Client\Bin\*.exe
del /f /q .\Client\Bin\*.exp
del /f /q .\Client\Bin\*.ilk
del /f /q .\Client\Bin\*.lib
del /f /q .\Client\Bin\*.dll
del /f /q .\Client\Bin\*.iobj
del /f /q .\Client\Bin\*.ipdb
del /f /q .\Client\Bin\*.pdb

rmdir /s /q .\Tool\Default\Debug
rmdir /s /q .\Tool\Default\Release
rmdir /s /q .\Tool\Default\x64

del /f /q .\Tool\Bin\*.*

del /f /q D3DFrame.VC.db