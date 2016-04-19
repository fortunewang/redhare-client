#include "photo_processing.h"

namespace photo_processing {

namespace {

inline void polt(QImage &dest, int x, int y, int alpha0)
{
    QRgb pixel;
    int red, green, blue, alpha;
    int width = dest.width() - 1;
    int height = dest.height() - 1;

    pixel = dest.pixel(x, y);
    red = qRed(pixel) * alpha0 / 255;
    green = qGreen(pixel) * alpha0 / 255;
    blue = qBlue(pixel) * alpha0 / 255;
    alpha = qAlpha(pixel) * alpha0 / 255;
    dest.setPixel(x, y, qRgba(red, green, blue, alpha));

    pixel = dest.pixel(width - x, y);
    red = qRed(pixel) * alpha0 / 255;
    green = qGreen(pixel) * alpha0 / 255;
    blue = qBlue(pixel) * alpha0 / 255;
    alpha = qAlpha(pixel) * alpha0 / 255;
    dest.setPixel(width - x, y, qRgba(red, green, blue, alpha));

    pixel = dest.pixel(x, height - y);
    red = qRed(pixel) * alpha0 / 255;
    green = qGreen(pixel) * alpha0 / 255;
    blue = qBlue(pixel) * alpha0 / 255;
    alpha = qAlpha(pixel) * alpha0 / 255;
    dest.setPixel(x, height - y, qRgba(red, green, blue, alpha));

    pixel = dest.pixel(width - x, height - y);
    red = qRed(pixel) * alpha0 / 255;
    green = qGreen(pixel) * alpha0 / 255;
    blue = qBlue(pixel) * alpha0 / 255;
    alpha = qAlpha(pixel) * alpha0 / 255;
    dest.setPixel(width - x, height - y, qRgba(red, green, blue, alpha));
}

} // anonymous namespace

void opaque(QImage &src)
{
    src = opaqued(src);
}

QImage opaqued(const QImage &src)
{
    if(src.isNull())
    {
        return QImage();
    }
    QImage dest(src.size(), QImage::Format_ARGB32_Premultiplied);
    if(!dest.isNull())
    {
        dest.fill(Qt::white);
        QPainter painter(&dest);
        painter.drawImage(0, 0, src);
        painter.end();
    }
    return dest;
}

void scale(QImage &src, int w, int h)
{
    src = scaled(src, w, h);
}

QImage scaled(const QImage &src, int w, int h)
{
    return src.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void monochrome(QImage &src)
{
    for(int i = 0; i < src.size().width(); ++i)
    {
        for(int j = 0; j < src.size().height(); ++j)
        {
            QRgb pixel = src.pixel(i, j);
            int gray = qGray(pixel);
            src.setPixel(i, j, qRgba(gray, gray, gray, qAlpha(pixel)));
        }
    }
}

QImage monochromed(const QImage &src)
{
    QImage dest = src.copy();
    monochrome(dest);
    return dest;
}

void round(QImage &src)
{
    if(src.format() != QImage::Format_ARGB32_Premultiplied)
    {
        src = src.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }
    if(src.width() > 4 || src.height() > 4)
    {
        polt(src, 0, 0, 0);
        polt(src, 0, 1, 64);
        polt(src, 0, 2, 128);
        polt(src, 0, 3, 192);
        polt(src, 1, 0, 64);
        polt(src, 2, 0, 128);
        polt(src, 3, 0, 192);
        polt(src, 1, 1, 170);
    }
}

QImage rounded(const QImage &src)
{
    QImage dest = src.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    round(dest);
    return dest;
}

void frame(QImage &src)
{
    if(src.format() != QImage::Format_ARGB32_Premultiplied)
    {
        src = src.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }
    int width = src.width();
    int height = src.height();
    if(width <= 6 || height <= 6)
    {
        return;
    }
    QImage origin = src.copy(1, 1, width - 2, height - 2);
    src.fill(Qt::white);
    round(src);
    round(origin);
    QPainter p(&src);
    p.drawImage(1, 1, origin);
    p.end();
}

QImage framed(const QImage &src)
{
    QImage dest = src.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    frame(dest);
    return dest;
}

} // namespace photo_processing

