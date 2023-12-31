# CppND-System-Monitor
This project known as System Monitor displays the information of system resources that includes CPU usage , RAM , Uptime , Command , PID information . The project is basically like a htop that displays system utilization.



![System Monitor](images/monitor.png)



## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.


If you are not using the Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`


![System_Monitor](https://github.com/LogicalDepth/CppND-System-Monitor/assets/92685394/dabfe4fa-7624-4177-b7e0-33e9271ed799)
