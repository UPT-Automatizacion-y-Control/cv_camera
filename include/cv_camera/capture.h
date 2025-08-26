#ifndef CV_CAMERA_CAPTURE_H
#define CV_CAMERA_CAPTURE_H

#include "cv_camera/exception.h"
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <image_transport/image_transport.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/image_encodings.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <camera_info_manager/camera_info_manager.hpp>

namespace cv_camera
{

class Capture
{
public:
  Capture(rclcpp::Node::SharedPtr node,
          const std::string &topic_name,
          uint32_t buffer_size,
          const std::string &frame_id);

  void open(int32_t device_id);
  void open(const std::string &device_path);
  void open();
  void openFile(const std::string &file_path);

  void loadCameraInfo();

  bool capture();
  void publish();

  inline const sensor_msgs::msg::CameraInfo &getInfo() const
  {
    return info_;
  }

  inline const cv::Mat &getCvImage() const
  {
    return bridge_.image;
  }

  inline const sensor_msgs::msg::Image::SharedPtr getImageMsgPtr() const
  {
    return bridge_.toImageMsg();
  }

  inline bool setWidth(int32_t width)
  {
    return cap_.set(cv::CAP_PROP_FRAME_WIDTH, width);
  }

  inline bool setHeight(int32_t height)
  {
    return cap_.set(cv::CAP_PROP_FRAME_HEIGHT, height);
  }

  bool setPropertyFromParam(int property_id, const std::string &param_name);

private:
  void rescaleCameraInfo(uint width, uint height);
  void configureFormat();  // <-- NUEVO MÉTODO DECLARADO

  rclcpp::Node::SharedPtr node_;
  image_transport::ImageTransport it_;
  std::string topic_name_;
  std::string frame_id_;
  uint32_t buffer_size_;

  image_transport::CameraPublisher pub_;
  cv::VideoCapture cap_;
  cv_bridge::CvImage bridge_;
  sensor_msgs::msg::CameraInfo info_;
  camera_info_manager::CameraInfoManager info_manager_;
  bool rescale_camera_info_;
  rclcpp::Duration capture_delay_;
};

} // namespace cv_camera

#endif // CV_CAMERA_CAPTURE_H
