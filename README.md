# firstOGLUI
8/26/22 CAS Reflection 4 - firstOGLUI

<h1> Initial Note / Disclaimer </h1>
  <p>This application is very minimal right now, but the code took a long time to develop and I just wanted to make a small exmple to show my progress and how it works </p>

<h1> How to download and execute </h1>
  <p> <b> Note about source code: </b> the dlls are not included in the /firstUI folder due to them being architecture dependant. If you want to run the source code yourself, drag the respective dlls from the /standalone/dlls folder into the /firstUI folder where main.cpp resides </p>
  <p> I made this project with Visual Studio, using C++20 with Microsoft's MSVC compiler. Other compilers should work but for simplicity I recommend using Visual Studio as well. I use Visual Studio 2022 but older versions will work as well </p>
  <p> To download, install git if not already installed and type the following command in any terminal: </p>

```
git clone https://github.com/dec-lied/firstOGLUI.git
``` 

<p> to download the repository. The main code is in the /firstUI folder with the includes being in the include/ directory. </p>
<p> You can do either of the following to run the program: </p>
<ol>
  <li> Build it from the source yourself by opening oglUI.sln and in Visual Studio, selecting Release as well as x64 or x86 according to your pc architecture then click build. If you decide to do this, be sure to <b> <ins> place the executable oglUI.exe into the /standalone folder and pull the architecture respective dlls from the dll folders into the /standalone folder together with oglUI.exe. </ins> </b> </li>
  <li> Download the release according to your comuter's architecture from the Releases tab on 
  <a href="https://github.com/dec-lied/firstOGLUI/releases"> this page </a>. </li>
</ol>

<h1> How to use </h1>
  <p> It is a standard UI so it will be very intuitive, but hovering over a button with the mouse will change its color so you know you can click it. Then, clicking it will do some action that should be described to you on the page. </p>
