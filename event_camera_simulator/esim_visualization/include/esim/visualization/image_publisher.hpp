#pragma once

#include <esim/common/types.hpp>
#include <esim/visualization/publisher_interface.hpp>
#include <opencv2/opencv.hpp>

namespace event_camera_simulator {

class ImagePublisher : public Publisher
{
public:
  ImagePublisher(const std::string& path_to_image_folder, size_t num_cameras);
  ~ImagePublisher();

  virtual void imageCallback(const ImagePtrVector& images, Time t) override;
  static Publisher::Ptr createFromGflags(size_t num_cameras);


private:
  std::string image_folder_;
};

} // namespace event_camera_simulator
