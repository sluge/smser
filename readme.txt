
This is open-source project smser, that allow to user send sms messages by Igor Sobinov

Requements:
   It is needed Qt4 for work, so, install in first


Getting source   

   1)Install git for you operating system
   2)type command "git clone git://github.com/sluge/smser.git"
   
Build instructions:
   Linux:
   1) Make sure you have Qt4 on your system. To check it, type 
      in termital windiw "rpm -qa | grep qt4"

   Go to smser directory and type "qmake;make" without "

   Windows:
   1) Download Qt SDK for windows from qt.nokia.com
   2) Install it, seleted all options
   3)Add to PATH enviroment variable "C:\Qt\2010.05\mingw\bin;C:\Qt\2010.05\qt\bin" if you 
     install qt to "C:\Qt\2010.05"
   3) Open console window (cmd.exe) and go to qt install dir (default is "C:\Qt\2010.05\qt")
     by typing "cd C:\Qt\2010.05\qt"
   4) Type configure command "-static -release -no-exceptions -opensource -fast
      -no-accessibility -no-stl -no-opengl -no-dsp -no-vcproj -no-phonon -no-multimedia 
      -no-audio-backend -no-webkit -no-script -no-qt3support -no-declarative
      -nomake examples -nomake demos"
      After it type "mingw32-make sub-src" 
    
   
Run:
  on linux:
  Go to "smser/src" and type "./smser" without "
  
