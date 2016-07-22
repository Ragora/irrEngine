#include <CGUIImage.h>

CGUIImage::CGUIImage(IrrlichtDevice *device)
{
    Device = device;
    Video = Device->getVideoDriver();
    Gui = Device->getGUIEnvironment();
    Scale = vector2df(1,1); //In images 1,1 is the actual scale

    //Add our button
    Image = Gui->addImage(0,  core::position2d<s32>(0,0));
    Image->setScaleImage(true);

}

CGUIImage::~CGUIImage(void)
{
    if (Image)
        Image->remove();
    // if (Texture)
    //   Texture->remove();
}

void CGUIImage::setToolTipText(const wchar_t* text)
{
    Image->setToolTipText(text);
}

void CGUIImage::setImage(video::ITexture* image)
{
    Texture = image;
    Image->setImage(image);
}

void CGUIImage::setRelativePosition(vector2df position)
{
    const core::dimension2d<u32>& imageSize = Texture->getOriginalSize();
    vector2df offset = vector2df(imageSize.Width, imageSize.Height);

    Image->setRelativePosition(core::rect<s32>(
                                   position.X,
                                   position.Y,
                                   position.X + (offset.X * Scale.X),
                                   position.Y + (offset.Y * Scale.Y)));
}

vector2df CGUIImage::getRelativePosition()
{
    const core::rect<s32>& rectangle = Image->getRelativePosition();
    return vector2df(rectangle.UpperLeftCorner.X, rectangle.UpperLeftCorner.Y);
}

void CGUIImage::setRelativeScale(vector2df scale)
{
    Scale = scale;
    this->setRelativePosition(getRelativePosition()); //Tells it to resize the image
}

void CGUIImage::setPosition(vector2df position)
{
    const core::dimension2d<u32>& imageSize = Texture->getOriginalSize();
    vector2df offset = vector2df(imageSize.Width, imageSize.Height);

    Image->setRelativePosition(core::rect<s32>(
                                   position.X - (offset.X * Scale.X),
                                   position.Y - (offset.Y * Scale.Y),
                                   position.X + (offset.X * Scale.X),
                                   position.Y + (offset.Y * Scale.Y)));
}

void CGUIImage::setScale(vector2df scale)
{
    const core::dimension2d<u32>& imageSize = Texture->getOriginalSize();
}

vector2df CGUIImage::getPosition()
{

}
