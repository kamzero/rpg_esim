#include <esim/visualization/bbox_file_publisher.hpp>
#include <esim/common/utils.hpp>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(path_to_bboxes_text_file, "",
"Path to the text file in which to write the bboxes.");

namespace event_camera_simulator {

BBoxFilePublisher::BBoxFilePublisher(const std::string& path_to_bboxes_text_file, size_t num_cameras)
{
  CHECK_EQ(num_cameras, 1) << "BBoxFilePublisher implemented for one camera only";
  bboxes_text_file_.open(path_to_bboxes_text_file);
}

BBoxFilePublisher::~BBoxFilePublisher()
{
    bboxes_text_file_.close();
}

Publisher::Ptr BBoxFilePublisher::createFromGflags(size_t num_cameras)
{
  if(FLAGS_path_to_bboxes_text_file == "")
  {
    LOG(WARNING) << "Empty bboxes text file path: will not write bboxes to a text file.";
    return nullptr;
  }

  return 
         std::make_shared<BBoxFilePublisher>(FLAGS_path_to_bboxes_text_file,
                                             num_cameras);
}

void BBoxFilePublisher::bboxCallback(const std::vector<BBox>& bboxes, Time t)
{
    // CHECK_EQ(bboxes.size(), 1);
    if(bboxes.size() != 1){
      std::cout << "bboxes size is " << bboxes.size() << std::endl;
      return; 
    }
    bboxes_text_file_ << std::to_string(t) << " " << bboxes[0].x  << " " <<  bboxes[0].y  << " " 
      << bboxes[0].width  << " " << bboxes[0].height << std::endl;
}


} // namespace event_camera_simulator
