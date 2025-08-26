# cv_camera modificado
Este paquete se ha probado en ROS2 Jazzy en Ubuntu 24.04. 

Este paquete está basado en este [repositorio](https://github.com/Kapernikov/cv_camera) del cual se ha modificado el codigo fuente para poder añadir una opción de escoger el formato de la cámara, ya sea MJPG o YUYV.

Este paquete ocupa [camera_info_manager](http://wiki.ros.org/camera_info_manager), si no se establecen datos de calibración, tendrá valores ficticios excepto el ancho y la altura.

Para obtener los datos de calibración de alguna cámara se tiene que instalar el siguiente paquete (si es que no se ha instalado antes) y seguir los pasos de este [tutorial](https://github.com/ros-perception/image_pipeline/blob/rolling/camera_calibration/doc/tutorial_mono.rst):

```
sudo apt-get install ros-jazzy-image-pipeline
```
Al igual que asegurarse que se tengan instaladas las dependencias del paquete al ejecutar la siguientes líneas de código desde la raíz del workspace:

```
sudo apt update
rosdep install -i --from-path src --rosdistro jazzy -y
```
# Launcher recomendado
El launcher recomendado para utilizar este paquete es el siguiente:
```
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cv_camera',
            executable='cv_camera_node',
            parameters=[
                {"device_path": "/dev/video2"},
                {"device_id": 2},
                {"frame_id": "webcam"}, 
                {"image_width": 1920},
                {"image_height": 1080},
                {"rate": 30.0},
                {"pixel_format": "MJPG"},  # <-- MJPG o YUYV
                {"camera_info_url": ""}
            ]
        )
    ])

```