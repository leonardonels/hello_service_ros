


# Hello Service ROS

A ROS2 service node that publishes a heartbeat message to indicate the ORIN device is online.

## Overview

This node publishes a `std_msgs/Bool` message at a configurable rate when enabled. It uses a wall timer to ensure consistent real-time publishing regardless of simulation state, making it suitable for hardware communication.

## Configuration

The node can be configured via the `config/config.yaml` file:

```yaml
hello_service_ros_node:
  ros__parameters:
    orin_on_topic: "/orin/on"    # Topic name to publish on
    orin_on: true                 # Enable/disable publishing (true/false)
    topic_hz: 10.0                # Publishing frequency in Hz
```

**Parameters:**
- `orin_on_topic`: The topic name where the Bool message will be published (default: `/orin/on`)
- `orin_on`: Enable (`true`) or disable (`false`) message publishing (default: `false`)
- `topic_hz`: Publishing rate in Hz (default: `10.0`)

**Note:** The node name in the config file (`hello_service_ros_node`) must match the node name specified in the launch file.

## Building

```bash
cd ~/ros2_ws
colcon build --packages-select hello_service_ros
source install/setup.bash
```

## Running

### Manual Launch
```bash
ros2 launch hello_service_ros hello.launch.py
```

### Setting up as a System Service

To run this node automatically on system startup using systemd:

1. **Copy the service file to systemd directory:**
   ```bash
   sudo cp src/hello_service_ros/orin_on.service /etc/systemd/system/
   ```

2. **Update the service file if needed:**
   Edit `/etc/systemd/system/orin_on.service` and verify:
   - The `User` and `Group` match your username
   - The paths in `ExecStart` are correct for your ROS2 installation
   
3. **Enable and start the service:**
   ```bash
   sudo systemctl daemon-reload
   sudo systemctl enable orin_on.service
   sudo systemctl start orin_on.service
   ```

4. **Check service status:**
   ```bash
   sudo systemctl status orin_on.service
   ```

5. **View logs:**
   ```bash
   journalctl -u orin_on.service -f
   ```

### Service Management Commands

- **Restart the service:**
  ```bash
  sudo systemctl restart orin_on.service
  ```

- **Stop the service:**
  ```bash
  sudo systemctl stop orin_on.service
  ```

- **Disable autostart:**
  ```bash
  sudo systemctl disable orin_on.service
  ```

## Monitoring

To verify the node is publishing:

```bash
ros2 topic echo /orin/on
ros2 topic hz /orin/on
```