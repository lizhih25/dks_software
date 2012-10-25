DKS software
============

DKS Demo Software

## Structure

      ├─libs
      │  ├─opencv242
      │  │  ├─bin
      │  │  ├─include
      │  │  └─lib
      │  ├─qt481
      │  │  └─bin
      ├─datacollector
      └─test

## Dependencies

#### Qt 4.8.1 msvc2010 32bit

#### OpenCV 2.4.2 vc10 x86 with support to Qt 4.8.1

## datacollector

### Functions

+ Collect images and videos

### Shortcuts in MainWindow

+ Shortcut 'c': change the config file
+ Shortcut 'd': change the root dir
+ Shortcut '0','1','2': change the camera to 0,1,2
+ Shortcut Enter: take a picture
+ Shortcut Space: take a video

### Command Line Arguments

+ -0                       Uses camera No.0
+ -1                       Uses camera No.1
+ -2                       Uses camera No.2
+     --camera 0           Uses camera No.0
+ -c  --config config.xml  Config File Name
+ -d  --dir saveDir        Dir to Save Images and Videos
+ -l  --log                Displays log window

### Passed Tests

_test.bat_

```{batch}
      set "PATH=..\libs\qt481\bin;..\libs\opencv242\bin;%PATH%"
      set EXENAME=datacollector
      set "EXEDIR=..\%EXENAME%-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____"
      set "EXEFILE=%EXENAME%.exe"
      set "RELEASEEXE=%EXEDIR%\release\%EXEFILE%"
      set "DEBUGEXE=%EXEDIR%\debug\%EXEFILE%"
      
      if not exist %RELEASEEXE% goto NoRelease
      start %RELEASEEXE% --camera 0 --config configtest.xml
      start %RELEASEEXE% -1 --config rootdirtest.xml --dir dirtestsuccess
      start %RELEASEEXE% -0c configtest.xml
      :NoRelease
      
      if not exist %DEBUGEXE% goto NoDebug
      start %DEBUGEXE% --camera 0 --config configtest.xml
      start %DEBUGEXE% -1 --config rootdirtest.xml --dir dirtestsuccess
      start %DEBUGEXE% -0c configtest.xml
      :NoDebug
``````
_configtest.xml_

```
      <?xml version="1.0"?>
      <opencv_storage>
            <saveRootDir>E:/code/dks_software/test/configtestsuccess</saveRootDir>
            <dataSetDir>E:/code/dks_software/test</dataSetDir>
      </opencv_storage>

``````

_rootdirtest.xml_

```
      <?xml version="1.0"?>
      <opencv_storage>
            <saveRootDir>E:/code/dks_software/test/dirtestfail</saveRootDir>
            <dataSetDir>E:/code/dks_software/test</dataSetDir>
      </opencv_storage>
``````
