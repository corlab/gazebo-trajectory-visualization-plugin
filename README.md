# gazebo-trajectory-visualization-plugin
Gazebo plugin for visualizing trajectories. Communication is supported by the ignition transport.

![endeff_viz](https://cloud.githubusercontent.com/assets/7841720/21016520/1ebdb968-bd66-11e6-9c1d-e34bb7813403.png)

## Usage

1. Do in each terminal (i.e. for deployer and gzclient)
```bash
# export orocos service component
export RTT_COMPONENT_PATH=<...>/gazebo-trajectory-visualization-plugin/build/orocos:$RTT_COMPONENT_PATH

# export gazebo gui plugin
export GAZEBO_PLUGIN_PATH=<...>/gazebo-trajectory-visualization-plugin/build:$GAZEBO_PLUGIN_PATH
```
2. Deployer
```bash
import("trajectoryService")
loadService("this","TrajectoryService")
```
3. GzClient
```bash
gzclient -g libtrajectory_wp.so
```
4. Use the TrajectoryService in the Deployer
```bash
Deployer [S]> TrajectoryService.newTrajectoryLink("kuka", "baseLink") 

# For general help do:
Deployer [S]> help TrajectoryService. <TAB>
TrajectoryService.activateLifecycle         TrajectoryService.clearTrajectoryModel      TrajectoryService.newCustomTrajectory       TrajectoryService.resume
TrajectoryService.activateLifecycleLink     TrajectoryService.deactivateLifecycle       TrajectoryService.newTrajectory             TrajectoryService.resumeTrajectory
TrajectoryService.activateLifecycleModel    TrajectoryService.deactivateLifecycleLink   TrajectoryService.newTrajectoryLink         TrajectoryService.resumeTrajectoryLink
TrajectoryService.addPoint                  TrajectoryService.deactivateLifecycleModel  TrajectoryService.newTrajectoryModel        TrajectoryService.resumeTrajectoryModel
TrajectoryService.addSquare                 TrajectoryService.delAll                    TrajectoryService.pause                     TrajectoryService.setLifecycle
TrajectoryService.clear                     TrajectoryService.delTrajectory             TrajectoryService.pauseTrajectory           TrajectoryService.setLifecycleLink
TrajectoryService.clearTrajectory           TrajectoryService.delTrajectoryLink         TrajectoryService.pauseTrajectoryLink       TrajectoryService.setLifecycleModel
TrajectoryService.clearTrajectoryLink       TrajectoryService.delTrajectoryModel        TrajectoryService.pauseTrajectoryModel 

# For specific help do:
Deployer [S]> help TrajectoryService.newTrajectoryLink

 newTrajectoryLink( string model, string link ) : void
   Add tajectory to link of specific model.
   model : Name of the model
   link : Name of the link

```
