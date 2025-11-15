orin@ubuntu:~/ros2_ws$ sudo cp src/as_drive/orin_on.service /etc/systemd/system/
orin@ubuntu:~/ros2_ws$ sudo systemctl daemon-reload
orin@ubuntu:~/ros2_ws$ sudo systemctl restart orin_on.service
orin@ubuntu:~/ros2_ws$ sudo systemctl status orin_on.service