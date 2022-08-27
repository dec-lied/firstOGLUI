# firstOGLUI
8/26/22 CAS Reflection 4 - firstOGLUI

<h1> Initial Note / Disclaimer </h1>
  <p>This application is very minimal right now, the code took a long time to develop and I just wanted to make a minimal example UI to show my progress and how it works </p>
  <p> <del> IMPORTANT: For some reason this application, in my testing, uses a LOT of GPU and and more CPU than anticipated. It could be solely due to freetype and the way I handle it, or I could have some strange GPU memory leak. It only uses 23MB of RAM so I'm not entirely sure, but I am going to look into it </del> </p>
   <p> This is fixed. I had vsync off so it was going full throttle on calculations. It now sits at a comfy 1.3% CPU and ~3% GPU. </p>

<h1> How to download and execute </h1>
  <p> <b> Note about source code: </b> the dlls are not included in the /firstUI folder due to them being architecture dependant. Thus, if you want to run the source    code yourself, drag the respective dlls from the /standalone folder into the /firstUI folder where main.cpp resides </p>
  <p> I made this project with Visual Studio, using C++20 with Microsoft's MSVC compiler. Other compilers should work but for simplicity I recommend using Visual Studio as well. I use Visual Studio 2022 but older versions will work as well </p>
  <p> To download, install git if not already installed and type the following command in any terminal: </p>

```
git clone https://github.com/dec-lied/firstOGLUI.git
``` 

<p> to download the repository. The main code is in the /firstUI folder with the includes being in the include/ directory. You can do either of the following to run the program: </p>
<ol>
  <li> Build it from the source yourself by opening oglUI.sln and in Visual Studio, selecting Release as well as x64 or x86 according to your pc architecture then click build. If you decide to do this, be sure to <b> <ins> place the executable oglUI.exe into the /standalone folder and pull the architecture respective dlls from the dll folders for irrKlang and freetype into the /standalone folder together with golf.exe. </ins> </b> </li>
  <li> Download the release according to your comuter's architecture from the Releases tab on 
  <a href="https://github.com/dec-lied/firstOGLUI/releases"> this page </a>. </li>
</ol>

<h1> How to use </h1>
  <p> It is a standard UI so it will be very intuitive, but hovering over a button with the mouse will change its color so you know you can click it. Then, clicking it will do some action that should be described to you on the page. </p>
