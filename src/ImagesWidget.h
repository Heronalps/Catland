#ifndef IMAGES_WIDGET_H_
#define IMAGES_WIDGET_H_

#include <vector>

#include <Wt/WContainerWidget.h>

using namespace Wt;

class ImagesWidget : public WContainerWidget
{
public:
  static const int HURRAY;

  ImagesWidget(int maxGuesses);

  /*
   * 0 - maxGuesses: corresponds to 0 up to maxGuesses guesses
   *         HURRAY: when won
   */
  void showImage(int index);
  int currentImage() const { return image_; }

private:
  std::vector<WImage *> images_;
  int image_;

  WImage *image(int index) const;
};

#endif // IMAGES_WIDGET_H_
