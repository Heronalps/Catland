#include "ImagesWidget.h"

#include <Wt/WImage.h>
#include <Wt/WAny.h>

const int ImagesWidget::HURRAY = -1;

ImagesWidget::ImagesWidget(int maxGuesses)
{
  for (int i = 0; i <= maxGuesses; ++i) {
    std::string fname = "icons/item";
    fname += std::to_string(i) + ".jpg";
    WImage *theImage = addWidget(cpp14::make_unique<WImage>(fname));
    images_.push_back(theImage);

    // Although not necessary, we can avoid flicker (on konqueror)
    // by presetting the image size.
    theImage->resize(512, 512);
    theImage->hide();
  }

  WImage *hurray = addWidget(cpp14::make_unique<WImage>("icons/hurray.jpg"));
  hurray->resize(512, 512);
  hurray->hide();
  images_.push_back(hurray);
  std::cout << images_.size() << std::endl;

  image_ = 0;
  showImage(HURRAY);
}

void ImagesWidget::showImage(int index)
{
  image(image_)->hide();
  image_ = index;
  image(image_)->show();
}

WImage *ImagesWidget::image(int index) const
{
  return index == HURRAY ? images_.back() : images_[index];
}
