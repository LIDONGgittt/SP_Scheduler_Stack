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


## Problems
1. If `chrt` coudn't change priority:
    - execute: `sysctl -w kernel.sched_rt_runtime_us=-1`
2. 