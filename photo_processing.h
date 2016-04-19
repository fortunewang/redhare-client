#ifndef __REDHARE__PHOTO_PROCESSING__H__
#define __REDHARE__PHOTO_PROCESSING__H__

#include <QImage>

namespace photo_processing {

void opaque(QImage &src);
void scale(QImage &src, int w, int h);
void monochrome(QImage &src);
void round(QImage &src);
void frame(QImage &src);

QImage opaqued(const QImage &src);
QImage scaled(const QImage &src, int w, int h);
QImage monochromed(const QImage &src);
QImage rounded(const QImage &src);
QImage framed(const QImage &src);

} // namespace photo_processing

#endif // __REDHARE__PHOTO_PROCESSING__H__

