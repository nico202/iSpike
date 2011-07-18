:: Set SpikeStream root directory
SET SpikeStreamRoot=D:\Home\Programs\spikestream\trunk
::SET SpikeStreamRoot=C:\Users\daogamez\Home\Programs\spikestream\trunk

:: Set location of iSpike library
::SET iSpikeLibrary=lib
SET iSpikeLibraryDirectory=D:\Home\Programs\iSpike\src

:: Copy library to external library location
copy %iSpikeLibraryDirectory%\libiSpike.dll %SpikeStreamRoot%\extlib\ispike\lib\libiSpike.dll /Y

:: Copy libray to bin location
copy %iSpikeLibraryDirectory%\libiSpike.dll  %SpikeStreamRoot%\bin\libiSpike.dll /Y

:: Delete include files from external library
rmdir  %SpikeStreamRoot%\extlib\ispike\include\iSpike /s /q

:: Copy include files to external library
xcopy include\*.hpp  %SpikeStreamRoot%\extlib\ispike\include /s
