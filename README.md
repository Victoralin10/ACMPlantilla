# ICPC-Notebook
Notebook for Zoids team at ACM ICPC. Based on https://github.com/INSAlgo/ICPC-Notebook 

# Usage
C++ and Python notebook files are located in the cpp/ and python/ directories, respectively.
To add files and sections to a notebook, add it to a subfolder and add it to the corresponding `contents.txt` file.

`contents.txt` has the following format :
```
[Section name]
subfolder/file.cpp  Description of the file      # Optional end-of-line comment
```
Note that there is a tab between the filename and its description. You shouldn't use tabs anywhere else in this file.

The generator script can add text highlighting for the following file formats : `.h, .c, .cc, .cpp, .java, .py`

Once the `contents.txt` file is ready, the notebook can be generated using 
(warning, it will download a 3GB docker latex image, if you prefer to install latex locally and use that installation change lines 71 and 72 of generator.py)

    `./generator.py [python|cpp]`