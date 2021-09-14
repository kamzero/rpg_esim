#include <esim/visualization/image_publisher.hpp>
#include <esim/common/utils.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <ros/ros.h>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(path_to_image_folder, "",
"Path to the image folder in which to save the images.");

namespace event_camera_simulator {

ImagePublisher::ImagePublisher(const std::string& path_to_image_folder, size_t num_cameras)
{
  CHECK_EQ(num_cameras, 1) << "ImagePublisher implemented for one camera only";
//   image_folder_.open(path_to_image_folder);
  image_folder_ = path_to_image_folder;
}

ImagePublisher::~ImagePublisher()
{
    // image_folder_.close();
}

Publisher::Ptr ImagePublisher::createFromGflags(size_t num_cameras)
{
  if(FLAGS_path_to_image_folder == "")
  {
    LOG(WARNING) << "Empty image folder path: will not save images.";
    return nullptr;
  }

  return std::make_shared<ImagePublisher>(FLAGS_path_to_image_folder,
                                             num_cameras);
}


void ImagePublisher::imageCallback(const ImagePtrVector& images, Time t) {
    // CHECK_EQ(images.size(), 1);
    ROS_WARN("ImagePtrVector: %d", images.size());
    for(auto image_ptr: images)
    {
        cv::imwrite(image_folder_+std::to_string(t)+".jpg", *image_ptr);
    }   
}


} // namespace event_camera_simulator
