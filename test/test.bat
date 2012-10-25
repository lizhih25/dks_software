set "PATH=..\libs\qt481\bin;..\libs\opencv242\bin;%PATH%"
set EXENAME=datacollector
set "EXEDIR=..\%EXENAME%-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____"
set "EXEFILE=%EXENAME%.exe"
set "RELEASEEXE=%EXEDIR%\release\%EXEFILE%"
set "DEBUGEXE=%EXEDIR%\debug\%EXEFILE%"

if not exist %RELEASEEXE% goto NoRelease
      start %RELEASEEXE% -0c configtest.xml
:NoRelease

if not exist %DEBUGEXE% goto NoDebug
start %DEBUGEXE%
:NoDebug

