# gazebo-trajectory-visualization-plugin
Gazebo plugin for visualizing trajectories. Communication is supported by the ignition transport.

![endeff_viz](https://cloud.githubusercontent.com/assets/7841720/21016520/1ebdb968-bd66-11e6-9c1d-e34bb7813403.png)

## Usage

```bash
# export orocos service component
export RTT_COMPONENT_PATH=<...>/gazebo-trajectory-visualization-plugin/build/orocos:$RTT_COMPONENT_PATH

# export gazebo gui plugin
export GAZEBO_PLUGIN_PATH=<...>/gazebo-trajectory-visualization-plugin/build:$GAZEBO_PLUGIN_PATH
```
