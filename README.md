
<h1 align="center">Femto Shell Extension</h1>

<div align="center">

[![GitHub issues](https://img.shields.io/github/issues/ehababdalnaby/Femto-Unix-Utilities-pwd-echo-cp-mv)](https://github.com/ehababdalnaby/Femto-Unix-Utilities-pwd-echo-cp-mv/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/kylelobo/The-Documentation-Compendium.svg)](https://github.com/ehababdalnaby/Femto-Unix-Utilities-pwd-echo-cp-mv/pulls)
[![GitHub license](https://img.shields.io/github/license/ehababdalnaby/Femto-Unix-Utilities-pwd-echo-cp-mv)](https://github.com/ehababdalnaby/Femto-Unix-Utilities-pwd-echo-cp-mv)

</div>

---

## 📝 Table of Contents

- [1. Prerequists](#Prerequists)
- [2. Compilation command](#Compilation_command)
- [3. Main features](#Main_features)
  - [1. Executing external commands](#Executing_external_commands)
  - [2. Set local variables](#Set_local_variables)
  - [3. export local to env](#export)
- [4. Extra feature](#extra)
  - [1. cd command](#cd)
  - [2. IO redirection](#redirection)
  - [3. Pipe feature](#pipe)
  - [4. edit input line](#)
  - [5. Previos command using up and down keys](#)
  - [6. Support commands from assignment #2](#old)

---

## 1. Prerequists <a name = "Prerequists"></a>

install readline library.

- ### ⛏️ Command

    ```$ sudo apt-get install lib32readline8 lib32readline-dev```

## 2. Compilation command <a name = "Compilation_command"></a>

- ### ⛏️ compilation command

    ```$ gcc -o shell prompt/prompt.c tokenizer/tokenizer.c main.c variables/vars.c executer/executer.c builtincmd/builtinCMD.c -lreadline```

- ### 💻 output

    >![compilation output](./pic/gcc.png)

---

## 3. Main features <a name = "Main_features"></a>

- ### 1. Executing external commands <a name = "Executing_external_commands"></a>

- #### Examples

- #### 💻 ls -l

    >![ls ouput](./pic/ls.png)

- #### 💻 ps -l

    >![ps ouput](./pic/ps.png)

- ### 2. Set local variables <a name = "Set_local_variables"></a>

- ####  Examples

- #### 💻 Local variables

    >![ls ouput](./pic/set.png)

- ### 3. export local to env <a name = "export"></a>

- ####  Examples

- #### 💻 export Local variables

    >![ls ouput](./pic/export1.png)

    >![ls ouput](./pic/export2.png)

---

## 4. Extra feature <a name = "extra"></a>

- #### 1. cd command <a name = "cd"></a>

- ####  Examples

- #### 💻 cd command output

    >![ls ouput](./pic/cd.png)

- ### 2. IO redirection <a name = "redirection"></a>

- ####  Examples

- #### 💻 Output redirection

    >![Ouput redirection](./pic/r1.png)

- #### 💻 Error redirection

    >![Error redirection](./pic/r2.png)

- #### 💻 Output and error redirection

    >![Output and error redirection](./pic/r3.png)

- #### 💻 Input redirection

    >![Input redirection](./pic/r4.png)

- ### 3. Pipe feature <a name = "pipe"></a>

- ####  Examples

- #### 💻 Output redirection

    >![Ouput redirection](./pic/pipe1.png)

    >![Ouput redirection](./pic/pipe2.png)

- ### 6. Support commands from [assignment #2](https://github.com/ehababdalnaby/Femto-Unix-Utilities-pwd-echo-cp-mv)<a name = "old"></a>

- #### 💻 Output

        >![old commands](./pic/old.png)
