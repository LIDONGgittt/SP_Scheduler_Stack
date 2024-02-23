# SP metrics Stack
Software stack for experiments of computation-aware scheduling and SP metric

## Dependencies

1. Xavier AGX with [Jetpack 5.1.2](https://developer.nvidia.com/embedded/jetpack-sdk-512) installed. \
   Normally, these are included with Jetpack 5.1.2:
   1. GCC/C++ >= 9.4.0
   2. Cmake >= 3.16.3
   3. Boost
   4. Eigen3
   5. python == 2.7
2. OpenCV == 3.4.1 (manually build locally)
3.  ROS2 Foxy desktop


## Tasks
1. YOLO-DynaSLAM 
    - [https://github.com/bijustin/YOLO-DynaSLAM](https://github.com/bijustin/YOLO-DynaSLAM)
    - Build the target:
      1. Build and install [Pangolin](https://github.com/stevenlovegrove/Pangolin), need the specific version: v0.6 (clone and `git checkout v0.6`)
      2. Follow the readme in the original repo, but with the modified source code in this repo.
    - Execute runnable:
      `./YOLO-DynaSLAM/Examples/RGB-D/rgbd_tum_yolo ./YOLO-DynaSLAM/Vocabulary/ORBvoc.txt ./YOLO-DynaSLAM/Examples/RGB-D/TUM3.yaml ./dataset/rgbd_dataset_freiburg3_walking_xyz/ ./YOLO-DynaSLAM/Examples/RGB-D/associations/fr3_walking_xyz.txt`
    - ROS2 Foxy wrapper: the directory named dynaslam
      - Require a locally built dynaSLAM library (libDynaSLAM): this is linked by hard code path in the CMakeLists.txt, make sure the DynaSLAM is built locally
      - Set ld path to find the shared library: `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/nvidia/workspace/sdcard/SP_Scheduler_Stack/YOLO-DynaSLAM/lib`
      - Usage: refer to dynaslam_demo node
1. RRT
    - RRT wrapper for ROS2 Foxy: the directory named rrt_solver
      - Adapted from [https://github.com/nikhilchandak/Rapidly-Exploring-Random-Trees](https://github.com/nikhilchandak/Rapidly-Exploring-Random-Trees).
    - Required: 
      - C++ 11+ and SFML (Simple and Fast Multimedia Library)
      - Install DFML: `sudo apt-get install libsfml-dev`
    - RRT demo nodes:
      - rrt_demo_withoutGUI: find a path using RRT and exit immediatelly.
      - rrt_demo_withGUI: show the searching process of RRT, will not automaticly exit.



## Problems
1. If `chrt` coudn't change priority:
    - execute: `sysctl -w kernel.sched_rt_runtime_us=-1`
2. 