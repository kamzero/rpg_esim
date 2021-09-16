#pragma once

#include <esim/common/types.hpp>
#include <esim/visualization/publisher_interface.hpp>
#include <fstream>

namespace event_camera_simulator {

class BBoxFilePublisher : public Publisher
{
public:
  BBoxFilePublisher(const std::string& path_to_bboxes_text_file, size_t num_cameras);
  ~BBoxFilePublisher();

  virtual void bboxCallback(const std::vector<BBox>& bboxes, Time t) override;

  static Publisher::Ptr createFromGflags(size_t num_cameras);


private:
  std::ofstream bboxes_text_file_;
};

} // namespace event_camera_simulator
