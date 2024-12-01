# ROS2 Packages

## Build

To build all packages

```bash
colcon build --merge-install
```

To build you some single package

```bash
colcon build --merge-install --packages-up-to package_name
```
or
```bash
colcon build --packages-select package_name
```

## Install
Current installation dir is ```/axior_ws/packages/install```. To run setup do

```bash
. install/setup.bash
```
